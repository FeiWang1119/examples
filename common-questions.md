# 在高分辨率下，图标变小的问题

## 分析

更改某个应用分辨率的环境变量：  

D_DXCB_DISABLE_OVERRIDE_HIDPI=1   
QT_SCALE_FACTOR=1.25

调用主题图标： 

``` c++
QIcon::fromeTheme("search")
qApp->setAttribute(Qt::AA_UseHighDpiPixmaps,  true);
```
流程：  
1. fromeTheme (...)   ==>  platformTheme->createIconEngine(...) 返回 DIconProxyEngine (qdeepin主题插件)

2.  DIconProxyEngine:paint(...) 转到  XdgIconProxyEngine:paint(...)