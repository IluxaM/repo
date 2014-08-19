#include "SOCKET.h"
#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <netinet/in.h>


using namespace std;
void netlib::Addres::init(int argc,  char **argv,bool serv_1)
{
    serv = serv_1;
    if (serv)
    {
        if (argc == 2)
            port = atoi(argv[1]);
        else
            port = 3445;
    }
    else
    {
        if( argc > 2 )
        {
            port = atoi(argv[1]);
            ip = argv[2];
            loopback = false;
            return;
        }
        if (argc == 2)
        {
            cout<<"IP doen't matched, you will be connect to LOOPBACK"<<endl;
            loopback = true;
            return;
        }
        port = 3445;
        loopback = true;
    }
}

void netlib::Socket::change_port(int sock)
{
    sockfd_ = sock;
    if( sockfd_ < 0 )
    {
        cout<<"invalid change of socket, sockfd = "<<sockfd_<<endl;

        exit(1);
    }
}

netlib::Socket::Socket()
{
    sockfd_ = -1;
}

netlib::Socket::Socket(int sockfd,struct sockaddr_in echo,bool server)
{
    sockfd_ = sockfd;
    if( sockfd_ < 0 )
    {
        cout<<"invalid socket, sockfd ="<<sockfd_<<endl;
        exit(1);
    }
    echo_ = echo;
    server_ = server;
}

void netlib::Socket::init(Addres addres)
{
    sockfd_ = socket(AF_INET,SOCK_STREAM,0);
    if( sockfd_ < 0 )
    {
        cout<<"invalid socket, sockfd ="<<sockfd_<<endl;
        exit(1);
    }
    server_ = addres.serv;
        if(server_)
        {
            echo_.sin_family = AF_INET;
            echo_.sin_port = htons(addres.port);
            if ( addres.port<=0)
            {
                cout<<"invalid port, port = "<<addres.port<<endl;
                exit(2);

            }
            echo_.sin_addr.s_addr= htonl(INADDR_ANY);
        }
        else
        {
            echo_.sin_family = AF_INET;
            echo_.sin_port = htons(addres.port);
            if ( addres.port<=0)
            {
                cout<<"invalid port, port = "<<addres.port<<endl;
                exit(2);

            }
            if( addres.loopback )
                echo_.sin_addr.s_addr= htonl(INADDR_LOOPBACK);
            else
                echo_.sin_addr.s_addr=inet_addr(addres.ip);
        }


}

void netlib::Socket::bind()
{
    int bind = ::bind(sockfd_, (struct sockaddr *)&echo_, sizeof(echo_));
    if (bind < 0)
    {
        cout<<"can't bind port"<<endl;
        exit(3);
    }
}

int netlib::Socket::return_sockfd()
{
    return sockfd_;
}

netlib::Socket* netlib::Socket::accept()
{
    int sock = ::accept(sockfd_,NULL,NULL);
    if ( sock<0)
    {
        cout<<"accept error"<<endl;
        exit(4);
    }
    struct sockaddr_in echo_1 = echo_;
    return new Socket(sock,echo_1,1);
}

void netlib::Socket::send(char* data,int size)
{
    int Send = ::send(sockfd_,data,size,0);
    if ( Send < 0 )
    {
        cout<<"send error"<<endl;
        exit(5);
    }
}

int netlib::Socket::listen(int queue)
{
    int listen_ = ::listen(sockfd_,queue);
    if ( listen_ < 0 )
    {
        cout<<"listen error"<<endl;
        exit(8);
    }
    return listen_;
}

netlib::Socket::~Socket()
{
    int close_ = close(sockfd_);
    if (close_ < 0)
    {
        cout<<"can't close socket"<<endl;
        cout<<close_<<endl;
        exit(6);
    }
    cout<<"Socket #"<<sockfd_<<" was deleted"<<endl;

}

void netlib::Socket::connect()
{
    int connect_ = ::connect(sockfd_,(struct sockaddr *)&echo_,sizeof(echo_));
    if( connect_ < 0 )
    {
        cout<<"connect error"<<endl;
        exit(7);
    }
}
