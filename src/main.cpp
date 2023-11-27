#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>

#include "include/engine.h"
#include "include/rendering/sprite.h"
#include "include/game.h"

#include "include/myLibs/hashMap.h"

int main(){
   Engine engine(800, 800);
 
   Game game(&engine);

   std::thread mainthread(&Engine::Init, &engine);

   mainthread.join();
   return 0;
}
