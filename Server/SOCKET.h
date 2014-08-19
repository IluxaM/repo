#ifndef SOCKET_H
#define SOCKET_H

#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <netinet/in.h>

namespace netlib
{
struct Addres
{
    int port;
    //const char* ip;
    char* ip;
    bool serv;
    bool loopback;
    //void init(int argc, const char **argv,bool Serv);
    void init(int argc, char **argv,bool Serv);
};

class Socket
{
private:
    int sockfd_;
    struct sockaddr_in echo_;
    bool server_;
public:
    void init(Addres addres);
    Socket();
    Socket(int sock,struct sockaddr_in echo_1,bool serv);
    void bind();
    Socket* accept();
    void change_port(int sock);
    void send(char* data,int size);
    void recv(char* data, int size);
    int return_sockfd();
    void connect();
    int listen(int queue);
    ~Socket();
};
}

#endif // SOCKET_H
