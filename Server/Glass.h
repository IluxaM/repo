#ifndef GLASS_H
#define GLASS_H
#include <QtOpenGL>
#include <QtWidgets>
#include <QKeyEvent>
#include "Figure.h"
#include "Queue.h"


class Glass: public QGLWidget
{
   Q_OBJECT
public:
    Glass(QWidget *parent = 0);
   // bool** return_plane(){ return plane ;}
    void clearline_move(int line);
    int sumJ(int line);
    int return_n(){return n;}
    int return_N(){return N;}
    bool compare_dif_score();
    char* return_data(){return data;}
    Queue queue;


public slots:
    void game();
    void activate_message();

protected:
    void initializeGL();
    void resizeGL(int width,int height);
    void paintGL();
    void keyPressEvent(QKeyEvent* event);

void draw();

int n;
int N;
bool active;
int scores;
int level;
int difficulty;
bool done;
bool PoM;
int type;
Plane plane_;

Figure* figure;
QTimer* timer_1;
QTimer* timer_2;
char data[256];


};

#endif // GLASS_H
