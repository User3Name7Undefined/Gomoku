#include "Board.h"
#include <mmsyscom.h>

Board::Board(const int board_dimension, const int board_size, const int margin):
    kBoardDimension(board_dimension),kBoardSize(board_size),kMargin(margin),kGridSize((kBoardDimension-2*kMargin)*1.0/(kBoardSize-1)){
	board_state.resize(kBoardDimension, std::vector<ChessType>(kBoardDimension, kNoChess));
}

void Board::Init() {
	initgraph(kBoardSize, kBoardSize);
	loadimage(&board_img, "asset/board.png", kBoardSize, kBoardSize);
	loadimage(&black_chess_img, "asset/black.png");
	loadimage(&white_chess_img, "asset/white.png");

	for(int i=0;i<kBoardDimension;++i){
		for(int j=0;j<kBoardDimension;++j){
			board_state[i][j] = kNoChess;
		}
	}

	putimage(0, 0, &board_img);
	mciSendString("play asset/game_start.mp3", NULL, 0, NULL);
}

bool Board::Click(int x, int y, ChessPos& pos) {
    return true;
}

void Board::ChessDown(const ChessPos& pos, ChessType) {

}