#ifndef MUTEX_H
#define MUTEX_H
#include <pthread.h>
namespace netlib
{
class Mutex
{
private:
    pthread_mutex_t mutex;
public:
    Mutex(){pthread_mutex_init(&mutex,NULL);}
    ~Mutex(){pthread_mutex_destroy(&mutex);}
    void lock(){ pthread_mutex_lock(&mutex);}
    void unlock(){ pthread_mutex_unlock(&mutex);}
};
}
#endif // MUTEX_H
