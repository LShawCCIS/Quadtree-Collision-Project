#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"

class Circle
{
  public:

    Circle(Surface &, Event &);
    Circle(int, int, double);
    ~Circle();
    int & get_x();
    int & get_y();
    int & get_dx();
    int & get_dy();
    int & get_speed();
    void set_x(int);
    void set_y(int);
    void draw_circle(Surface &, Event &);
    void move_circle(Surface &, std::vector< Circle * > &, bool);
    void check_circles(Circle *&);
    friend std::ostream & operator<<(std::ostream &, Circle &);
  private:
    int x_, y_;
    double radius_;
    int speed_;
    int dx;
    int dy;
    int color_;
};

#endif
