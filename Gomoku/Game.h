#pragma once
#include "Board.h"
#include "Player.h"
#include "AI.h"

enum PlayerType {
    PLAYER = 1,
    COMPUTER = 2
};

enum GameState {
    RUNNING,
    SOMEONE_WIN,
    DRAW
};

class Game {
private:
    Player& player;
    AI& ai;
    Board& board;
    PlayerType turn;
    GameState state;
public:
    Game(Player& p, AI& a, Board& b, PlayerType turn);
    void Start();
    void Run();
    bool CheckEnd();
    void End();
};