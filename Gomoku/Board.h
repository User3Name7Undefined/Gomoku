#pragma once

struct ChessPos {
    int row;
    int col;
};

enum ChessType {
    WHITE = 1,
    BLACK = -1,
    NONE = 0
};

class Board {
private:
public:
    void Init();
    bool Click(int x, int y, ChessPos& pos);//if valid, return pos
    void ChessDown(const ChessPos& pos, ChessType type);
    ChessType get_chess_type(const ChessPos& pos);
};