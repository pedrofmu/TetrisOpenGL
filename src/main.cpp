#include <iostream>
#include <stdio.h>
#include <thread>

#include "include/engine.h"
#include "include/rendering/sprite.h"
#include "include/game.h"

int main(){
   Engine engine(800, 800);
 
   Game game(&engine);

   std::thread mainthread(&Engine::Init, &engine);

   mainthread.join();
   return 0;
}
