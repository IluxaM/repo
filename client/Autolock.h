#ifndef AUTOLOCK_H
#define AUTOLOCK_H

#include "Mutex.h"
namespace netlib{
class Autolock
{
private:
    netlib::Mutex* mutex;
public:
    Autolock(netlib::Mutex* _mutex){mutex = _mutex ; mutex->lock();}
    ~Autolock(){mutex->unlock();}
};
}




#endif // AUTOLOCK_H
