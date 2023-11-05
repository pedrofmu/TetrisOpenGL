#ifndef TILESPEITE
#define TILESPEITE

#include "include/rendering/sprite.h"
class TileSprite : public Sprite{
public:
    TileSprite(unsigned int defaultTexture, float X, float Y, float WIDTH, float HEIGTH);

    void setTexutre(unsigned int newTexture);
};

#endif 
