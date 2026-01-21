// g++ -O3 -std=c++17 -pthread md5_miner.cpp -o md5_miner -lcrypto -lssl 
// [线程 3] 358200M 次 @    7.5 MH/s | 局部最佳: 10/16 → 20251231204968ee | 字符串: HappyNewYear137694701283 | 全局: 10/16
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>
#include <mutex>
#include <openssl/md5.h>

#ifdef _WIN32
#include <windows.h>
#endif

// ==================== 配置区 ====================
const std::string source_prefix = "HappyNewYear";
// const std::string target_prefix = "20251231";          // 测试推荐 8 位（很快成功）
const std::string target_prefix = "2025123120260101";  // 16 位终极挑战
// ================================================

const int target_len = target_prefix.length();

// 全局状态
std::atomic<bool> found{ false };
std::atomic<int> global_best_len{ 0 };
std::string global_best_string;
std::string global_best_hash;

std::mutex cout_mutex;

// MD5 计算
std::string md5_hex(const std::string& input) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), digest);

    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        oss << std::setw(2) << static_cast<unsigned int>(digest[i]);
    }
    return oss.str();
}

// 挖掘线程
void miner_thread(unsigned int thread_id, unsigned int num_threads) {
    std::string base = source_prefix;
    unsigned long long counter = 8815902064 + thread_id;
    auto start_time = std::chrono::high_resolution_clock::now();

    // 线程局部最佳
    int local_best_len = 0;
    std::string local_best_prefix = std::string(target_len, '-');  // 初始用 - 填充
    std::string local_best_string = "<初始>";

    while (!found) {
        std::string input = base + std::to_string(counter);
        std::string hash_hex = md5_hex(input);

        int match_len = 0;
        while (match_len < target_len && hash_hex[match_len] == target_prefix[match_len]) {
            ++match_len;
        }

        // 更新局部最佳
        if (match_len > local_best_len) {
            local_best_len = match_len;
            local_best_prefix = hash_hex.substr(0, target_len);
            local_best_string = input;

            // 如果刷新了全局，也在这里处理（避免重复）
            if (match_len > global_best_len) {
                int old = global_best_len.load();
                if (match_len > old && global_best_len.compare_exchange_strong(old, match_len)) {
                    global_best_string = input;
                    global_best_hash = hash_hex;

                    std::lock_guard<std::mutex> lock(cout_mutex);
                    std::cout << "\n🔥 【全局新纪录！】线程 " << thread_id
                        << " → " << match_len << "/" << target_len << " 位: "
                        << local_best_prefix << " | 字符串: " << input << "\n\n";
                }
            }
        }

        // 完美匹配
        if (match_len == target_len) {
            found = true;
            auto end_time = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration<double>(end_time - start_time).count();
            double rate = counter / elapsed / 1e6;

            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "\n🎉🎉🎉 恭喜！找到了完美匹配！🎉🎉🎉\n"
                    << "幸运线程: " << thread_id << " | 字符串: " << input << "\n"
                    << "MD5: " << hash_hex << " | 后缀: " << counter << "\n"
                    << "用时: " << elapsed << " 秒 | 速度: "
                    << std::fixed << std::setprecision(2) << rate << " MH/s\n"
                    << "Happy New Year 2026! 🚀🎄\n\n";
            }
            return;
        }

        counter += num_threads;

        // 每 100M 次输出一行进度（严格单行！）
        if (counter % 100'000'000 == thread_id) {
            auto now = std::chrono::high_resolution_clock::now();
            double secs = std::chrono::duration<double>(now - start_time).count();
            if (secs > 1.0) {
                double rate = (counter - thread_id) / secs / 1e6;
                int current_global = global_best_len.load();

                // 截取字符串后 20 字符显示（避免一行太长）
                std::string display_str = local_best_string;
                if (display_str.length() > 30) {
                    display_str = "..." + display_str.substr(display_str.length() - 27);
                }

                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "[线程" << std::setw(2) << thread_id << "] "
                    << std::setw(5) << (counter / 1'000'000) << "M 次 @ "
                    << std::fixed << std::setprecision(1) << std::setw(6) << rate << " MH/s | "
                    << "局部最佳: " << std::setw(2) << local_best_len << "/" << target_len
                    << " → " << local_best_prefix
                    << " | 字符串: " << display_str
                    << " | 全局: " << current_global << "/" << target_len << "\n";
            }
        }
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 8;

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "🎉 Happy New Year 2025 特别挑战\n"
            << "目标前缀: " << target_prefix << " (" << target_len << " 位)\n"
            << "使用线程数: " << num_threads << "\n\n"
            << "开始挖掘... ⛏️\n\n";
    }

    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < num_threads; ++i) {
        threads.emplace_back(miner_thread, i, num_threads);
    }

    for (auto& t : threads) t.join();

    return 0;
}