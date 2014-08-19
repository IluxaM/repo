#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <iostream>
#include <pthread.h>
namespace netlib
{
class Thread
{
private:
    pthread_t thread;
    pthread_attr_t attr;
public:
    Thread(){}
    static void* call_thread_function(void* thread);
    void start();
    void join();
    virtual void run_thread_function() = 0;
    void cancel(){std::cout<<"Thread Canceled"<<std::endl; pthread_cancel(thread);}
    ~Thread(){}
};
}
#endif // MYTHREAD_H
