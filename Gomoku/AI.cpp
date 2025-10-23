#include <vector>
#include <map>
#include <deque>
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
		{ { 0,1,1,1,1,2 }, kSleepingFour }, { { 2,1,1,1,1,0 }, kSleepingFour },
		{ { 0,1,1,1,0,0 }, kActiveThree }, { { 0,0,1,1,1,0 }, kActiveThree },
		{ { 0,1,0,1,1,0 }, kActiveThree }, { { 0,1,1,0,1,0 }, kActiveThree },
		{ { 0,0,1,1,1,2 }, kSleepingThree }, { { 2,1,1,1,0,0 }, kSleepingThree },
		{ { 0,1,0,1,1,2 }, kSleepingThree }, { { 2,1,1,0,1,0 }, kSleepingThree },
		{ { 0,1,1,0,1,2 }, kSleepingThree }, { { 2,1,0,1,1,0 }, kSleepingThree },
		{ { 0,0,1,1,0,0 }, kActiveTwo },
		{ { 0,1,0,0,1,0 }, kActiveTwo },
		{ { 0,0,1,0,1,2 }, kSleepingTwo }, { { 2,1,0,1,0,0 }, kSleepingTwo },
		{ { 0,1,0,0,1,2 }, kSleepingTwo }, { { 2,1,0,0,1,0 }, kSleepingTwo },
		//five
		{ { 1,1,1,1,1 }, kFive },
		{ { 1,0,1,1,1 }, kSleepingFour }, { { 1,1,1,0,1 }, kSleepingFour },
		{ { 1,1,0,1,1 }, kSleepingFour },
		{ { 1,0,0,1,1 }, kSleepingThree }, { { 1,1,0,0,1 }, kSleepingThree },
		{ { 1,0,1,0,1 }, kSleepingThree },
		{ { 1,1,0,0,1 }, kSleepingThree }, { { 1,0,0,1,1 }, kSleepingThree },
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

int AI::CheckSeven(const std::deque<int> *seq) {
	return 0;
}

int AI::CheckSix(const std::deque<int> *seq) {
	return 0;
}

int AI::CheckFive(const std::deque<int> *seq) {
	return 0;
}

int AI::Evaluate(const vvector<PieceType>* board_state, PieceType type) {
	uint64_t hash = ZobristHash(board_state);
	if (transposition_table[type].count(hash))return transposition_table[type][hash];

	int score = 0;
	auto convert = [&](PieceType p) {
		if (p == kNoPiece)return 0;
		else return p == type ? 1 : 2;
		};
	auto Push = [&](std::deque<int>* seq, int x, int y) {
		if (x == -1 || y == -1 || x == kBoardDimension || y == kBoardDimension)
			seq->push_back(2);
		else seq->push_back(convert((*board_state)[x][y]));
		};
	auto Check = [&](std::deque<int>* seq, int len) {
		switch (len) {
		case 5:
			score += CheckFive(seq);
			score += CheckFive(seq);
			break;
		case 6:
			score += CheckSix(seq);
			score += CheckSix(seq);
			break;
		case 7:
			score += CheckSeven(seq);
			score += CheckSeven(seq);
			break;
		}
		};

	//horizontal and vertical
	for (int i = 0; i < kBoardDimension; ++i) {
		for (int len = 5, p; len <= 7; ++len) {
			std::deque<int> seq_h;
			std::deque<int> seq_v;
			for (p = -1; p <= kBoardDimension; ++p) {
				Push(&seq_h, i, p);
				Push(&seq_v, p, i);

				if (seq_h.size()>len) {
					seq_h.pop_front();
					seq_v.pop_front();
				}
				if (seq_h.size() < len)continue;

				Check(&seq_h, len);
				Check(&seq_v, len);
			}
		}
	}

	//diagonal
	vector<std::pair<int, int>>edge;
	for (int row = kBoardDimension, col = -1; row >= -1; --row)edge.push_back({ row,col });
	for (int row = -1, col = 0; col <= kBoardDimension; ++col) edge.push_back({ row,col });

	for (int len = 5; len <= 7; ++len) {
		for (auto &pair : edge) {
			std::deque<int>seq_main;
			std::deque<int>seq_anti;
			for (int x = pair.first, y = pair.second; max(x, y) <= kBoardDimension; ++x, ++y) {
				Push(&seq_main, x, y);
				Push(&seq_anti, kBoardDimension - 1 - x, y);

				if (seq_main.size() > len) {
					seq_main.pop_front();
					seq_anti.pop_front();
				}
				if (seq_main.size() < len)continue;

				Check(&seq_main, len);
				Check(&seq_anti, len);
			}
		}
	}

	return (transposition_table[type][hash] = score);
}

void AI::AlphaBeta() {

}

void AI::Init(Board *_board, PieceType _self_type) {
	board = _board;
	self_type = _self_type;
}

void AI::Move() {
	std::uniform_int_distribution<> dist_int(0, 12);

	PiecePos pos;
	while (true) {
		sim_board_state = board->get_board_state();
		Evaluate(&sim_board_state,kWhitePiece);
		Evaluate(&sim_board_state, kBlackPiece);
		pos = { dist_int(generator),dist_int(generator) };
		if (board->get_piece_type(&pos) != kNoPiece)continue;
		board->PlacePiece(&pos, self_type);
		break;
	}
}