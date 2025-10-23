#include <vector>
#include <map>
#include<random>

#include "AI.h"

AI::AI(const int _board_dimension) :zobrist_table(GenerateZobristTable(_board_dimension)) {

}

vvvull AI::GenerateZobristTable(const int board_dimension) {
	std::random_device rd;
	std::mt19937_64 gen(rd());

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

unsigned long long AI::ZobristHash() {
	return 0ll;
}

void AI::Init(Board *_board, PieceType _use_type) {
	board = _board;
	use_type = _use_type;
}

void AI::Move() {

}