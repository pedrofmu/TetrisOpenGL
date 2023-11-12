#ifndef GAME
#define GAME 
#include "include/engine.h"
#include "include/rendering/sprite.h"
#include "include/piece.h"
#include "include/rendering/tileSprite.h"
#include "include/board.h"
#include "include/movingPiece.h"
#include "include/staticPiece.h"
#include <iostream>
#include <vector>

class Game : public IUpdateSubscriber , public IInputSubscriber{
public:
    Game(Engine* engine);
    void Init();   

    void update() override;

    void processInput(int key) override;

private:
    int keyToProcess;
    double lastTime = 0;
    double timeToPass = 0.25;

    Engine* _engine;
    TileSprite* tiles[10][20];
    std::vector<StaticPiece> staticPieces;
    Board board;
    MovingPiece* movingPiece;

    void movePiece();
    void placePiece();
    void deleteRow(int row);

    unsigned int texutres[5];

    bool isValidMove(int newX, int newY, std::vector<std::vector<int>>& structure);
};
#endif 
