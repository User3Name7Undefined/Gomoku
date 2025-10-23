#pragma once
#include "graphics.h"
#include <vector>

struct PiecePos {
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
    const int kMargin;
    const float kGridSize;

    const int kPieceSize;

	std::vector<std::vector<PieceType>> board_state;

    int grid_pixel_pos(int index);
public:
	Board(const int board_dimension, const int board_size, const int margin, const int piece_size);
    void Init();
    bool Click(int x, int y, PiecePos *pos);//if valid, return pos
    void PlacePiece(const PiecePos *pos, PieceType type);
    PieceType get_piece_type(const PiecePos *pos);
};