#include "rectangle.h"

Rectangle::Rectangle(int h, int w)
    : height_(h), width_(w)
{
    center_x = w / 2;
    center_y = h / 2;
    north_ = h - h;
    south_ = h;
    west_ = w - w;
    east_ = w;
}

Rectangle::Rectangle(double x, double y, double h, double w)
    :  center_x(x), center_y(y), height_(h), width_(w)
{
    north_ = center_y - height_ / 2;
    south_ = center_y + height_ / 2;
    east_ = center_x + width_ / 2;
    west_ = center_x - width_ / 2;
}

Rectangle::~Rectangle()
{}

double & Rectangle::c_x()
{
    return center_x;
}

double & Rectangle::c_y()
{
    return center_y;
}


double & Rectangle::height()
{
    return height_;
}

double & Rectangle::width()
{
    return width_;
}

double & Rectangle::north()
{
    return north_;
}

double & Rectangle::south()
{
    return south_;
}

double & Rectangle::east()
{
    return east_;
}

double & Rectangle::west()
{
    return west_;
}

bool Rectangle::contains(Circle * circle)
{

    return ((circle->get_y() >= north_ && circle->get_y() <= south_) &&
            (circle->get_x() >= west_ && circle->get_x() <= east_));
    
}

