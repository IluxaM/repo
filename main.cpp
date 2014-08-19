#include "mainwindow.h"
#include <QApplication>
#include <QtOpenGL>
#include "Glass.h"
#include <time.h>
#include "Figure.h"
#include <iostream>
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
#include <vector>
#include "Mutex.h"
#include "Autolock.h"
#include "Thread.h"
#include "SocketStorage.h"
#include "MyThread.h"

#include <qdialog.h>



using namespace std;

struct Client_ptr
{
    char* data;
    int data_size;
    int sockfd;
    bool end;
    netlib::Socket* socket;
    Client_ptr(char* data_1,int data_size_1,int sockfd_1,netlib::Socket* socket_1)
    {
        data = data_1;
        data_size = data_size_1;
        sockfd = sockfd_1;
        end = false;
        socket = socket_1;
    }
};
struct Glass_plus_client
{
    Client_ptr* client_ptr_ptr;
    Glass* glass_home_ptr;
    Glass* glass_friend_ptr;
    Glass_plus_client(Glass* glass_home_ptr_1,Glass* glass_friend_ptr_1,Client_ptr* client_ptr_ptr_1)
    {
        glass_home_ptr = glass_home_ptr_1;
        glass_friend_ptr = glass_friend_ptr_1;
        client_ptr_ptr = client_ptr_ptr_1;
    }
};


namespace netlib
{
    class Thread_read : public Thread
    {
    public:
        Glass_plus_client* glass_plus_client_ptr;
        Thread_read(Glass_plus_client* glass_plus_client_ptr_1):Thread()
        {
            glass_plus_client_ptr = glass_plus_client_ptr_1;
        }
        void run_thread_function()
        {
            threadfunction_read(glass_plus_client_ptr->client_ptr_ptr->sockfd,
                                glass_plus_client_ptr->client_ptr_ptr->data,
                                glass_plus_client_ptr->client_ptr_ptr->data_size,
                                glass_plus_client_ptr->client_ptr_ptr->end,
                                glass_plus_client_ptr->glass_friend_ptr,
                                glass_plus_client_ptr->glass_home_ptr
                                );
            std::cout<<"Thread_read ended"<<std::endl;
        }
    };
   class Thread_queue : public Thread
    {
    public:
        Glass* glass;
        Thread_queue(Glass* glass_1):Thread()
        {
            glass = glass_1;
        }
        void run_thread_function()
        {
            for( ; ; )
                glass->activate_message();
             std::cout<<"Thread_message ended"<<std::endl;
        }
    };
    class Thread_send : public Thread
    {
    public:
        Glass_plus_client* glass_plus_client_ptr;
        Thread_send(Glass_plus_client* glass_plus_client_ptr_1):Thread()
        {
            glass_plus_client_ptr = glass_plus_client_ptr_1;
        }
        void run_thread_function()
        {
            threadfunction_glass_send(glass_plus_client_ptr->glass_home_ptr,
                                      glass_plus_client_ptr->glass_friend_ptr,
                                      glass_plus_client_ptr->client_ptr_ptr->socket,
                                      glass_plus_client_ptr->client_ptr_ptr->end);
            std::cout<<"Thread_send ended"<<std::endl;
        }
    };

}


int main(int argc, char *argv[])
{       
        QApplication app(argc, argv);
        //bool end = false;
        char data_recv[256];
        //char data_send[256];
       // Message* message = new Message;
        netlib::Socket client_socket;
        netlib::Addres addres;
        addres.init(argc, argv,false);

        client_socket.init(addres);
        client_socket.connect();

        Glass* glass_home = new Glass; // окно дом
        Glass* glass_friend = new Glass; //окно друг
        glass_friend->set_friend_window();

        Client_ptr* client_sock_ptr = new Client_ptr(data_recv,sizeof(data_recv),client_socket.return_sockfd(),&client_socket);
        Glass_plus_client* glass_plus_home_friend_ptr = new Glass_plus_client(glass_home,glass_friend,client_sock_ptr);
        //Glass_plus_client* glass_plus_client_ptr = new Glass_plus_client(glass_home,client_sock_ptr);


        // новая часть

        QMessageBox* pmbx =
                            new QMessageBox("MessageBox",
                            "Do you want left keyboard?",
                            QMessageBox::Information,
                            QMessageBox::Yes,
                            QMessageBox::No,
                            QMessageBox::Cancel | QMessageBox::Escape);
        int n = pmbx->exec();
        delete pmbx;
        if (n == QMessageBox::Yes)
          glass_home->switch_keyboard();


        //

        netlib::Thread_read client_read = netlib::Thread_read(glass_plus_home_friend_ptr); // read
        client_read.start();

       // glass_home->switch_activity();

        netlib::Thread_send client_send = netlib::Thread_send(glass_plus_home_friend_ptr); // send
        client_send.start();

        netlib::Thread_queue thread_queue_friend = netlib::Thread_queue(glass_friend);
        thread_queue_friend.start(); // поток на чтение


        netlib::Thread_queue thread_queue_home = netlib::Thread_queue(glass_home);
        thread_queue_home.start(); // поток на запись команд

        glass_friend->setWindowTitle(QObject::tr("Tetris Friend"));
        glass_friend->resize(400, 300);
        glass_friend->show();


        QPoint point = glass_friend->mapToGlobal(QPoint(0,0));

        glass_home->setWindowTitle(QObject::tr("Tetris Home"));
        glass_home->resize(400, 300);
        glass_home->move(point.x()+300,point.y());
        glass_friend->move(point.x()-300,point.y());
        glass_home->show();

    /*
        for( ; ; )
        {
            if (strncmp(data_recv,"esc",strlen("esc")) == 0 )
            {
                client_sock_ptr->end = true;
             //   client_read.join();
                break;
            }
            if(end)
            {
                client_sock_ptr->end = true;
            //    client_read.join();
            }
        }
     */
        return app.exec();
}
