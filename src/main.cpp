#include "include/engine.h"
#include "include/rendering/sprite.h"

int main () {
   Engine engine = Engine();
   
   //ahora mismo és 
   engine.añadirSprite("../assets/textures/tex.jpeg", 400, 300, 800, 600);
   engine.añadirSprite("../assets/textures/coche.jpg", 0, 0, 800, 600);

   engine.Init();

   return 0;
}
