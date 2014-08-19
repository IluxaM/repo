#include "Glass.h"
#include "Figure.h"
#include "mainwindow.h"
#include <iostream.h>
#include<string.h>
Glass::Glass(QWidget* parent) : QGLWidget(parent)
{
   setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
   n = 16;
   N = 24;
   srand( time( NULL ) );
   //active = true;
   active = false;
   scores = 0;
   level = 1;
   difficulty = 0; 
   plane_.plane = new bool* [n];
   plane_.color = new int* [n];
   done = false;
   for(int i = 0 ; i < n ; i++)
   {
       plane_.plane[i] = new bool [N];
       plane_.color[i] = new int [N];
   }
   for(int i = 0; i< n ;i++)
       for(int j = 0;j<N;j++)
       {
           plane_.plane[i][j]=false;
           plane_.color[i][j] = 0;
       }

   int type = rand() % 5 + 1;
   figure = new Figure(type,n/2,N-1,plane_);
   //
   figure->free_figure(plane_);
   figure->active = false;
   //
   timer_1 = new QTimer(this);
   connect(timer_1, SIGNAL(timeout()), this, SLOT(game()));
   timer_1->start(400);
   rightarm_keyboard = true;
   friend_window = false;
   type_friend = 0;
}

void Glass::initializeGL()
{
    qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

}

void Glass::resizeGL(int width,int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width)/height;
    glFrustum(-x, +x, -1.0, +1.0, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}

void Glass::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}

void Glass::draw()
{

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-14.0f);
    GLfloat pointi = 0;
    GLfloat pointj = 0;
    GLfloat height = 3;
    GLfloat width = 2;
    //Glass pix map
    glBegin(GL_POLYGON);
    glColor4f(1.0f,1.0f,0.0f,0.1f);
    glVertex3f( -width,height-0.25, 0.0f);
    glVertex3f(-width,-height-0.25, 0.0f);
    glVertex3f(width,-height-0.25,0.0f);
    glVertex3f( width,height-0.25, 0.0f);
    glEnd();


    qglColor(Qt::white);
    renderText(width+0.2,height,0, QString::fromUtf8("Scores : %0").arg(scores),QFont());
    renderText(width+0.2,height-0.25,0, QString::fromUtf8("Level : %0").arg(level),QFont());
    if(!active)
    {
        glColor3f(0.0f,0.0f,0.0f);
        renderText(-width/2,0,0,"Game pause!",QFont());
    }


    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < N  ; j++)
        {
            if(plane_.plane[i][j])
            {
                glBegin(GL_POLYGON);
                if (plane_.color[i][j] == 0) glColor3f(0,0,1.0f); // blue
                if (plane_.color[i][j] == 1) glColor3f(0.0f,1.0f,0.0f); // green
                if (plane_.color[i][j] == 2)  glColor3f(1.0f,0.0f,0.0f);  // red
                if (plane_.color[i][j] == 3)  glColor3f(1.0f,0.0f,1.0f);  //
                //glColor3f(sin(color),cos(color),1.0f);
                glVertex3f(-width+pointi, -height+pointj,0.01f);
                //glColor3f(0.0f,0.0f,sin(color)+cos(color));
                glVertex3f(-width+pointi, -height-0.25+pointj,0.01f);
                //glColor3f(1.0f+sin(color),0.0f,0.0f);
                glVertex3f(-width+0.25+pointi, -height-0.25+pointj, 0.01f);
                //glColor3f(sin(color)+cos(color),1.0f,0.0f);
                glVertex3f(-width+0.25+pointi, -height+pointj, 0.01f);
                glEnd();
            }
            pointj+=0.25;

        }
        pointj = 0;
        pointi+=0.25;
    }

}

int Glass::sumJ(int line)
 {
     int summa = 0;
     for(int i = 0 ; i < n ; i++)
         summa+=plane_.plane[i][line];
     return summa;
 }
void Glass::clearline_move(int line)
{
     for( int i = 0 ; i<n ; i++)
     {
        plane_.plane[i][line] = false;
        plane_.color[i][line] = 0;
     }
     scores+=100;
     for(int i = 0 ; i<n;i++)
         for(int j = line ; j < N-1 ; j++)
         {
             plane_.plane[i][j] =plane_.plane[i][j+1];
             plane_.color[i][j] =plane_.color[i][j+1];
         }
     for(int i = 0 ; i < n ; i++)
     {
        plane_.plane[i][N-1] = false;
        plane_.color[i][N-1] = 0;
     }
 }

void Glass::keyPressEvent(QKeyEvent* event)
 {
      switch(event->key())
      {
          case Qt::Key_Escape:
          {
             queue.add_front("esc");
             queue_send.add_front("esc");
             return;
          }
          case Qt::Key_Space:
          {
            queue.add_front("space");
            queue_send.add_front("space");
            return;
          }

          case Qt::Key_Right:
          {
            if(rightarm_keyboard)
            {
                if(active && figure->ACTIVE())
                {
                    queue.add_front("right");
                    queue_send.add_front("right");
                }
                    return;
             }
             return;
              }
           case Qt::Key_Left:
           {
                if(rightarm_keyboard)
                {
                    if(active && figure->ACTIVE())
                    {
                        queue.add_front("left");
                        queue_send.add_front("left");
                    }

                      return;
                }
            }
            case Qt::Key_Up:
            {
                if(rightarm_keyboard)
                {
                    if(active && figure->ACTIVE())
                    {
                        queue.add_front("up");
                        queue_send.add_front("up");
                    }
                 }
                  return;
              }
              case Qt::Key_Down:
              {
                if(rightarm_keyboard)
                {
                    if(active && figure->ACTIVE())
                    {
                        queue.add_front("down");
                        queue_send.add_front("down");
                    }
                }
                  return;
              }




            case Qt::Key_D:
            {
                  if(!rightarm_keyboard)
                  {
                      if(active && figure->ACTIVE())
                      {
                          queue.add_front("right");
                          queue_send.add_front("right");
                      }
                          return;
                   }
                   return;
             }
             case Qt::Key_A:
             {
                  if(!rightarm_keyboard)
                  {
                      if(active && figure->ACTIVE())
                      {
                          queue.add_front("left");
                          queue_send.add_front("left");
                      }

                        return;
                  }
              }
              case Qt::Key_W:
              {
                  if(!rightarm_keyboard)
                  {
                      if(active && figure->ACTIVE())
                      {
                          queue.add_front("up");
                          queue_send.add_front("up");
                      }
                   }
                    return;
                }
                case Qt::Key_S:
                {
                      if(!rightarm_keyboard)
                      {
                          if(active && figure->ACTIVE())
                          {
                              queue.add_front("down");
                              queue_send.add_front("down");
                          }
                      }
                        return;
                }

      }
  }
bool Glass::compare_dif_score()
{
     if( scores > difficulty )
     {
         difficulty = scores*2;
         level++;
         return true;
     }
     else return false;
}
void Glass::game()
{
  string support_el;
  if(done)
  {
      QMessageBox::information(0, "Information", "Closing client's widgets...");
      exit(0);
  }
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
          {
              QMessageBox::information(0, "Information", "Game Over !");
              done = true;
          }
          else
          {
              type = rand() % 5 + 1 ;
              delete figure;
              //
              support_el ="type";
              char* data = new char[10];
              for(int i = 0 ;i<support_el.size(); i++)
                      data[i] = support_el[i];
              data[support_el.size()] = type+'0';
              //data[support_el.size()+1] = '.';
              //data[support_el.size()+2] = type+'0';
              queue_send.add_front(data);
              std::cout<<"TYPEPE_1 IS : "<<"type"+type+'0'<<std::endl;
              std::cout<<"TYPEPE_2 IS : "<<queue_send.return_last()<<std::endl;
              //
              if(friend_window)
              {
                  while(type_friend == 0);
                  figure = new Figure(type_friend,n/2,N-1,plane_);
                  std::cout<<"TRUE TYPE FRIEND "<<type_friend<<std::endl;
                  type_friend = 0;
              }
              else
                  figure = new Figure(type,n/2,N-1,plane_);
          }
      }
      figure->fall(plane_);
  }
  updateGL();
 }

void Glass::activate_message()
 {
        if (queue.size() == 0)
            return;

        if(queue.return_last() == "space")
        {
            queue.delete_back();
            active = !active;
            return;
        }
        if(queue.return_last() == "right")
        {
            queue.delete_back();
            if(active && figure->ACTIVE()) //
            { //
                PoM = true;
                figure->boundary(PoM,plane_);
            } //
            return;
        }
        if(queue.return_last() == "left")
        {
            queue.delete_back();
            if(active && figure->ACTIVE()) //
            { //
                PoM = false;
                figure->boundary(PoM,plane_);
            } //
             return;
         }
         if(queue.return_last() == "up")
         {
             queue.delete_back();
             if(active && figure->ACTIVE()) //
             { //
                    figure->change_type(plane_);
             } //
             return;
         }
         if(queue.return_last() == "down")
         {
                queue.delete_back();
                if(active && figure->ACTIVE()) //
                { //
                    figure->fall(plane_);
                } //
                return;
         }
         if(queue.return_last() == "esc")
         {
             std::cout<<"Game is ending"<<std::endl;
             //
             queue.delete_back();
             //
             done = true;
         }

 }
