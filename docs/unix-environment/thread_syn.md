# 线程同步

当多个线程共享相同的内存时，需要确保每个线程看到一致的数据视图。

## 互斥量

互斥量本质上是一把锁，在访问共享资源前对互斥量进行设置（加锁），在访问完成后释放（解锁）互斥量。

初始化：

- PTHREAD_MUTEX_INITIALIZER (只适用于静态分配的互斥量)
- pthread_mutex_init函数

初始化和销毁：

```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int pthread_mutex_init(pthread_mutex_t *restrict mutex,
                       const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

加锁和解锁：

```c
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_timedlock(pthread_mutex_t *restrict mutex,
                            const struct timespec *restrict abstime);
```
pthread_mutex_timedlock 达到超时时间时, 不会对互斥量进行加锁而是返回错误玛 ETIMEDOUT

死锁两种情况：

 - 线程对同一个互斥量加锁两次
 - 两个线程相互请求另一个线程拥有的资源

 第二种死锁情况解决方法:

1. 控制加锁的顺序,总是以相同的顺序加锁
2. 使用pthread_mutex_trylock,返回成功可以前进，返回失败释放已经占有的锁,过一段时间再试

