#pragma once
#include "graphics.h"
#include <vector>
#include "TypeAliases.h"

struct GridPos {
    int row;
    int col;
};

enum PieceType {
    kWhitePiece,
    kBlackPiece,
	kNoPiece
};

class Board {
private:
	IMAGE board_img;
	IMAGE white_piece_img;
	IMAGE black_piece_img;

    const int kBoardDimension;
    const int kBoardSize;
    const int kMarginX;
    const int kMarginY;
    const double kGridSize;

    const int kPieceSize;

    vvector<PieceType> board_state;
public:
	Board(const int board_dimension, const int board_size, const int marginx, const int marginy, const double gird_size, const int piece_size);
    void Init();
    bool Click(int x, int y, GridPos *pos);//if valid, return pos

    void PlacePiece(const GridPos *pos, PieceType type);
    PieceType get_piece_type(const GridPos *pos);
    vvector<PieceType> get_board_state();

    void DebugCircle(int col, int row, int radius);
};