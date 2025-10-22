#pragma once
class Board;
enum ChessType;

class AI {
private:
    Board* board;
    ChessType use_type;
public:
    void Init(Board *_board);
    void Move();
};