# proxy

10.20.52.42  7890  
localhost, 127.0.0.0/8, ::1, *.org.deepin.org, *.uniontech.com, *.deepin.com  

proxy config：~/.ssh/config

``` sh
Host github.com
    Hostname github.com
    ProxyCommand /usr/bin/corkscrew 10.20.52.42 7890 %h %p
```
git config --global http.proxy 'http://127.0.0.1:7890'  
git config --global https.proxy 'https://127.0.0.1:7890'  
export http_proxy=https://127.0.0.1:7890/  

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
export https_proxy=https://127.0.0.1:7890/  
```

# Qt http passwd

iQbFdwc8jWo+w7FRzqM4SKRJu7+kg4JzmHmA78SM3g


# transifex

home 目录下 ：~/ .transifexrc

```c
[https://www.transifex.com]
rest_hostname = https://rest.api.transifex.com
api_hostname = https://api.transifex.com
hostname = https://www.transifex.com
token = ???

项目下： .tx/config

``` c
[main]
host = https://www.transifex.com
minimum_perc = 80
mode = developer

[o:linuxdeepin:p:deepin-desktop-environment:r:dde-calendar]
file_filter = translations/dde-calendar_<lang>.ts
source_file = translations/dde-calendar_en_US.ts
source_lang = en_US
type = QT

[o:linuxdeepin:p:deepin-desktop-environment:r:dde-calendar_desktop]
file_filter = translations/desktop/desktop_<lang>.ts
source_file = translations/desktop/desktop.ts
source_lang = en
type = QT

[o:linuxdeepin:p:deepin-desktop-environment:r:dde-calendar-service]
file_filter = translations/dde-calendar-service_<lang>.ts
source_file = translations/dde-calendar-service_en_US.ts
source_lang = en_US
type = QT
```

相关命令（tx --help）

| command                      | description              |
|------------------------------|--------------------------|
| apt install transifex-client | 安装tx                   |
| tx pull -t -a -s -b master   | 拉取翻译（-a -f 全部拉取） |
| tx push -s -b master         | 推送翻译                 |