# debian

|command|description|
|--|--|
apt build-dep packagename | 构建依赖
dpkg-buildpackage -us -uc -nc | 构建deb包
apt depends packagename | packagename依赖的包
apt rdepends packagename | 哪些包依赖packagename
apt-file search file | 搜索文件相关的包
apt download packagename | 下载包
apt source packagename | 下载源码包

# gsetting

|command|description|
|--|--|
glib-compile-schemas | /usr/share/glib-2.0/schemas
gsettings list-schemas |             显示系统已安装的不可重定位的schema  
gsettings list-relocatable-schemas | 显示已安装的可重定位的schema  
gsettings list-children SCHEMA   |  显示指定schema的children，其中SCHEMA指xml  文件中schema的id属性值，例如实例中的"org.lili.test.app.testgsettings"
gsettings list-keys SCHEMA |         显示指定schema的所有项(key)
gsettings range SCHEMA KEY  |        查询指定schema的指定项KEY的有效取值范围
gsettings get SCHEMA KEY     |      显示指定schema的指定项KEY的值
gsettings set SCHEMA KEY VALUE |    设置指定schema的指定项KEY的值为VALUE
gsettings reset SCHEMA KEY      |   恢复指定schema的指定项KEY的值为默认值
gsettings reset-recursively SCHEMA| 恢复指定schema的所有key的值为默认值
gsettings list-recursively [SCHEMA]|如果有SCHEMA参数，则递归显示指定schema的所有项(key)和值(value)，如果没有SCHEMA参数，则递归显示所有schema的所有项(key)和值(value)

# translation

|command|description|
|--|--|
sudo apt install transifex-client |  安装tx
tx pull -t -a -s -b master |  拉取翻译（-a -f 全部拉取）
tx push -s -b master | 推送翻译

# coredump

1. sudo apt install systemd-coredump 安装
2. sudo apt install dde-control-center-dbgsym 安装控制中心符号调试信息
如果没有进行core dump 的相关设置，默认是不开启的。可以通过ulimit -c查看是否开启。如果输出为0，则没有开启，需要执行ulimit -c unlimited开启core dump功能
3. 配置/etc/profile 中加上 ulimit -c unlimited生成coredump文件
4. 使用coredumpctl list查看崩溃列表 获取崩溃的pid 
5. 复现问题后马上使用coredumpctl dump查看堆栈信息 或者 coredumpctl info + 崩溃pid
6. sudo apt install lz4; lz4 -d FILE 来解压coredump文件

# ssh

generate key :  

``` sh
ssh-keygen  // default key type : RSA 
ssh-keygen -t ed25519 //  specify key type: ed25519  
```

proxy config：~/.ssh/config

``` sh
Host github.com
    Hostname github.com
    ProxyCommand /usr/bin/corkscrew 10.20.52.42 7890 %h %p
```

/usr/sbin/sshd -T 查看出错原因

no hostkeys available— exiting:  

# 进程

|command|description|
|--|--|
cat /proc/28818/environ \| tr '\0' '\n' | 查看进程28816的环境变量
pldd 12345 或者 （cat /proc/12345/maps \| awk '{print $6}' \| grep '\.so' \| sort \| uniq）| 查看程依赖的so
strings *.so | 查看so的字符

# dbus

|command|description|
|--|--|
qdbus --session | 查看当前session所有的service信息
qdbus --system  | 查看当前system所有的service信息
could not find a Qt installation of '' | sudo apt install qtchooser
qdbus com.deepin.dde.Clipboard /com/deepin/dde/Clipboard | tab补全
dbus-monitor --session interface=org.freedesktop.Notifications  | 监听dbus服务接口

# plantuml (vscode plugin)

install java & Graphviz

``` sh
sudo apt install default-jre graphviz
```

# gammaray

/proc/sys/kernel/yama/ptrace_scope to 0

``` sh
sudo vim /etc/sysctl.d/10-ptrace.conf
```
type : ` kernel.yama.ptrace_scope = 0`

take effect immediately：

``` sh
sudo sysctl --system -a -p | grep yama
```

# proxy

10.20.52.42  7890  
localhost, 127.0.0.0/8, ::1, *.org.deepin.org, *.uniontech.com, *.deepin.com  
git config --global http.proxy 'http://127.0.0.1:7890'  
git config --global https.proxy 'https://127.0.0.1:7890'  
export http_proxy=https://127.0.0.1:7890/  
export https_proxy=https://127.0.0.1:7890/  

# DTK

|command|description|
|--|--|
D_DXCB_FORCE_NO_TITLEBAR | 强制无标题栏

# others

|command|description|
|--|--|
sudo apt install manpages-dev | 安装手册
xprop | 查看窗口属性
uos-activator-cmd -s --kms kms.uniontech.com:8900:Vlc1cGIyNTBaV05v | 激活UOS
sudo pkill -ef /usr/lib/deepin-daemon/dde-system-daemon; sudo DDE_DEBUG_LEVEL=debug DDE_DEBUG_MATCH=account /usr/lib/deepin-daemon/dde-system-daemon | 定位 dde-daemon
