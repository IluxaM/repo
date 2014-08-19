#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include "SocketStorage.h"
#include "SOCKET.h"
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <netinet/in.h>
#include "SOCKET.h"
#include <pthread.h>
#include "Glass.h"
#include "Glass_friend.h"

namespace netlib
{
void threadfunction_read_send(SocketStorage* Sockets,char* data,int size,bool &end);
//void threadfunction_read(int sockfd,char* data,int size,bool& end);
void threadfunction_read(int sockfd,char* data,int size,bool& end,Glass* glass_home,Glass* glass_friend);
void threadfunction_listen(Socket* S,SocketStorage* Sockets,bool &end);
void threadfunction_glass(Glass* glass);
void threadfunction_glass_send(Glass* glass_home,Glass* glass_friend, Socket* client_socket,bool& end);
void threadfunction_glass_friend(Glass_friend* glass);
}
#endif // THREAD_H
