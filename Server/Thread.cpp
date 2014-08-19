#include "Thread.h"
#include "SocketStorage.h"
#include "SOCKET.h"
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include <netinet/in.h>
#include "SOCKET.h"
#include <pthread.h>
#include <signal.h>
#include "Glass.h"
#include "Glass_friend.h"
#include <iostream>

void netlib::threadfunction_read_send(SocketStorage* sockets,char* data,int size,bool &end)
{
    fd_set readsockets;
    fd_set errors;
    timeval timeout;
    ssize_t bytes = 0;


    for( ; ;)
    {
        if(end)
        {
            std::cout<<"READ&WRITE is Gonna end !"<<std::endl;
            for(int i = 0 ; i< sockets->return_size() ; i++)
                sockets->return_socket(i)->send("esc", sizeof("esc"));
            break;
        }
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        FD_ZERO(&readsockets);
        FD_ZERO(&errors);
        for(int i = 0 ; i< sockets->return_size() ; i++)
        {
            FD_SET(sockets->return_descriptor(i),&readsockets);
            FD_SET(sockets->return_descriptor(i),&errors);
        }

        if(select(sockets->return_max_descriptor()+1,&readsockets,NULL,&errors,&timeout)>0)
        {

            for(int i = 0 ; i< sockets->return_size() ; i++)
            {
                if (FD_ISSET(sockets->return_descriptor(i),&errors)>0)
                {
                    sockets->delete_(i);
                    std::cout<<"client #"<<i<<" left game with error"<<std::endl;
                    continue;
                }
                if (FD_ISSET(sockets->return_descriptor(i),&readsockets)>0)
                {
                    bytes = recv(sockets->return_descriptor(i),data,size,0);
                    if( bytes > 0 )
                    {
                        if( strncmp(data,"esc",3) == 0 )
                        {
                            sockets->delete_(i);
                            std::cout<<"client #"<<i<<" left game"<<std::endl;
                            bytes = 0;
                            break;
                        }
                        else
                        {
                            std::cout<<"client # "<<i<<"; message : "<<data<<std::endl;
                            /*if (strncmp(data,"space",5) == 0)
                            {
                                for(int j = 0; j < sockets->return_size() ; j++)
                                    sockets->return_socket(j)->send(data, 10);
                            }
                            else
                            {*/
                                for(int j = 0; j < sockets->return_size() ; j++)
                                {
                                    if( i == j ) continue;
                                    sockets->return_socket(j)->send(data, 10);
                                }
                            //}
                        }
                    }
                    if (bytes < 0)
                    {
                        sockets->delete_(i);
                        std::cout<<"client #!!!"<<i<<" left game "<<std::endl;
                    }
                    bytes = 0;

                }
            }
        }
    }
}

void netlib::threadfunction_listen(Socket* socket,SocketStorage* sockets,bool &end)
{
    timeval timeout;
    fd_set readsockets;
    FD_ZERO(&readsockets);

    for( ; ; )
    {
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        FD_SET(socket->return_sockfd(),&readsockets);

        if (end)
        {
            std::cout<<"Listen is Gonna end !"<<std::endl;
            break;
        }
                if ( socket->listen(2) == 0 )
                {
                    if(select(socket->return_sockfd()+1,&readsockets,NULL,NULL,&timeout) > 0)
                    {
                        sockets->add(socket->accept());
                        if(sockets->return_descriptor(sockets->return_size()-1) < 0)
                        {
                            std::cout<<"bad socket #"<<std::endl;
                            sockets->delete_(sockets->return_size()-1);
                        }

                    }
                }
    }
}
