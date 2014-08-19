#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <list>
#include <iostream>
#include "Mutex.h"
#include "Autolock.h"

using namespace std;

class Queue
{
private:
    list<string> queue;
    netlib::Mutex mutex;
public:
    int size(){ //netlib::Autolock autolock(&mutex);
        return queue.size();}
    //void add_back(string word){ netlib::Autolock autolock(&mutex); queue.push_back(word); }
    //void add_front(string word){ netlib::Autolock autolock(&mutex); queue.push_front(word); }
    void add_back(string word){ netlib::Autolock autolock(&mutex); queue.push_back(word); }
    void add_front(string word){ netlib::Autolock autolock(&mutex); queue.push_front(word); }
    void delete_back(){ netlib::Autolock autolock(&mutex); queue.pop_back(); }
    void delete_front(){ netlib::Autolock autolock(&mutex); queue.pop_front(); }
    //string return_last_and_del(){ string word = *(queue.end()) ; delete_back(); return word;}
    //string return_last(){return *(queue.end()) ; }
    string return_last(){netlib::Autolock autolock(&mutex);return *(--queue.end()) ; }
    string return_first(){netlib::Autolock autolock(&mutex);return *(queue.begin()) ; }
    bool empty_queue(){ netlib::Autolock autolock(&mutex);return queue.empty();}
    void clear_queue(){ netlib::Autolock autolock(&mutex); queue.clear();}
};

#endif // QUEUE_H
