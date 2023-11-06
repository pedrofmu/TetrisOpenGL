#include "include/piece.h"

#ifndef STATICPIECE
#define STATICPIECE

class StaticPiece{
public:
    StaticPiece(int startX, int startY, COLOR startColor): color(startColor), x(startX), y(startY){};

    COLOR color;
    int x, y;
};

#endif 
