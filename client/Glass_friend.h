#ifndef GLASS_FRIEND_H
#define GLASS_FRIEND_H

#include "Glass.h"
#include <string>
/*struct Message
{
    bool space;
    bool left;
    bool right;
    bool esc;
    bool up;
    bool down;
    Message()
    {
        space = false;
        left = false;
        right =false;
        esc = false;
        up = false;
        down = false;
    }
    void read(string data_recv)
    {
        if(data_recv == "esc") esc = true;
        if(data_recv == "space") space = true;
        if(data_recv == "left") left = true;
        if(data_recv == "right") right = true;
        if(data_recv == "up") up = true;
        if(data_recv == "down") down = true;
    }
};*/

class Glass_friend: public Glass//,QGLWidget
{
   //Q_OBJECT
   //Message message;
   void activate_message();
  // Message* message;
   public slots:
        void game();
};

#endif // GLASS_FRIEND_H

