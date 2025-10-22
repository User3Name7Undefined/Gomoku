#pragma once
#include "Board.h"
#include "Player.h"
#include "AI.h"

enum PlayerType {
    kPlayer,
    kComputer
};

enum GameState {
    kRunning,
    kSomeoneWin,
    kDraw
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