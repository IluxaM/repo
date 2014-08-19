#include "Figure.h"
#include <time.h>


int n = 16;
int N = 24;
void Figure::boundary(bool PoM,Plane plane_)
 {
    if(PoM)
    {
        free_figure(plane_);
        I++;


        if(type == 1 )
            if(I >= n-1 ) I=n-1;
        if( (type == 2) || (type == 6)||(type == 4) ||(type == 5) )
            if(I+1 >= n-1 ) I = n-2;
        if( (type == 8)|| (type == 12) )
            if(I >= n-1 ) I = n-1;
        if( (type == 7) || (type == 11) )
            if(I+1 >= n-1 ) I = n-2;
        if(type == 3)
            if(I+1> n-1) I = n-1;
        if( type == 9)
            if(I+2>n-1) I = n - 3;
        if (figure(plane_)) I--;
        bind_figure(plane_);
    }
    else
    {
        free_figure(plane_);
        I--;
        if(type == 1 )
            if(I-1 <= 0 ) I = 1;
        if( (type == 2) || (type == 6) ||(type == 4) ||(type == 5) )
            if(I-1 <= 0 ) I = 1;
        if( (type == 8)|| (type == 12) )
            if(I-1 <= 0 ) I = 1;
        if( (type == 7)|| (type == 11) )
            if(I <= 0 ) I = 0;
        if(type == 3)
            if(I<0) I=0;
        if(type == 9)
            if(I-1<0) I = 1;
        if (figure(plane_)) I++;
        bind_figure(plane_);
    }


 }
Figure::Figure(int TYPE, int i, int j,Plane plane_)
{
    type = TYPE;
    active = true;
    color = rand() % 3 + 0;
    I = i;
    J = j;
     if( type == 1 )
     {
         plane_.plane[I][J] = true;
         plane_.plane[I-1][J] = true;
         plane_.plane[I][J-1] = true;
         plane_.plane[I-1][J-1] = true;
         plane_.color[I][J] = color;
         plane_.color[I-1][J] = color;
         plane_.color[I][J-1] = color;
         plane_.color[I-1][J-1] = color;
     }
     if( type == 2)
     {
         plane_.plane[I][J] = true;
         plane_.plane[I-1][J] = true;
         plane_.plane[I+1][J] = true;
         plane_.plane[I][J-1] = true;
         plane_.color[I][J] = color;
         plane_.color[I-1][J] = color;
         plane_.color[I+1][J] = color;
         plane_.color[I][J-1] = color;

     }
     if( type == 6)
     {
         plane_.plane[I][J] = true;
         plane_.plane[I-1][J-1] = true;
         plane_.plane[I+1][J-1] = true;
         plane_.plane[I][J-1] = true;
         plane_.color[I][J] = color;
         plane_.color[I-1][J-1] = color;
         plane_.color[I+1][J-1] = color;
         plane_.color[I][J-1] = color;
     }
     if( type == 7)
     {
         plane_.plane[I][J] = true;
         plane_.plane[I][J-1] = true;
         plane_.plane[I][J-2] = true;
         plane_.plane[I+1][J-1] = true;
         plane_.color[I][J] = color;
         plane_.color[I][J-1] = color;
         plane_.color[I][J-2] = color;
         plane_.color[I+1][J-1] = color;
     }
     if( type == 8)
     {
         plane_.plane[I][J] = true;
         plane_.plane[I-1][J-1] = true;
         plane_.plane[I][J-1] = true;
         plane_.plane[I][J-2] = true;
         plane_.color[I][J] = color;
         plane_.color[I-1][J-1] = color;
         plane_.color[I][J-1] = color;
         plane_.color[I][J-2] = color;
     }
     if(type == 3)
     {
         plane_.plane[I][J] = true;
         plane_.plane[I][J-1] = true;
         plane_.plane[I][J-2] = true;
         plane_.plane[I][J-3] = true;
         plane_.color[I][J] = color;
         plane_.color[I][J-1] = color;
         plane_.color[I][J-2] = color;
         plane_.color[I][J-3] = color;
     }
     if(type == 9)
     {
         plane_.plane[I][J] = true;
         plane_.plane[I-1][J] = true;
         plane_.plane[I+1][J] = true;
         plane_.plane[I+2][J] = true;
         plane_.color[I][J] = color;
         plane_.color[I-1][J] = color;
         plane_.color[I+1][J] = color;
         plane_.color[I+2][J] = color;
     }
     if(type == 4)
     {
         plane_.plane[I][J] = true;
         plane_.plane[I-1][J] = true;
         plane_.plane[I][J-1] = true;
         plane_.plane[I+1][J-1] = true;
         plane_.color[I][J] = color;
         plane_.color[I-1][J] = color;
         plane_.color[I][J-1] = color;
         plane_.color[I+1][J-1] = color;
     }
     if(type == 5)
     {
         plane_.plane[I][J] = true;
         plane_.plane[I+1][J] = true;
         plane_.plane[I][J-1] = true;
         plane_.plane[I-1][J-1] = true;
         plane_.color[I][J] = color;
         plane_.color[I+1][J] = color;
         plane_.color[I][J-1] = color;
         plane_.color[I-1][J-1] = color;
     }
     if(type == 11)
     {
         plane_.plane[I][J] = true;
         plane_.plane[I][J-1] = true;
         plane_.plane[I+1][J-1] = true;
         plane_.plane[I+1][J-2] = true;
         plane_.color[I][J] = color;
         plane_.color[I][J-1] = color;
         plane_.color[I+1][J-1] = color;
         plane_.color[I+1][J-2] = color;
     }

     if(type == 12)
     {
         plane_.plane[I][J] = true;
         plane_.plane[I][J-1] = true;
         plane_.plane[I-1][J-1] = true;
         plane_.plane[I-1][J-2] = true;
         plane_.color[I][J] = color;
         plane_.color[I][J-1] = color;
         plane_.color[I-1][J-1] = color;
         plane_.color[I-1][J-2] = color;
     }
}
bool Figure::END()
{
    if( (type == 1 ) || (type == 2) || (type == 6)||(type == 4) || (type == 5))
        if ( J == 1)
            return true;
    if( (type == 7) || (type == 8)||(type == 11)||(type == 12))
         if ( J == 2)
             return true;
    if(type == 3)
        if (J == 3)
            return true;
    if(type == 9)
        if (J == 0 )
            return true;
    return false;

}
bool Figure::figure(Plane plane_)
{
     int sum = 0;
     if( type == 1 )
        sum = plane_.plane[I][J-1]+plane_.plane[I-1][J-1]+plane_.plane[I][J]+plane_.plane[I-1][J];
     if(type == 2)
        sum =plane_.plane[I-1][J]+plane_.plane[I+1][J]+plane_.plane[I][J-1]+plane_.plane[I][J];
      if( type == 6)
        sum = plane_.plane[I-1][J-1] + plane_.plane[I+1][J-1] + plane_.plane[I][J-1] + plane_.plane[I][J];
     if( type == 7)
        sum = plane_.plane[I][J-2] + plane_.plane[I+1][J-1] + plane_.plane[I][J] + plane_.plane[I][J-1];
     if( type == 8)
        sum = plane_.plane[I][J-2] + plane_.plane[I-1][J-1] + plane_.plane[I][J] + plane_.plane[I][J-1];
     if( type == 3)
         sum = plane_.plane[I][J] + plane_.plane[I][J-1] + plane_.plane[I][J-2] + plane_.plane[I][J-3];
     if(type == 9)
         sum = plane_.plane[I][J] + plane_.plane[I-1][J] + plane_.plane[I+1][J] + plane_.plane[I+2][J];
     if(type == 4)
         sum = plane_.plane[I][J] + plane_.plane[I-1][J] + plane_.plane[I][J-1] + plane_.plane[I+1][J-1];
     if(type == 5)
         sum = plane_.plane[I][J] + plane_.plane[I+1][J] + plane_.plane[I-1][J-1] + plane_.plane[I][J-1];
     if(type == 11)
         sum = plane_.plane[I][J] + plane_.plane[I][J-1] + plane_.plane[I+1][J-1] + plane_.plane[I+1][J-2];
     if(type == 12)
         sum = plane_.plane[I][J] + plane_.plane[I-1][J-1] + plane_.plane[I][J-1] + plane_.plane[I-1][J-2];
     if ( sum == 0 )
         return false;
     return true;
 }
void Figure::bind_figure(Plane plane_)
{
    if( type == 1 )
    {
        plane_.plane[I][J] = true;
        plane_.plane[I-1][J] = true;
        plane_.plane[I][J-1] = true;
        plane_.plane[I-1][J-1] = true;
        plane_.color[I][J] = color;
        plane_.color[I-1][J] = color;
        plane_.color[I][J-1] = color;
        plane_.color[I-1][J-1] = color;
    }
    if( type == 2)
    {
        plane_.plane[I][J] = true;
        plane_.plane[I-1][J] = true;
        plane_.plane[I+1][J] = true;
        plane_.plane[I][J-1] = true;
        plane_.color[I][J] = color;
        plane_.color[I-1][J] = color;
        plane_.color[I+1][J] = color;
        plane_.color[I][J-1] = color;

    }
    if( type == 6)
    {
        plane_.plane[I][J] = true;
        plane_.plane[I-1][J-1] = true;
        plane_.plane[I+1][J-1] = true;
        plane_.plane[I][J-1] = true;
        plane_.color[I][J] = color;
        plane_.color[I-1][J-1] = color;
        plane_.color[I+1][J-1] = color;
        plane_.color[I][J-1] = color;
    }
    if( type == 7)
    {
        plane_.plane[I][J] = true;
        plane_.plane[I][J-1] = true;
        plane_.plane[I][J-2] = true;
        plane_.plane[I+1][J-1] = true;
        plane_.color[I][J] = color;
        plane_.color[I][J-1] = color;
        plane_.color[I][J-2] = color;
        plane_.color[I+1][J-1] = color;
    }
    if( type == 8)
    {
        plane_.plane[I][J] = true;
        plane_.plane[I-1][J-1] = true;
        plane_.plane[I][J-1] = true;
        plane_.plane[I][J-2] = true;
        plane_.color[I][J] = color;
        plane_.color[I-1][J-1] = color;
        plane_.color[I][J-1] = color;
        plane_.color[I][J-2] = color;
    }
    if(type == 3)
    {
        plane_.plane[I][J] = true;
        plane_.plane[I][J-1] = true;
        plane_.plane[I][J-2] = true;
        plane_.plane[I][J-3] = true;
        plane_.color[I][J] = color;
        plane_.color[I][J-1] = color;
        plane_.color[I][J-2] = color;
        plane_.color[I][J-3] = color;
    }
    if(type == 9)
    {
        plane_.plane[I][J] = true;
        plane_.plane[I-1][J] = true;
        plane_.plane[I+1][J] = true;
        plane_.plane[I+2][J] = true;
        plane_.color[I][J] = color;
        plane_.color[I-1][J] = color;
        plane_.color[I+1][J] = color;
        plane_.color[I+2][J] = color;
    }
    if(type == 4)
    {
        plane_.plane[I][J] = true;
        plane_.plane[I-1][J] = true;
        plane_.plane[I][J-1] = true;
        plane_.plane[I+1][J-1] = true;
        plane_.color[I][J] = color;
        plane_.color[I-1][J] = color;
        plane_.color[I][J-1] = color;
        plane_.color[I+1][J-1] = color;
    }
    if(type == 5)
    {
        plane_.plane[I][J] = true;
        plane_.plane[I+1][J] = true;
        plane_.plane[I][J-1] = true;
        plane_.plane[I-1][J-1] = true;
        plane_.color[I][J] = color;
        plane_.color[I+1][J] = color;
        plane_.color[I][J-1] = color;
        plane_.color[I-1][J-1] = color;
    }
    if(type == 11)
    {
        plane_.plane[I][J] = true;
        plane_.plane[I][J-1] = true;
        plane_.plane[I+1][J-1] = true;
        plane_.plane[I+1][J-2] = true;
        plane_.color[I][J] = color;
        plane_.color[I][J-1] = color;
        plane_.color[I+1][J-1] = color;
        plane_.color[I+1][J-2] = color;
    }

    if(type == 12)
    {
        plane_.plane[I][J] = true;
        plane_.plane[I][J-1] = true;
        plane_.plane[I-1][J-1] = true;
        plane_.plane[I-1][J-2] = true;
        plane_.color[I][J] = color;
        plane_.color[I][J-1] = color;
        plane_.color[I-1][J-1] = color;
        plane_.color[I-1][J-2] = color;
    }
}
void Figure::free_figure(Plane plane_)
{
    if( type == 1 )
    {
        plane_.plane[I][J] = false;
        plane_.plane[I-1][J] = false;
        plane_.plane[I][J-1] = false;
        plane_.plane[I-1][J-1] = false;
        plane_.color[I][J] = 0;
        plane_.color[I-1][J] = 0;
        plane_.color[I][J-1] = 0;
        plane_.color[I-1][J-1] = 0;
    }
    if( type == 2)
    {
        plane_.plane[I][J] = false;
        plane_.plane[I-1][J] = false;
        plane_.plane[I+1][J] = false;
        plane_.plane[I][J-1] = false;
        plane_.color[I][J] = 0;
        plane_.color[I-1][J] = 0;
        plane_.color[I+1][J] = 0;
        plane_.color[I][J-1] = 0;

    }
    if( type == 6)
    {
        plane_.plane[I][J] = false;
        plane_.plane[I-1][J-1] = false;
        plane_.plane[I+1][J-1] = false;
        plane_.plane[I][J-1] = false;
        plane_.color[I][J] = 0;
        plane_.color[I-1][J-1] = 0;
        plane_.color[I+1][J-1] = 0;
        plane_.color[I][J-1] = 0;
    }
    if( type == 7)
    {
        plane_.plane[I][J] = false;
        plane_.plane[I][J-1] = false;
        plane_.plane[I][J-2] = false;
        plane_.plane[I+1][J-1] = false;
        plane_.color[I][J] = 0;
        plane_.color[I][J-1] = 0;
        plane_.color[I][J-2] = 0;
        plane_.color[I+1][J-1] = 0;
    }
    if( type == 8)
    {
        plane_.plane[I][J] = false;
        plane_.plane[I-1][J-1] = false;
        plane_.plane[I][J-1] = false;
        plane_.plane[I][J-2] = false;
        plane_.color[I][J] = 0;
        plane_.color[I-1][J-1] = 0;
        plane_.color[I][J-1] = 0;
        plane_.color[I][J-2] = 0;
    }
    if(type == 3)
    {
        plane_.plane[I][J] = false;
        plane_.plane[I][J-1] = false;
        plane_.plane[I][J-2] = false;
        plane_.plane[I][J-3] = false;
        plane_.color[I][J] = 0;
        plane_.color[I][J-1] = 0;
        plane_.color[I][J-2] = 0;
        plane_.color[I][J-3] = 0;
    }
    if(type == 9)
    {
        plane_.plane[I][J] = false;
        plane_.plane[I-1][J] = false;
        plane_.plane[I+1][J] = false;
        plane_.plane[I+2][J] = false;
        plane_.color[I][J] = 0;
        plane_.color[I-1][J] = 0;
        plane_.color[I+1][J] = 0;
        plane_.color[I+2][J] = 0;
    }
    if(type == 4)
    {
        plane_.plane[I][J] = false;
        plane_.plane[I-1][J] = false;
        plane_.plane[I][J-1] = false;
        plane_.plane[I+1][J-1] = false;
        plane_.color[I][J] = 0;
        plane_.color[I-1][J] = 0;
        plane_.color[I][J-1] = 0;
        plane_.color[I+1][J-1] = 0;
    }
    if(type == 5)
    {
        plane_.plane[I][J] = false;
        plane_.plane[I+1][J] = false;
        plane_.plane[I][J-1] = false;
        plane_.plane[I-1][J-1] = false;
        plane_.color[I][J] = 0;
        plane_.color[I+1][J] = 0;
        plane_.color[I][J-1] = 0;
        plane_.color[I-1][J-1] = 0;
    }
    if(type == 11)
    {
        plane_.plane[I][J] = false;
        plane_.plane[I][J-1] = false;
        plane_.plane[I+1][J-1] = false;
        plane_.plane[I+1][J-2] = false;
        plane_.color[I][J] = 0;
        plane_.color[I][J-1] = 0;
        plane_.color[I+1][J-1] = 0;
        plane_.color[I+1][J-2] = 0;
    }

    if(type == 12)
    {
        plane_.plane[I][J] = false;
        plane_.plane[I][J-1] = false;
        plane_.plane[I-1][J-1] = false;
        plane_.plane[I-1][J-2] = false;
        plane_.color[I][J] = 0;
        plane_.color[I][J-1] = 0;
        plane_.color[I-1][J-1] = 0;
        plane_.color[I-1][J-2] = 0;
    }
 }
void Figure::fall(Plane plane_)
{

    if(END()){active = false; return;}
    free_figure(plane_);
    J--;
    if(!figure(plane_)){bind_figure(plane_);}
    else {J++; bind_figure(plane_);active = false;}


}
void Figure::change_type(Plane plane_)
{
    if(type == 1 )
        return;
    if(type == 2)
    {
        free_figure(plane_);
        type = 7;
        if(I+1 >= n-1 ){ type = 2; bind_figure(plane_);return;}
        if(I<0){type = 2; bind_figure(plane_);return;}
        if(figure(plane_))
            type = 2;
        bind_figure(plane_);
        return;
    }
    if(type == 6)
    {
        free_figure(plane_);
        type = 8;
        if(I >= n-1 ){type = 6 ; bind_figure(plane_);return;}
        if(I-1 <= 0 ){type = 6 ; bind_figure(plane_);return;}
        if(figure(plane_))
            type = 6;
        bind_figure(plane_);
        return;
    }
    if(type == 7)
    {
        free_figure(plane_);
        type = 6;
        if(I-1 <= 0 ){ type = 7 ; bind_figure(plane_); return;}
        if(I+1 >= n-1 ){ type = 7 ; bind_figure(plane_); return;}
        if(figure(plane_)|| (I+1>n-1)||(I-1<0))
            type = 7;
        bind_figure(plane_);
        return;
    }
    if(type == 8)
    {
        free_figure(plane_);
        type = 2;
        if(I+1 >= n-1 ){ type = 8 ; bind_figure(plane_); return;}
        if(I-1 <= 0 ){ type = 8 ; bind_figure(plane_); return;}
        if(figure(plane_) || (I+1>n-1)||(I-1<0))
            type =8;
        bind_figure(plane_);
        return;
    }
    if(type == 3)
    {
        free_figure(plane_);
        type = 9;
        if(I-1<0){type = 3 ; bind_figure(plane_); return;}
        if(I+2>n-1){type = 3 ; bind_figure(plane_); return;}
        if(figure(plane_) || (I-1<0) || (I+2>n-1))
            type = 3;
        bind_figure(plane_);
        return;
    }
    if(type == 9)
    {
        free_figure(plane_);
        type = 3;
        if(I<0){type = 9 ; bind_figure(plane_); return;}
        if(I+1> n-1){type = 9 ; bind_figure(plane_); return;}
        if(figure(plane_) || (J-2<0))
            type = 9;
        bind_figure(plane_);
        return;
    }
    if(type == 4)
    {
        free_figure(plane_);
        type = 12;
        if(I >= n-1 ){type = 4 ; bind_figure(plane_);return;}
        if(I-1 <= 0 ){type = 4 ; bind_figure(plane_);return;}
        if(figure(plane_) ||(J-1<0))
            type = 4;
        bind_figure(plane_);
        return;
    }
    if(type == 12)
    {
        free_figure(plane_);
        type = 4;
        if(I+1 >= n-1 ){ type = 12 ; bind_figure(plane_); return;}
        if(I-1 <= 0 ){ type = 12 ; bind_figure(plane_); return;}
        if(figure(plane_) ||(I+1>n-1))
            type = 12;
        bind_figure(plane_);
        return;
    }
    if(type == 5)
    {
        free_figure(plane_);
        type = 11;
        if(I+1 >= n-1 ){ type = 5; bind_figure(plane_);return;}
        if(I<0){type = 5; bind_figure(plane_);return;}
        if(figure(plane_) || (J-1<0))
            type = 5;
        bind_figure(plane_);
        return;
    }
    if(type == 11)
    {
        free_figure(plane_);
        type = 5;
        if(I+1 >= n-1 ){ type = 11 ; bind_figure(plane_); return;}
        if(I-1 <= 0 ){ type = 11 ; bind_figure(plane_); return;}
        if(figure(plane_) || (I-1<0))
            type = 11;
        bind_figure(plane_);
        return;
    }
}
