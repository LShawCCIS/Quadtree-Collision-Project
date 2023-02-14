#include "quad.h"


Quadtree::Quadtree(int h, int w, Quadtree * parent_ = NULL)
    :   parent(parent_)
{
    rect = new Rectangle(h, w);
    divided = false;
    threshold = 10;
    northeast = NULL;
    northwest = NULL;
    southeast = NULL;
    southwest = NULL;
}

Quadtree::Quadtree(double x, double y, double h, double w, Quadtree * parent_ = NULL)
    :   parent(parent_)
{
    rect = new Rectangle(x, y, h, w);
    divided = false;
    threshold = 10;
    northeast = NULL;
    northwest = NULL;
    southeast = NULL;
    southwest = NULL;
}




Quadtree::~Quadtree()
{
    delete rect;
    if (this->northeast != NULL)
        delete this->northeast;
    if (this->northwest != NULL)
        delete this->northwest;
    if (this->southeast != NULL)
        delete this->southeast;
    if (this->southwest != NULL)
        delete this->southwest; 
}

void Quadtree::insert(Circle *& c_point, Surface & surface)
{
    if (this == NULL)
        return;
    if (rect->contains(c_point) == false)
    {
        return;
    }
    if (this->points.size() < threshold && this->divided == false)
    {
        points.push_back(c_point);
        return;
    }
    else
    {
        if (!divided && (get_depth(this) < depth_max))
        {
            this->divide(surface);
        }
        if (!divided && (get_depth(this) >= depth_max))
        {
            points.push_back(c_point);
            return;
        }
        else
        {
            if (this->northeast->rect->contains(c_point))
                get_ne()->insert(c_point, surface);
            if (this->northwest->rect->contains(c_point))
                get_nw()->insert(c_point, surface);
            if (this->southeast->rect->contains(c_point))
                get_se()->insert(c_point, surface);
            if (this->southwest->rect->contains(c_point))
                get_sw()->insert(c_point, surface);
        
        }  
    }
}

void Quadtree::divide(Surface & surface)
{
    int x = this->rect->c_x();
    int y = this->rect->c_y();
    
    surface.put_line(x, this->rect->north(), x, this->rect->south(), 255, 0, 0);

    surface.put_line(this->rect->west(), y, this->rect->east(), y, 0, 183, 0);
    
    this->divided = true;
    northeast = new Quadtree((this->rect->c_x() + this->rect->east()) / 2,
                             (this->rect->c_y() + this->rect->north()) / 2,
                             this->rect->height() / 2, this->rect->width() / 2,
                             this);
    northwest = new Quadtree((this->rect->c_x() + this->rect->west()) / 2,
                             (this->rect->c_y() + this->rect->north()) / 2,
                             this->rect->height() / 2, this->rect->width() / 2,
                             this);

    southeast = new Quadtree((this->rect->c_x() + this->rect->east()) / 2,
                             (this->rect->c_y() + this->rect->south()) / 2,
                            this->rect->height() / 2, this->rect->width() / 2,
                            this);

    southwest = new Quadtree((this->rect->c_x() + this->rect->west()) / 2,
                             (this->rect->c_y() + this->rect->south()) / 2,
                            this->rect->height() / 2, this->rect->width() / 2,
                            this);
    this->spread_children(surface);
   
}

void Quadtree::spread_children(Surface & surface)
{
    
    for (int i = 0; i < this->points.size(); i++)
    {
        //std::cout << "IN SIDE OF SPREAD CHILDREN" << std::endl;
        if (this->northeast->rect->contains(points[i]) == false &&
            this->northwest->rect->contains(points[i]) == false &&
            this->southeast->rect->contains(points[i]) == false &&
            this->southwest->rect->contains(points[i]) == false)
        {
            i++;
        }
        else
        {
            this->insert(points[i], surface);
            this->points.erase(points.begin() + i);
            i--;
        }  
    }
}

int Quadtree::get_depth(Quadtree * node)
{
    if (node->parent == NULL)
    {
        return 0;
    }
    else
    {
        int x = get_depth(node->parent);
        return x + 1;
    }
}

Quadtree *& Quadtree::get_ne()
{
    return northeast;
}

Quadtree *& Quadtree::get_nw()
{
    return northwest;
}

Quadtree *& Quadtree::get_se()
{
    return southeast;
}

Quadtree *& Quadtree::get_sw()
{
    return southwest;
}

void Quadtree::print_tree(Quadtree * node)const
{
    if (node == NULL)
    {
        return;
    }
    else
    {
        std::cout << "\n<Tree " << node <<  "parent: " << node->parent << " divided:"
                  << node->get_divided() << " child count: " << node->points.size() << " > ";
        print_tree(node->get_ne());
        print_tree(node->get_nw());
        print_tree(node->get_se());
        print_tree(node->get_sw());
    }
}


bool Quadtree::get_divided()const
{
    return divided;
}

Quadtree * Quadtree::find_circles(Circle * c)
{
    Quadtree * temp = NULL;
     if (this != NULL)
    {
        
    }
    
    if (this == NULL)
    {
        return NULL;
    }
    else if (this->rect->contains(c) && this->divided == true)
    {
        Quadtree * temp = NULL;
        if (this->northeast->rect->contains(c))
            temp = get_ne()->find_circles(c);
        if (this->northwest->rect->contains(c))
            temp = get_nw()->find_circles(c);
        if (this->southeast->rect->contains(c))
            temp = get_se()->find_circles(c);
        if (this->southwest->rect->contains(c))
            temp = get_sw()->find_circles(c);
        return temp;
    }
    else 
    {
        return this;
    }
}

void Quadtree::check_collisions(Circle * circle)
{
    for (int i =0; i < this->points.size(); i++)
    {
        if (this->points[i] == circle)
            i++;
        else
            circle->check_circles(points[i]);
    }
}

std::vector< Circle *> & Quadtree::get_points()
{
    return points;
}

std::ostream & operator<<(std::ostream &cout, Quadtree& tree)
{
    tree.print_tree(&tree);
    return cout;
}
