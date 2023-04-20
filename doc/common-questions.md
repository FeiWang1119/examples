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
1. fromeTheme (...)   ==>  platformTheme->createIconEngine(...) 返回 DIconProxyEngine (qdeepin主题插件);
2.  DIconProxyEngine:paint(...) 转到  XdgIconProxyEngine:paint(...);
3.  rect(16*16), ratio = 1.25 , pixmap(20*20) when AA_UseHighDpiPixmaps=true;
4.   rect(16*16), ratio = 1, pixmap(16*16) when AA_UseHighDpiPixmaps=false;

原因:  
drawPixmap(rect,  pix)
rect和pix的大小不匹配 ，导致scale。

+++++ 1 QRect(32,14 16x16) QSize(16, 16)
+++++ 1 QRect(32,44 16x16) QSize(16, 16)
+++++ 1 QRect(32,76 16x16) QSize(16, 16)
+++++ 1 QRect(32,106 16x16) QSize(16, 16)
+++++ 1 QRect(32,136 16x16) QSize(16, 16)
+++++ 1 QRect(32,166 16x16) QSize(16, 16)
+++++ 1 QRect(32,198 16x16) QSize(16, 16)

 +++++ 2 QRect(48,6 32x32) QSize(64, 64)
 +++++ 2 QRect(48,36 32x32) QSize(64, 64)
 +++++ 2 QRect(48,68 32x32) QSize(64, 64)
 +++++ 2 QRect(48,98 32x32) QSize(64, 64)
 +++++ 2 QRect(48,128 32x32) QSize(64, 64)
 +++++ 2 QRect(48,158 32x32) QSize(64, 64)
 +++++ 2 QRect(48,190 32x32) QSize(64, 64)

+++++ 2 QRect(32,14 16x16) QSize(32, 32) QSize(32, 32)
+++++ 2 QRect(32,44 16x16) QSize(32, 32) QSize(32, 32)
+++++ 2 QRect(32,76 16x16) QSize(32, 32) QSize(32, 32)
+++++ 2 QRect(32,106 16x16) QSize(32, 32) QSize(32, 32)
+++++ 2 QRect(32,136 16x16) QSize(32, 32) QSize(32, 32)
+++++ 2 QRect(32,166 16x16) QSize(32, 32) QSize(32, 32)
+++++ 2 QRect(32,198 16x16) QSize(32, 32) QSize(32, 32)
# ssh 克隆仓库遇到 Permission denied (publickey).

1.  调试看信息：    

github:
```
 ssh -vt git@github.com  
```
gerrit:
```
 ssh -vv -p 29418 ut003691@gerrit.uniontech.com
```
 信息里出现：` send_pubkey_test: no mutual signature algorithm  `  
   由于各种安全漏洞，RSA SHA-1 哈希算法正迅速在操作系统和 SSH 客户端中被弃用，其中许多技术现在完全拒绝使用该算法。注意，默认情况下 Bitbucket 提供对 ECDSA 和 ED25519 算法的支持。 使用这些算法生成的密钥不受 RSA 弃用的影响。

   Resolutions:  
   
   1. Workaround for re-enabling RSA
   
   In order to re-enable ssh-rsa support, inserting the following line into the affected SSH client's config file can re-enable this algorithm:
   `PubkeyAcceptedKeyTypes +ssh-rsa`

   2. Resolution using ECDSA and ED25519 algorithms  
   
```
   ssh-keygen -t ed25519 -C "your_email@example.com"
```
more：

Verify that you have a private key generated and loaded into SSH.

```
ssh-add -l -E sha256
```

   [reference url]( https://confluence.atlassian.com/bitbucketserverkb/ssh-rsa-key-rejected-with-message-no-mutual-signature-algorithm-1026057701.html)