#include "MyThread.h"
#include <iostream>
#include <pthread.h>

void* netlib::Thread::call_thread_function(void* thread)

{
    ( (Thread *)thread)->run_thread_function();
    pthread_exit(NULL);
    return NULL;
}

void netlib::Thread::start()
{
    int start;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); // это вроде дeфолтно выставляется
    start = pthread_create(&thread, &attr, Thread::call_thread_function, this);
    if( start != 0 )
        std::cout<<"can't create thread"<<std::endl;
}

void netlib::Thread::join()
{
    int join;
    std::cout<<"JOIN"<<std::endl;
    join = pthread_join(thread,NULL);

    if( join != 0 )
        std::cout<<"can't join thread"<<std::endl;
}

