#include "circle.hpp"

void circle::print(){
    
   
    int x0 = start_x;
    int y0 = start_y;
    int radius = size;
    double mid_y = ((y0+20)+(y0+25))/2;
    double mid_x = x0+8;
//    for(int cross = 0; cross < radius; cross++)
//    {
//        w.draw(x0+8,mid_y+cross);
//        w.draw(x0+8,mid_y-cross);
//        w.draw(x0+8+cross,mid_y);
//        w.draw(x0+8-cross,mid_y);
//    }
   if( radius < 1 ){
      return;       
   }
   int fx = 1 - radius;
   int ddFx = 1;
   int ddFy = -2 * radius;
   int x = 0;
   int y = radius;
   w.draw( mid_x + 0, mid_y + radius );
   w.draw( mid_x + 0, mid_y - radius );
   w.draw( mid_x + radius, mid_y + 0 );
   w.draw( mid_x - radius, mid_y + 0 );
    
   while( x < y ){
        if( fx >= 0 )
        {
            y--;
            ddFy += 2;
            fx += ddFy;
        }
        x++;
        ddFx += 2;
        fx += ddFx;   
      
        w.draw( mid_x + x, mid_y + y );
        w.draw( mid_x - x, mid_y + y );
        w.draw( mid_x + x, mid_y - y );
        w.draw( mid_x - x, mid_y - y );
        w.draw( mid_x + y, mid_y + x );
        w.draw( mid_x - y, mid_y + x );
        w.draw( mid_x + y, mid_y - x );
        w.draw( mid_x - y, mid_y - x );
      
   }
   
   
   
  
}


