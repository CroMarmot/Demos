import random
import time
import signal
from datetime import datetime
from rich.console import Console
from rich.live import Live
from rich.panel import Panel
from rich.layout import Layout
from rich.text import Text

# 初始化
console = Console()
running = True

def signal_handler(sig, frame):
    global running
    console.print("\n\n[bold yellow]🛑 收到中断信号，正在安全退出...[/bold yellow]")
    running = False

signal.signal(signal.SIGINT, signal_handler)

STEPSBAR = 10000

class CollatzMonitor:
    def __init__(self):
        self.attempt = 0
        self.start_datetime = datetime.now()  # 只记录开始时间
        self.current_start = 0
        self.steps = 0
        self.timeout_cnt = 0
        self.max_steps = 0
        self.max_steps_val = 0
        self.ge_bar_cnt = 0


    def make_layout(self) -> Layout:
        layout = Layout()
        layout.split(
            Layout(name="header", size=12),
            Layout(name="main",size=7),
        )
        layout["header"].update(self._make_header())
        layout["main"].update(self._make_current_task())
        return layout

    def _make_header(self) -> Panel:
        # 只展示程序开始时间（时分秒）
        start_time_str = self.start_datetime.strftime("%Y-%m-%d %H:%M:%S") # 修改为年月日时分秒
        text = Text()
        text.append("🚀 Collatz 反例搜索器\n", style="bold green")
        text.append(f"开始时间          : {start_time_str}\n", style="dim")
        text.append(f"总尝试            : {self.attempt}\n", style="dim")
        text.append(f"超时次数          : {self.timeout_cnt}\n", style="dim")
        text.append(f"最大步数          : {self.max_steps} ({self.max_steps_val})\n", style="dim")
        text.append(f"大于{STEPSBAR} steps次数: {self.ge_bar_cnt}\n", style="dim")
        return Panel(text, title="📊 统计", border_style="green")

    def _make_current_task(self) -> Panel:
        if self.current_start == 0:
            content = "等待启动..."
        else:
            bits = self.current_start.bit_length()
            content = (
                f"起始值: [bold cyan]{self.current_start}[/bold cyan] ({bits} 位)\n"
                f"步数: {self.steps}"
            )
        return Panel(content, title="🔄 当前任务", border_style="magenta")

    def run_one_trial(self):
        # 生成 2^500 < n < 2^1000 的随机整数
        while True:
            bits = random.randint(500, 999)
            n = random.getrandbits(bits)
            if n > (1 << 68):
                break

        self.attempt += 1
        self.current_start = n
        self.current_value = n
        self.steps = 0
        
        n_val = n
        
        # 只在步骤达到阈值时才开始记录时间进行超时检查
        start_time = None
        
        while n_val != 1 and running:
            # 执行 Collatz 步骤
            if n_val & 1:
                n_val = 3 * n_val + 1
            else:
                n_val //= 2

            self.steps += 1
            if n_val == 1 and self.steps > self.max_steps:
                self.max_steps = self.steps
                self.max_steps_val = self.current_start           

            # 每 500 步更新一次状态（避免频繁刷新）
            if self.steps and  self.steps % STEPSBAR == 0:
                self.ge_bar_cnt += 1
                if start_time is None:
                    start_time = time.time()  # 第一次达到阈值时才记录时间
                # 超时检查（1 分钟 = 60 秒）
                if time.time() - start_time > 60:
                    self._write_to_file("timeout", n, current=n_val, steps=self.steps)
                    self.timeout_cnt += 1
                    return


    def _write_to_file(self, kind, start, **kwargs):
        with open("find.txt", "a", encoding="utf-8") as f:
            f.write(f"{'='*60}\n")
            f.write(f"类型: {'超时' if kind == 'timeout' else '非平凡环'}\n")
            f.write(f"起始值: {start}\n")
            if kind == "timeout":
                f.write(f"当前值: {kwargs['current']}\n")
                f.write(f"步数: {kwargs['steps']}\n")
            else:
                f.write(f"环: {kwargs['cycle']}\n")
            f.write(f"时间: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
            f.write(f"{'='*60}\n\n")

def main():
    global running
    monitor = CollatzMonitor()
    
    try:
        with Live(monitor.make_layout(), refresh_per_second=1, console=console) as live:
            while running:
                monitor.run_one_trial()
                if not running:
                    break
                live.update(monitor.make_layout())
    except KeyboardInterrupt:
        pass
    finally:
        console.print("[bold green]👋 程序已退出。[/bold green]")

if __name__ == "__main__":
    main()