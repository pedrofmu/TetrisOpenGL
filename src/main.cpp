#include "include/engine.h"
#include "include/objeto.h"

int main () {
   Engine engine = Engine();

   //del 0 al 1 (ahora centrado)
   engine.añadirObjeto("../assets/textures/tex.jpeg", 0.5, 0.5, 0.3, 0.3);
   engine.añadirObjeto("../assets/textures/coche.jpg", 0.75, 0.25, -0.3, -0.3);

   engine.Init();

   return 0;
}
