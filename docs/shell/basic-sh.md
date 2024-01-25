# 登陆shell从5个不同的启动文件里读取命令：

- /etc/profile (系统默认的bash shell主启动文件, 用户登陆都会执行该启动文件)
- $HOME/.bash_profile
- $HOME/.bashrc
- $HOME/.bash_login
- $HOME/.profile

# 特殊变量（位置参数）

|name|decription|
|---|---|
| $0| shell的名称。|
| $n| 第n个位置参数。|
| $*| 含有所有参数内容的单个值，由IFS环境变量中的第一个字符分隔；没定义IFS的话， 由空格分隔。|
| $@| 将所有的命令行参数展开为多个参数。|
| $#| 位置参数的总数。|
| $?| 最近一个命令的退出状态码。|
| $-| 当前选项标记。|
| $$| 当前shell的进程ID（PID）。|
| $!| 最近一个后台命令的PID。|
