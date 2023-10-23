#include "include/engine.h"
#include "include/rendering/sprite.h"

int main () {
   Engine engine = Engine();

   //del 0 al 1 (ahora centrado)
   engine.añadirSprite("../assets/textures/tex.jpeg", 0, 0, 0.3, 0.3);
   engine.añadirSprite("../assets/textures/coche.jpg", 0.75, 0.25, -0.3, -0.3);

   engine.Init();

   return 0;
}
