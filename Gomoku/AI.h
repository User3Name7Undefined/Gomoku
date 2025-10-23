#pragma once
class Board;
enum PieceType;

class AI {
private:
    Board* board;
    PieceType use_type;
public:
    void Init(Board *_board, PieceType _use_type);
    void Move();
};