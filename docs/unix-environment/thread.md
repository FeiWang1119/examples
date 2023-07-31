# ·线程概念

线程是系统运行的最小单位,是轻量级进程(LWP).
进程是系统分配资源的最小单位.

# 线程的好处

- 通过为每种事件类型分配单独的处理线程,可以简化处理异步事件的代码;
- 多个线程自动地可以访问相同的存储地址空间和文件描述符(进程复杂些);
- 有些问题可以分解从而提供整个程序的吞吐量;
- 交互的程序同样可以通过多线程来改善响应时间.

即使单处理器也能从多线程编程模型中获益,程序可以通过使用线程得以简化,并且在单处理器上运行还是可以改善响应时间和吞吐量.

每个线程包含执行环境所必需的信息:  
线程ID, 一组寄存器值,栈,调度优先级和策略,信号屏蔽字,errno变量以及线程私有数据.

线程之间共享的信息:  
一个进程所有信息对该进程的所有线程都是共享的,包括:可执行程序代码,程序的全局内存和堆内存,栈以及文件描述符.

## 线程标识

线程ID (pthread_t 结构)

int pthread_equal(pthread_t tid1, pthread_t tid2); // 比较两个线程ID是否相等:  

pthread_t pthread_self(void) // 获取线程ID

## 线程创建

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);

## 线程终止

单个线程可以通过三种方式退出:

1. 线程可以简单地从启动例程中返回,返回值是线程的退出码;
2. 线程可以被同一进程中的其他线程取消;
3. 线程调用pthread_exit.

void pthread_exit(void *retval);

int pthread_join(pthread_t thread, void **retval);
