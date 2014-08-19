#include "Glass_friend.h"
void Glass_friend::activate_message()
{
    if(strncmp(queue.return_last(),"space",5) == 0)
    {
      active = !active;
      queue.delete_back();
      return;
    }
    if(strncmp(queue.return_last(),"right",5 ))
    {
        if(active && figure->ACTIVE())
        {
           PoM = true;
           figure->boundary(PoM,plane_);
        }
        queue.delete_back();
        return;
    }
    if(strncmp(queue.return_last(),"left",4))
    {
        if(active && figure->ACTIVE())
        {
           PoM = false;
           figure->boundary(PoM,plane_);
        }
         queue.delete_back();
        return;
    }
    if(strncmp(queue.return_last(),"up",2))
    {
        if(active)
           figure->change_type(plane_);
        queue.delete_back();
        return;
    }
    if(strncmp(queue.return_last(),"down",4))
    {
        if(active)
           figure->fall(plane_);
         queue.delete_back();
        return;
    }
   if(strncmp(queue.return_last(),"esc",3))
        done = true;
    /*
     if(message->space)
     {
       active = !active;
       message->space = false;
       return;
     }
     if(message->right)
     {
         if(active && figure->ACTIVE())
         {
            PoM = true;
            figure->boundary(PoM,plane_);
         }
         message->right = false;
         return;
     }
     if(message->left)
     {
         if(active && figure->ACTIVE())
         {
            PoM = false;
            figure->boundary(PoM,plane_);
         }
         message->left = false;
         return;
     }
     if(message->up)
     {
         if(active)
            figure->change_type(plane_);
         message->up = false;
         return;
     }
     if(message->down)
     {
         if(active)
            figure->fall(plane_);
         message->down = false;
         return;
     }
    if(message->esc)
         done = true;
         */
}

void Glass_friend::game()
{
 activate_message();
 if(done)
     exit(0);
 if(!figure->ACTIVE())
 {
        for(int j = 0 ; j < N ; j++)
             if(sumJ(j) == n)
             {
                 clearline_move(j);
                 j--;
             }
 }
 if(active)
 {
     if(!figure->ACTIVE())
     {
         if(sumJ(N-1) != 0 )
             done = true;
         else
         {
             type = rand() % 5 + 1 ;
             delete figure;
             figure = new Figure(type,n/2,N-1,plane_);
         }
     }
     figure->fall(plane_);
 }
 updateGL();
}
