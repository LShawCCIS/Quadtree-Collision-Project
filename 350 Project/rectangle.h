#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "circle.h"

class Rectangle
{

  public:
    Rectangle(int, int);
    Rectangle(double, double, double, double);
    ~Rectangle();
    double & c_x();
    double & c_y();
    double & height();
    double & width();
    double & north();
    double & south();
    double & east();
    double & west();
    bool contains(Circle * circle);

  private:
    double center_x;
    double center_y;
    double height_;
    double width_;
    double north_;
    double south_;
    double east_;
    double west_;
};

#endif
