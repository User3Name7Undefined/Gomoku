#include <vector>
#include <map>
#include<random>

#include "AI.h"
#include "Board.h"

enum Shape {
	kFive = 50,
	kActiveFour = 27,
	kSleepingFour = 8,
	kActiveThree = 9,
	kSleepingThree = 4,
	kActiveTwo = 3,
	kSleepingTwo = 2,
};

AI::AI(const int board_dimension):kBoardDimension(board_dimension),
	generator(GenerateRandomGenerator()), zobrist_table(GenerateZobristTable(board_dimension, generator)) {
	shape_score = {
		//seven
		{ { 2,0,1,1,1,0,2 }, kSleepingThree },
		//six
		{ { 0,1,1,1,1,0 }, kActiveFour },
		{ { 0,1,1,1,1,2 }, kSleepingFour },
		{ { 0,1,1,1,0,0 }, kActiveThree },
		{ { 0,1,0,1,1,0 }, kActiveThree },
		{ { 0,0,1,1,1,2 }, kSleepingThree },
		{ { 0,1,0,1,1,2 }, kSleepingThree },
		{ { 0,1,1,0,1,2 }, kSleepingThree },
		{ { 0,0,1,1,0,0 }, kActiveTwo },
		{ { 0,1,0,0,1,0 }, kActiveTwo },
		{ { 0,0,1,0,1,2 }, kSleepingTwo },
		{ { 0,1,0,0,1,2 }, kSleepingTwo },
		//five
		{ { 1,1,1,1,1 }, kFive },
		{ { 1,0,1,1,1 }, kSleepingFour },
		{ { 1,1,0,1,1 }, kSleepingFour },
		{ { 1,0,0,1,1 }, kSleepingThree }, 
		{ { 1,0,1,0,1 }, kSleepingThree },
		{ { 1,1,0,0,1 }, kSleepingThree },
		{ { 0,1,0,1,0 }, kActiveTwo },
		{ { 1,0,0,0,1 }, kSleepingTwo },
	};
}

std::mt19937_64 AI::GenerateRandomGenerator() {
	std::random_device rd;
	std::array<uint32_t, 8> seed_data{};
	for (auto& elem : seed_data) {
		elem = rd();
	}
	std::seed_seq seq(seed_data.begin(), seed_data.end());
	return std::mt19937_64(seq);
}

vvvector<uint64_t> AI::GenerateZobristTable(const int board_dimension, std::mt19937_64 gen) {
	vvvector<uint64_t> table;
	for (int i = 0; i < board_dimension; ++i) {
		vvector<uint64_t> row;
		for (int j = 0; j < board_dimension; ++j) {
			vector<uint64_t> col;
			for (int k = 0; k < 3; ++k) {
				col.push_back(gen());
			}
			row.push_back(col);
		}
		table.push_back(row);
	}
	return table;
}

uint64_t AI::ZobristHash(const vvector<PieceType> *board_state) {
	uint64_t hash = 0;
	for (int i = 0; i < kBoardDimension; ++i) {
		for(int j = 0; j < kBoardDimension; ++j){
			PieceType type = (*board_state)[i][j];
			hash ^= zobrist_table[i][j][type];
		}
	}
	return hash;
}

int AI::CheckSeven(vvector<PieceType> *board_state) {

}

int AI::CheckSix(vvector<PieceType>* board_state) {

}

int AI::CheckFive(vvector<PieceType>* board_state) {
	//horizontal
	for(int i=0;i<kBoardDimension;++i){
		for(int j=-1;j+5-1<=kBoardDimension;++j){
			
		}
	}
	//vertical

	//diagonal
}

int AI::Evaluate(const vvector<PieceType> *board_state) {
	uint64_t hash = ZobristHash(board_state);
	if (transposition_table.count(hash))return transposition_table[hash];

	return 0;
}

void AI::AlphaBeta() {

}

void AI::Init(Board *_board, PieceType _use_type) {
	board = _board;
	use_type = _use_type;
}

void AI::Move() {
	std::uniform_int_distribution<> dist_int(0, 12);

	PiecePos pos;
	while (true) {
		pos = { dist_int(generator),dist_int(generator) };
		if (board->get_piece_type(&pos) != kNoPiece)continue;
		board->PlacePiece(&pos, use_type);
		break;
	}
}