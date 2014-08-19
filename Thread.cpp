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

void netlib::threadfunction_glass_send(Glass* glass_home,Glass* glass_friend, Socket* client_socket,bool& end)
{
    for(;;)
    {
        if(glass_home->queue_send.size() != 0)
        {
          if(glass_home->queue_send.return_last() == "esc")
          {
              end = true;
              break;
          }

          char* data_send = new char[glass_home->queue_send.return_last().size()+1+1];
          for(int i = 0; i < glass_home->queue_send.return_last().size() ; i++)
              data_send[i] = glass_home->queue_send.return_last()[i];
          data_send[glass_home->queue_send.return_last().size()+1] = glass_home->return_figure()->return_figure_type()+'0';
          if (strncmp(data_send,"space",5) == 0)
            glass_friend->queue.add_front("space");
          client_socket->send(data_send,256);
          glass_home->queue_send.delete_back();
          delete[] data_send;
        }
    }
}


void netlib::threadfunction_read(int sockfd,char* data,int size,bool& end,Glass* glass_friend,Glass* glass_home)
{
    ssize_t bytes = 0;
    fd_set readsockets;
    timeval timeout;

    for( ; ; )
    {
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        FD_SET(sockfd,&readsockets);
        if (end )
        {
            std::cout<<"READ is Gonna end !"<<std::endl;
            break;
        }

        if(select(sockfd+1,&readsockets,NULL,NULL,&timeout)>0)
        {

            if (FD_ISSET(sockfd,&readsockets)>0)
            {
                bytes = recv(sockfd,data,256,0);
                if (bytes > 0 )
                {
                   //перевод сообщения
                   if(strncmp(data,"type",4) == 0 )
                   {
                       glass_friend->type_friend = (std::atoi(&data[4]));
                       std::cout<<"ATOI "<<glass_friend->type_friend<<std::endl;
                   }
                   if(strncmp(data,"space",5) == 0)
                   {
                      glass_friend->queue.add_front("space");
                      glass_home->queue.add_front("space");
                      //glass_friend->type_friend = (std::atoi(&data[6]));
                   }
                   if(strncmp(data,"esc",3) == 0)
                      glass_friend->queue.add_front("esc");
                   if(strncmp(data,"right",5) == 0)
                   {
                      glass_friend->queue.add_front("right");
                      //glass_friend->type_friend = (std::atoi(&data[6]));
                   }
                   if(strncmp(data,"left",4) == 0)
                   {
                      glass_friend->queue.add_front("left");
                      //glass_friend->type_friend = (std::atoi(&data[5]));
                   }
                   if(strncmp(data,"up",2) == 0)
                   {
                      glass_friend->queue.add_front("up");
                      //glass_friend->type_friend = (std::atoi(&data[3]));
                   }
                   if(strncmp(data,"down",4) == 0)
                   {
                      glass_friend->queue.add_front("down");
                      //glass_friend->type_friend = (std::atoi(&data[5]));
                   }
                   //std::cout<<data<<"\t"<<glass->queue.return_first()<<std::endl;
                }
                bytes = -1;
            }
        }
    }

}
