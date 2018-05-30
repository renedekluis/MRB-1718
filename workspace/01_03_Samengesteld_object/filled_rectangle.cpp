#include "filled_rectangle.hpp"

void filled_rectangle::print(){
   int x0 = start_x, y0 = start_y, x1 = end_x, y1 = end_y;
   
   for(int i = x0; i < x1; i++){
       for(int j = y0; j < y1; j++){
           w.draw(i, j);
       }
   }
}
