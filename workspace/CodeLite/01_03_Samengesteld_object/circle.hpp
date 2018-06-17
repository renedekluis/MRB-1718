// example:
// declaration of a line class that stores its window

#ifndef circle_HPP
#define circle_HPP

#include "window.hpp"
// example:
// declaration of a line class that stores its window

#include "circle.hpp"

class circle {
private:
   int start_x;
   int start_y;
   int size;
   window & w;
public:
   circle( window & w, int start_x, int start_y, int size):
      start_x( start_x ),
      start_y( start_y ),
      size(size),
      w( w )
   {}
   void print();
};

#endif // LINE_HPP
