#include "mainwindow.h"
#include <QApplication>
#include<iostream>
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
#include "Mutex.h"
#include "SocketStorage.h"
#include "Thread.h"
#include "MyThread.h"


using namespace std;
namespace netlib
{
struct Socketsptrs
{
    SocketStorage* sockets_ptr;
    Socket* client_ptr;
    char* data_ptr;
    int data_size;
    bool end;
    Socketsptrs(SocketStorage* sockets_ptr_2,Socket* client_ptr_2,char* data_ptr_2,int data_size_2)
    {
        sockets_ptr = sockets_ptr_2;
        client_ptr = client_ptr_2;
        data_ptr = data_ptr_2;
        data_size = data_size_2;
        end = false;
    }

};

class Thread_listen : public Thread
{
public:
    Socketsptrs* server_sock;
    Thread_listen(Socketsptrs* server_sock_1):Thread()
    {
        server_sock = server_sock_1;
    }
    void run_thread_function()
    {
        threadfunction_listen(server_sock->client_ptr,server_sock->sockets_ptr,server_sock->end);
        cout<<"Thread_Listen ended"<<endl;

    }

};

class Thread_read_send : public Thread
{
public:
    Socketsptrs* server_sock;
    Thread_read_send(Socketsptrs* server_sock_1):Thread()
    {
        server_sock = server_sock_1;
    }
    void run_thread_function()
    {
        threadfunction_read_send(server_sock->sockets_ptr,server_sock->data_ptr,server_sock->data_size,server_sock->end);
        cout<<"ThreadRead_Send ended"<<endl;
    }
};
}

int main(int argc, char * argv[])
{

    string _exit;
    char data_recv[256];
    netlib::SocketStorage sockets;
    netlib::Socket clientsocket;
    netlib::Addres addres;
    addres.init(argc, argv,true);

    clientsocket.init(addres);

     if(clientsocket.return_sockfd()<0)
     {
        cout<<"socket error"<<endl;
        exit(1);
     }
     clientsocket.bind();

    netlib::Socketsptrs* sockets_ptrs = new netlib::Socketsptrs(&sockets,&clientsocket,data_recv,sizeof(data_recv));
    netlib::Thread_listen listen = netlib::Thread_listen(sockets_ptrs);
     listen.start();
    netlib::Thread_read_send read_send = netlib::Thread_read_send(sockets_ptrs);
     read_send.start();
     for( ; ; )
     {

         //cin>>_exit;
         //cout<<exit;
 /*        if( _exit == "!users")
             cout<<"There are "<<sockets.return_size()<<" users on the server"<<endl;
         if( _exit == "!usersD")

             for(int i = 0; i < sockets.return_size() ; i++)
                 cout<<"descriptor : "<<sockets.return_descriptor(i)<<endl;
         if( _exit == "!exit" )
         {
             sockets_ptrs->end = true;
             listen.join();
             read_send.join();
             break;
         }*/
     }
     return 0;
}

