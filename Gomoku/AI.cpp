#include <vector>
#include <map>
#include<random>

#include "AI.h"
#include "Board.h"

AI::AI(const int board_dimension):kBoardDimension(board_dimension),
	generator(GenerateRandomGenerator()), zobrist_table(GenerateZobristTable(board_dimension, generator)) {
	
}

vvvull AI::GenerateZobristTable(const int board_dimension, std::mt19937_64 gen) {
	vvvull table;
	for (int i = 0; i < board_dimension; ++i) {
		vvull row;
		for (int j = 0; j < board_dimension; ++j) {
			vull col;
			for (int k = 0; k < 3; ++k) {
				col.push_back(gen());
			}
			row.push_back(col);
		}
		table.push_back(row);
	}
	return table;
}

void AI::AlphaBeta() {

}

uint64_t AI::ZobristHash() {
	uint64_t hash = 0;
	PiecePos pos;
	for (int i = 0; i < kBoardDimension; ++i) {
		for(int j=0;j<kBoardDimension;++j){
			pos = { i,j };
			PieceType type = board->get_piece_type(&pos);
			hash ^= zobrist_table[i][j][type];
		}
	}
	return hash;
}

void AI::Init(Board *_board, PieceType _use_type) {
	board = _board;
	use_type = _use_type;
}

void AI::Move() {
	std::uniform_int_distribution<> dist_int(0, 12);
	int num[13] = {};
	for (int i = 1; i <= 1000; ++i) {
		num[dist_int(generator)] ++;
	}
	for (int i = 0; i < 13; ++i)printf("%d ", num[i]);
	printf("\n");

	PiecePos pos;
	while (true) {
		pos = { dist_int(generator),dist_int(generator) };
		if (board->get_piece_type(&pos) != kNoPiece)continue;
		board->PlacePiece(&pos, use_type);
		break;
	}
}