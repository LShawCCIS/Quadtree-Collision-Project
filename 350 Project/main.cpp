
#include "circle.h"
#include "quad.h"

int main(int argc, char* argv[])
{
        int height = 850;
        int width = 1680;
        bool quadStart = false;
        srand((unsigned int) time(NULL));
        Surface surface(width, height);
	Event event;
        int circle_count = 100;
        Circle circle(surface, event);
        //Quadtree quad(width/2, height/2, height, width, NULL);

	// Prints to console window
        std::vector< Circle * > circles;
        for (int i = 0; i < circle_count; i++)
        {
            Circle * p = new Circle(surface, event);
            circles.push_back(p);
            //quad.insert(p);
        }

        
        
        while(1)
        {
            if (event.poll() && event.type() == QUIT) break;
            
            surface.lock();
            surface.unlock();
            surface.flip();
            surface.fill(BLACK);
            delay(20);
            
            KeyPressed keypressed = get_keypressed();
	    if (keypressed[SPACE])
            {
                if (quadStart == false)
                    quadStart = true;
                else
                    quadStart = false;
       	    }
            if (quadStart)
            {
                if (event.poll() && event.type() == QUIT) break;
                
                Quadtree quad(height, width, NULL);
                Quadtree * temp;
                std::vector< Circle * > hold;
                for (int i = 0; i < circles.size(); i++)
                {
                    quad.insert(circles[i], surface);
                }
                
                for (int i = 0; i < circles.size(); i++)
                {
                    temp = quad.find_circles(circles[i]);
                    temp->check_collisions(circles[i]);
                    //circles[i]->check_circles(hold[j]);
                    circles[i]->move_circle(surface, circles, true);
                    
                   
                }
                

            }
            else
            {
                bool collision;
                for (int i = 0; i < circles.size(); i++)
                {
                    for (int j = i+1; j < circles.size(); j++)
                    {
                        circles[i]->check_circles(circles[j]);
                    }
                    circles[i]->move_circle(surface, circles, collision);     
                }
            }
        }
        for (int i = 0; i < circles.size(); i++)
        {
            delete circles[i];
        }
    
	return 0;
}
