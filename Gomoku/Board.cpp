#include "Board.h"
#include <mmsyscom.h>

Board::Board(const int board_dimension, const int board_size, const int margin):
    kBoardDimension(board_dimension),kBoardSize(board_size),kMargin(margin),kGridSize((kBoardSize-2*kMargin)*1.0/(kBoardDimension-1)){
	printf("Board created: dimension=%d, size=%d, margin=%d, grid size=%.2f\n", kBoardDimension, kBoardSize, kMargin, kGridSize);
	board_state.resize(kBoardDimension, std::vector<ChessType>(kBoardDimension, kNoChess));
}

void Board::Init() {
	loadimage(&board_img, "asset/board.png", kBoardSize, kBoardSize);
	loadimage(&black_chess_img, "asset/black.png");
	loadimage(&white_chess_img, "asset/white.png");

	putimage(0, 0, &board_img);
}

static float distance(float x1, float y1, float x2, float y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

bool Board::Click(int x, int y, ChessPos *pos) {
	static const float offset = kGridSize * 0.3;
	int col = (x - kMargin) / kGridSize;
	int row = (y - kMargin) / kGridSize;

	auto CheckDis = [&](int _col, int _row) {
		float grid_x = kMargin + _col * kGridSize;
		float grid_y = kMargin + _row * kGridSize;
		if (distance(x, y, grid_x, grid_y) <= offset) {
			pos->col = _col;
			pos->row = _row;
			return true;
		}
		return false;
	};

	// Check the four nearest grid points
	if (CheckDis(col, row))return true;
	if (CheckDis(col + 1, row))return true;
	if (CheckDis(col, row + 1))return true;
	if (CheckDis(col + 1, row + 1))return true;
	
	return false;
}

void Board::ChessDown(const ChessPos *pos, ChessType) {

}