
#include "face.hpp"

//window w( 400, 400, 2 );
#define radius 100
face::face( window & w, int oog1, int oog2, int itemID):
    eye1( oog1 ),
    eye2( oog2 ),
    move( itemID ),
    w( w ),
    wiel1(w,radius+move,radius,radius),
    wiel2(w,radius/4+20+move,radius,eye1),
    wiel3(w,radius*1.5+move,radius,eye2),
    mond(w, radius/2+move,2*radius-radius/4,2*radius-radius/2+move,2*radius-radius/5),
    scar(w,radius+move,radius/2,(radius/2+radius/4)+move,radius/2+radius/5),
    scar2(w,radius/2+radius/4+move,radius/2+radius/5,radius+move,radius/2+radius/5),
    scar3(w,radius+move,radius/2+radius/5,radius/2+radius/4+move,radius-radius/8)
    {}

void face::print()
{
    wiel1.print();
    wiel2.print();
    wiel3.print();
    mond.print();
    scar.print();
    scar2.print();
    scar3.print();

}