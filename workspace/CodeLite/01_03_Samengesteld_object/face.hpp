#ifndef face_HPP
#define face_HPP

#include "window.hpp"
#include "line.hpp"
#include "circle.hpp"
#include "filled_rectangle.hpp"
#include "face.hpp"

class face{
private:
    int eye1;
    int eye2;
    int move;
    window & w;
    circle wiel1;
    circle wiel2;
    circle wiel3;
    filled_rectangle mond;
    line scar;
    line scar2;
    line scar3;
   
public:
   face( window & w, int oog1, int oog2, int itemID);
    void print();

};

#endif // LINE_HPP