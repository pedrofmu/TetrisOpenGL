#include "include/engine.h"
#include "include/rendering/sprite.h"
#include <iostream>

class Game : public IUpdateSubscriber , public IInputSubscriber{
public:
    Game(Engine* engine);
    void Init();   

    void update() override;

    void processInput(int key) override;

private:
    Engine* _engine;
    Sprite* prueba;
};
