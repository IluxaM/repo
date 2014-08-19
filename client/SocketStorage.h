#ifndef SOCKETSTORAGE_H
#define SOCKETSTORAGE_H

#include <vector>
#include "SOCKET.h"
#include "Mutex.h"

namespace netlib
{
using namespace std;
class SocketStorage
{
private:
    std::vector<Socket*> sockets;
    Mutex mutex;
public:
    void add(Socket* s);
    void delete_(int j);
    int return_descriptor(int i);
    int return_size(){ return sockets.size(); }
    int return_max_descriptor();
    Socket* return_socket(int i);
    ~SocketStorage();
};
}

#endif // SOCKETSTORAGE_H
