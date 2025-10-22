#include "Board.h"

Board::Board(const int board_dimension, const int board_size, const int margin):
    kBoardDimension(board_dimension),kBoardSize(board_size),kMargin(margin),kGridSize((kBoardDimension-2*kMargin)*1.0/(kBoardSize-1)){
}

bool Board::Click(int x, int y, ChessPos& pos) {
    return true;
}

void Board::ChessDown(const ChessPos& pos, ChessType) {

}