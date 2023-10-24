#include "include/engine.h"
#include "include/rendering/sprite.h"

int main () {
   Engine engine = Engine(800, 600);
   
   //ahora mismo és 
   Sprite* sprite1 = engine.addSprite("../assets/textures/tex.jpeg", 400, 300, 800, 600);
   engine.addSprite("../assets/textures/coche.jpg", 0, 0, 800, 600);

   engine.Init();

   return 0;
}
