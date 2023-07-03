# Qt

|command|description|
|--|--|
-nograb -platformpluginpath /your/plugins | 指定平台插件
LANG=bo_CN LANGUAGE=bo_CN dde-file-manager |  藏语 (维语 ug_CN)
libqt5gui5-dbgsym libqt5widgets5-dbgsym libqt5core5a-dbgsym | 调试库
qtbase5-examples qt5-doc qt5-doc-html | 例子和帮助文档
qt5-default |  提供默认的 Qt5 开发库和工具
QT_SCALE_FACTOR | 缩放倍数
../configure -opensource -confirm-license  -nomake tests -nomake examples --sqlite=system --prefix=/home/fei/qt5.15  |  配置源码
libfontconfig1-dev libfreetype6-dev libx11-dev libx11-xcb-dev libxext-dev libxfixes-dev libxi-dev libxrender-dev libxcb1-dev libxcb-cursor-dev libxcb-glx0-dev libxcb-keysyms1-dev libxcb-image0-dev libxcb-shm0-dev libxcb-icccm4-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0-dev libxcb-util-dev libxcb-xinerama0-dev libxcb-xkb-dev libxkbcommon-dev libxkbcommon-x11-dev |  Qt for x11 requirements
libwayland-dev libwayland-egl1-mesa libwayland-server0 libgles2-mesa-dev libxkbcommon-dev |  Qt for QtWayland requirements

# qtcreator configure file

linux ：  
~/.config/QtProject  （测过）  
~/.local/share/data/QtProject/qtcreator  

window ：  
%APPDATA%\QtProject  
%LOCALAPPDATA%\QtProject  





