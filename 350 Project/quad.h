#ifndef QUAD_H
#define QUAD_H

#include <vector>
#include "rectangle.h"
#include "circle.h"

class Quadtree
{
  public:
    Quadtree(int, int, Quadtree *);
    Quadtree(double, double, double, double, Quadtree *);
    ~Quadtree();
    void insert(Circle *&, Surface &);
    void divide(Surface &);
    void print_tree(Quadtree * node)const;
    bool get_divided()const;
    int get_depth(Quadtree * node);
    Quadtree * find_circles(Circle *);
    void check_collisions(Circle *);
    void spread_children(Surface &);
    Quadtree *& get_ne();
    Quadtree *& get_nw();
    Quadtree *& get_se();
    Quadtree *& get_sw();
    std::vector< Circle *> & get_points();
    friend std::ostream & operator<<(std::ostream &, Quadtree&);
    
  private:
    Rectangle * rect;
    std::vector< Circle * > points;
    std::vector< Circle * > collisions;
    Quadtree * parent;
    Quadtree * northeast; // child 1
    Quadtree * northwest; // child 2
    Quadtree * southeast; // child 3
    Quadtree * southwest; // child 4
    bool divided;
    int threshold;
    int depth_max = 5;
};

#endif
