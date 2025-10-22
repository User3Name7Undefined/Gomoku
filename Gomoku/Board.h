#pragma once
#include "graphics.h"
#include <vector>

struct ChessPos {
    int row;
    int col;
};

enum ChessType {
    kWhiteChess,
    kBlackCHess,
	kNoChess
};

class Board {
private:
	IMAGE board_img;
	IMAGE white_chess_img;
	IMAGE black_chess_img;

    const int kBoardDimension;
    const int kBoardSize;
    const int kMargin;
    const float kGridSize;

	std::vector<std::vector<ChessType>> board_state;
public:
	Board(const int board_dimension, const int board_size, const int margin);
    void Init();
    bool Click(int x, int y, ChessPos& pos);//if valid, return pos
    void ChessDown(const ChessPos& pos, ChessType type);
    ChessType get_chess_type(const ChessPos& pos);
};