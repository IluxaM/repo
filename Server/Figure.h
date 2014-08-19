#ifndef FIGURE_H
#define FIGURE_H

#include <time.h>
#include <Qtimer>

struct Plane
{
    bool** plane;
    int** color;
};


class Figure
 {
 public:
    bool active;
    Figure(int TYPE, int i, int j, Plane plane_);
    bool figure(Plane plane_);
    bool END();
    void boundary(bool PoM,Plane plane_);
    void bind_figure(Plane plane_);
    void free_figure(Plane plane_);
    void fall(Plane plane_);
    bool ACTIVE(){return active;}
    void change_type(Plane plane_);
private:
     int I, J, type, color;
 };

#endif

