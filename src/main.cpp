#include "include/engine.h"
#include "include/rendering/sprite.h"

int main () {
   Engine engine = Engine(800, 600);

   Sprite* maderaSprite = engine.addSprite("../assets/textures/tex.jpeg", 400, 300, 600, 600);
//   Sprite* cocheSprite = engine.addSprite("../assets/textures/coche.jpg", 400, 300, 600, 600);

   engine.Init();

   return 0;
}
