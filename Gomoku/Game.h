#pragma once
class Board;
class Player;
class AI;

enum PlayerType {
    kPlayer,
    kComputer
};

class Game {
private:
    Player *player;
    AI *ai;
    Board *board;
    PlayerType turn;
public:
    Game(Player *_player, AI *_ai, Board *_b, PlayerType _turn);
    void Start();
    void Run();
    void End();
};