#include <iostream>
#include <stdio.h>
#include <thread>

#include "include/engine.h"
#include "include/rendering/sprite.h"
#include "include/game.h"

int main(){
   Engine engine(800, 800);
 
   std::thread mainthread(&Engine::Init, &engine);//
    
   Game game(&engine);

   mainthread.join();
   return 0;
}
