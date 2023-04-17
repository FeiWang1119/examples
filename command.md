# debian

|命令|说明|
|--|--|
 sudo apt build-dep packagename | 构建依赖
dpkg-buildpackage -us -uc -nc | 构建deb包
apt depends packagename | packagename依赖的包
apt rdepends packagename | 哪些包依赖packagename
apt-file search file | 搜索文件相关的包

# Qt 

|命令|说明|
|--|--|
apt source qtbase-opensource-src | 获取源码
-nograb -platformpluginpath /home/fei/repo/dtk/qt5integration/bin/plugins | 指定平台插件
export LD_LIBRARY_PATH=qtbuilddir/lib:dtkbuilddir/lib | 设置程序运行是链接库的路径
export QT_QPA_PLATFORM_PLUGIN_PATH=qtbuilddir/plugins/platforms |  平台相关插件
export QT_PLUGIN_PATH=qtbuilddir/plugins | Qt插件
export PKG_CONFIG_PATH=qtbuilddir/lib/pkgconfig:dtkbuilddir/lib/pkgconfig | 在 Qt pro 中配置的 phgconfig 就是用过查找该目录下的.PC文件 实现头文件和库的引入
sudo apt install libqt5gui5-dbgsym libqt5widgets5-dbgsym libqt5core5a-dbgsym | 安装Qt的调试库
LANG=bo_CN LANGUAGE=bo_CN dde-file-manager |  藏语
sudo apt install qtbase5-examples qt5-doc | 安装例子和帮助文档
sudo apt install qt5-default |  配置qt5 为qt开发的默认版本
../configure -opensource -confirm-license  -nomake tests -nomake examples --sqlite=system --prefix=/home/fei/qt5.15  |  配置源码

# qtcreator 配置文件

linux ：   
~/.config/QtProject  （测过）  
~/.local/share/data/QtProject/qtcreator   

window ：   
%APPDATA%\QtProject  
%LOCALAPPDATA%\QtProject  

# cmake 指定 特定路径下的qt库

``` sh
cmake -DCMAKE_PREFIX_PATH=$HOME/Qt/5.11.2/gcc_64 ..
```

- Make sure to clear the build directory before changing CMAKE_PREFIX_PATH
- Are you sure there's a lib/cmake folder inside /home/cavit/Qt/5.6? (That's where CMake finds the Qt5 config files)
  
# cmake 构建安装

``` sh
mkdir build && cd build
cmake ../ -G Ninja -DCMAKE_INSTALL_PREFIX=/usr/local
sudo ninja install
```

#  gsetting

|命令|说明|
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

#  dde-daemon

|命令|说明|
|--|--|
sudo pkill -ef /usr/lib/deepin-daemon/dde-system-daemon; sudo DDE_DEBUG_LEVEL=debug DDE_DEBUG_MATCH=account /usr/lib/deepin-daemon/dde-system-daemon | 定位 dde-daemon

#  translation

|命令|说明|
|--|--|
tx pull -s -b m20 |  拉取翻译（-a -f 全部拉取）
tx push -s -b master | 推送翻译

# coredump

1. sudo apt install systemd-coredump 安装
2. sudo apt install dde-control-center-dbgsym 安装控制中心符号调试信息
如果没有进行core dump 的相关设置，默认是不开启的。可以通过ulimit -c查看是否开启。如果输出为0，则没有开启，需要执行ulimit -c unlimited开启core dump功能
3. 配置/etc/profile 中加上 ulimit -c unlimited生成coredump文件
4. 使用coredumpctl list查看崩溃列表 获取崩溃的pid 
5. 复现问题后马上使用coredumpctl dump查看堆栈信息 或者 coredumpctl info + 崩溃pid
6. sudo apt install lz4; lz4 -d FILE 来解压coredump文件

# uos 激活

uos-activator-cmd -s --kms kms.uniontech.com:8900:Vlc1cGIyNTBaV05v

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

1. root权限下，重新生成密钥  

ssh-keygen -t dsa -f /etc/ssh/ssh_host_dsa_key  
ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key   

2. 修改密钥权限  

chmod 600 /etc/ssh/ssh_host_dsa_key  
chmod 600 /etc/ssh/ssh_host_rsa_key  

3. 重启ssh  

systemctl restart sshd  
service sshd restart

# CRP跳过单元测试方法：
项目-编辑-构建参数列表
{'i386': 'DEB_BUILD_OPTIONS=nocheck ', 'arm64': 'DEB_BUILD_OPTIONS=nocheck ','amd64': 'DEB_BUILD_OPTIONS=nocheck ', 'mips64el': 'DEB_BUILD_OPTIONS=nocheck ', 'sw_64': 'DEB_BUILD_OPTIONS=nocheck ', 'loongarch64': 'DEB_BUILD_OPTIONS=nocheck '}

crp上ut失败时跳过ut

# Git

|命令|说明|
|--|--|
git push origin develop | 创建远程分支develop
git push origin --delete develop | 删除远程分支develop
git fetch origin develop/snipe:snipe | 从远程分支到本地分支

# 进程

|命令|说明|
|--|--|
tr '\0' '\n' < /proc/12345/environ 或者 ps eww -p 12345 | 查看进程环境变量
pldd 12345 或者 （cat /proc/12345/maps \| awk '{print $6}' \| grep '\.so' \| sort \| uniq） | 查看程依赖的so
strings *.so | 查看so的字符

# dbus

|命令|说明|
|--|--|
qdbus --session | 查看当前session所有的service信息
qdbus --system  | 查看当前system所有的service信息
could not find a Qt installation of '' | sudo apt install qtchooser
qdbus com.deepin.dde.Clipboard /com/deepin/dde/Clipboard | tab补全
dbus-monitor --session interface=org.freedesktop.Notifications  | 监听dbus服务接口

# xprop 查看窗口属性

# crontab 系统定时工具

WAYLAND_DEBUG=1

# 支持 plantuml

安装java和Graphviz

``` sh
sudo apt install default-jre
sudo apt install graphviz
```
#  gammaray 

/proc/sys/kernel/yama/ptrace_scope to 0

``` sh
sudo vim /etc/sysctl.d/10-ptrace.conf
```
type : kernel.yama.ptrace_scope = 0

立即生效：

``` sh
sudo sysctl --system -a -p | grep yama
```