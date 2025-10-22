#pragma once
class Board;
class Player;
class AI;

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
    Game(Player& _player, AI& _ai, Board& _b, PlayerType _turn);
    void Start();
    void Run();
    bool CheckEnd();
    void End();
};