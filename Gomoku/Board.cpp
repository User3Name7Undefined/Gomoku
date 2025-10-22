#include "Board.h"
#include <mmsyscom.h>

Board::Board(const int board_dimension, const int board_size, const int margin):
    kBoardDimension(board_dimension),kBoardSize(board_size),kMargin(margin),kGridSize((kBoardDimension-2*kMargin)*1.0/(kBoardSize-1)){
	board_state.resize(kBoardDimension, std::vector<ChessType>(kBoardDimension, kNoChess));
}

void Board::Init() {
	loadimage(&board_img, "asset/board.png", kBoardSize, kBoardSize);
	loadimage(&black_chess_img, "asset/black.png");
	loadimage(&white_chess_img, "asset/white.png");

	putimage(0, 0, &board_img);
}

bool Board::Click(int x, int y, ChessPos *pos) {
    return true;
}

void Board::ChessDown(const ChessPos *pos, ChessType) {

}