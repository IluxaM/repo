#include "SocketStorage.h"
#include <vector>
#include "SOCKET.h"
#include "Mutex.h"
#include "Autolock.h"
using namespace std;
void netlib::SocketStorage::add(Socket* s)
{
    Autolock autolock(&mutex);
    sockets.push_back(s);
}

void netlib::SocketStorage::delete_(int j)
{
    Autolock autolock(&mutex);
    if( j == sockets.size()-1)
        sockets.pop_back();
    else
    {
        delete sockets[j];
        sockets[j] = sockets.back();
        sockets.pop_back();
    }
}
int netlib::SocketStorage::return_max_descriptor()
{
    Autolock autolock(&mutex);
    if( sockets.size() == 0 )
       return 0;
    int max_ = sockets[0]->return_sockfd();
    for(int i = 1 ; i < sockets.size() ; i++)
        max_ = max(max_, sockets[i]->return_sockfd());
    return max_;

}
netlib::SocketStorage::~SocketStorage()
{
    for (int i = 0 ; i < sockets.size() ; i++ )
        sockets[i]->~Socket();
}
netlib::Socket* netlib::SocketStorage::return_socket(int i)
{
    return sockets[i];
}
int netlib::SocketStorage::return_descriptor(int i)
{
    return sockets[i]->return_sockfd();
}
