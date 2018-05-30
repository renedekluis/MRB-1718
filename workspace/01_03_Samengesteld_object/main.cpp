// example: 
// using a line that requires its window

#include <iostream>
#include "window.hpp"
#include "line.hpp"
#include "circle.hpp"
#include "filled_rectangle.hpp"
#include "face.hpp"




int main(int argc, char **argv){
    window w( 800, 400, 2 );
    face gezicht1(w,20,20,0);
    gezicht1.print();
    face gezicht2(w,20,40,200);
    gezicht2.print();
    face gezicht3(w,40,20,400);
    gezicht3.print();
    return 0;
}



