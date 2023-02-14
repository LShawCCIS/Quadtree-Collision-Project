#include "circle.h"
#include <cmath>
#include <math.h>

Circle::Circle(Surface & surface, Event & event)
    {
        x_ = rand() % 1680;
       	y_ = rand() % 850;
        radius_ = 15; // 150
        speed_ = 4;
        dx = speed_;
        dy = speed_;
        surface.put_circle(x_, y_, radius_, 255, 105, 180);
        color_ = 255;
    }

Circle::~Circle()
{
    
}

int & Circle::get_x()
{
    return x_;
}

int & Circle::get_y()
{
    return y_;
}

int & Circle::get_dx()
{
    return dx;
}

int & Circle::get_speed()
{
    return speed_;
}

int & Circle::get_dy()
{
    return dy;
}

void Circle::set_x(int x)
{
    x_ = x;
}

void Circle::set_y(int y)
{
    x_ = y;
}

void Circle::move_circle(Surface & surface, std::vector< Circle * > & circles, bool collision)
{
    bool hit = false;
    
        x_ += dx;
        y_ += dy;
        
        if (x_ >= 1680 - radius_)
        {
            hit = true;
            dx = -speed_ - rand() % 4;
        }
        else if (x_ <= radius_)
        {
            hit = true;
            dx = speed_ + rand() % 4;
        }
        else if (y_ >= 850 - radius_)
        {
            hit = true;
            dy = -speed_ - rand() % 4;
        }
        else if (y_ <= radius_)
        {
            hit = true;
            dy = speed_ + rand() % 4;
        }
        if (hit == true)
        {
            if (color_ == 255)
            {
                surface.put_circle(x_, y_, radius_, 153, 50, 204);
                color_ = 153;
            }
            else
            {
                surface.put_circle(x_, y_, radius_, 255, 105, 180);
                color_ = 255;
            }
                
        }
        else
        {
            if (color_ == 255)
            {
                surface.put_circle(x_, y_, radius_, 255, 105, 180);
            }
            else
            {
                surface.put_circle(x_, y_, radius_, 153, 50, 204);
            }
            
        }
            
}

void Circle::draw_circle(Surface & surface, Event & event)
{
        
	int r = radius_;
        
      	surface.lock();
        surface.put_circle(x_, y_, radius_, 255, 0 , 0);
      	surface.unlock();
      	surface.flip();

        delay(20);
	
	return;
}

void Circle::check_circles(Circle *& c2)
{
    //std::cout << "checking circles for collision" << std::endl;
    int x1, x2, y1, y2, distance, x_s, y_s;
    x1 = this->x_;
    x2 = c2->x_;
    y1 = this->y_;
    y2 = c2->y_;
    x_s = x1 - x2;
    x_s = pow(x_s, 2);
    y_s = y1 - y2;
    y_s = pow(y_s, 2);
    distance = x_s + y_s;
    distance = sqrt(distance);
    
    if (distance < (radius_ + c2->radius_))
    {
        int temp, temp2;
        
        temp = this->get_dx();
        temp2 = this->get_dy();
        this->get_dx() = c2->get_dx(); 
        this->get_dy() = c2->get_dy();
        c2->get_dx() = temp; // random_x2;
        //c2->get_x() += random_x2;
        c2->get_dy() = temp2; //random_y2;
     
        if (this->get_x() <= c2->get_x())
        {
            this->get_x() -= ((radius_ + c2->radius_) - distance);
            c2->get_x() += ((radius_ + c2->radius_) - distance);
        }
        else
        {
            this->get_x() += ((radius_ + c2->radius_) - distance);
            c2->get_x() -= ((radius_ + c2->radius_) - distance);
        }

        if (this->color_ == 255)
            this->color_ = 128;
        else
            this->color_ = 255;
                
        if (c2->color_ == 255)
            c2->color_ = 128;
        else
            c2->color_ = 255;
            
    }
    
}


std::ostream & operator<<(std::ostream &cout, Circle & c)
{
    std::cout << "x:" << c.get_x() << " y:" << c.get_y() << " address:" << &c <<
        std::endl;
   
    return cout;
}
  
