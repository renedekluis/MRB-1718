// example:
// declaration of a line class that stores its window

#ifndef filled_rectangle_HPP
#define filled_rectangle_HPP

#include "window.hpp"
// example:
// declaration of a line class that stores its window

#include "filled_rectangle.hpp"

class filled_rectangle {
private:
   int start_x;
   int start_y; 
   int end_x;
   int end_y;
   window & w;
public:
   filled_rectangle( window & w, int start_x, int start_y, int end_x, int end_y ):
      start_x( start_x ),
      start_y( start_y ),
      end_x( end_x ),
      end_y( end_y ),
      w( w )
   {}
   void print();
};

#endif // LINE_HPP
