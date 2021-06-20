# gitee 提供了clone+同步功能 那这个仓库似乎没啥卵用了

https://gitee.com/help/articles/4284

# Github2Gitee

利用免费线环境解决github克隆问题

# 现状

部分国内网络 Github 网速只有10kb/s

gitee能有较好的网速，但没有想要的github上的仓库

部分在线开发平台能免费使用并且访问外部网络

# 准备工作

gitee 配置你所用的在线环境的身份信息，例如ssh key

在gitee 上创建仓库你的目标地址仓库

# 使用

`./clone.sh <github url> <gitee url>`

示例

`./clone.sh https://github.com/CroMarmot/Github2Gitee.git git@gitee.com:CroMarmot/Demo001.git`

# 警告

脚本会创建和删除`CROMARMOT_TMP_CLONE_FOLDER`文件夹, 虽然已经尽可能重名，但还是提醒一下注意不要重名

