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

int AI::EvaluateForType(const vvector<PieceType>* board_state, PieceType type) {
	int score = 0;

	//horizontal and vertical
	for (int i = 0; i < kBoardDimension; ++i) {
		for (int len = 5, p; len <= 7; ++len) {
			std::deque<int> seq_h;
			std::deque<int> seq_v;
			for (p = -1; p <= kBoardDimension; ++p) {
				if (p == -1 || p == kBoardDimension) {
					/*seq_h.push_back(2);
					seq_v.push_back(2);*/
					seq_h.push_back(p);
					seq_v.push_back(p);
				}
				else {
					seq_h.push_back(p);
					seq_v.push_back(p);
					/*if ((*board_state)[i][p] == kNoPiece) seq_h.push_back(0);
					else seq_h.push_back(((*board_state)[i][p] == type) ? 1 : 2);*/
					/*if ((*board_state)[p][i] == kNoPiece) seq_v.push_back(0);
					else seq_v.push_back(((*board_state)[p][i] == type) ? 1 : 2);*/
				}
				if (p >= len - 1) {
					seq_h.pop_front();
					seq_v.pop_front();
				}
				if (p < len - 2)continue;
				/*for (auto& x : seq_h) {
					board->DebugCircle(i, x);
				}
				for (auto& x : seq_v) {
					board->DebugCircle(x, i);
				}
				Sleep(50);
				cleardevice();*/
				switch (len) {
				case 5: score += CheckFive(&seq_h); CheckFive(&seq_v); break;
				case 6: score += CheckSix(&seq_h); CheckSix(&seq_v); break;
				case 7: score += CheckSeven(&seq_h); CheckSeven(&seq_v);  break;
				}
			}
		}
	}

	//diagonal
	vector<std::pair<int, int>>edge;
	for (int row = kBoardDimension, col = -1; row >= -1; --row)edge.push_back({ row,col });
	for (int row = -1, col = 0; col <= kBoardDimension; ++col) edge.push_back({ row,col });

	for (int len = 5; len <= 7; ++len) {
		for (auto &pair : edge) {
			printf("%d %d\n", pair.first, pair.second);
			std::deque<std::pair<int, int>>seq_main;
			std::deque<std::pair<int, int>>seq_anti;
			for (int x = pair.first, y = pair.second; max(x, y) <= kBoardDimension; ++x, ++y) {
				if (x == -1 || y == -1 || x == kBoardDimension || y == kBoardDimension) {
					seq_main.push_back({ x,y });
					seq_anti.push_back({ kBoardDimension - 1 - x,y });
				}
				else {
					seq_main.push_back({ x,y });
					seq_anti.push_back({ kBoardDimension - 1 - x,y });
				}

				if (seq_main.size() > len) {
					seq_main.pop_front();
					seq_anti.pop_front();
				}
				if (seq_main.size() < len)continue;

				for (auto& pair : seq_main) {
					int a = pair.first;
					int b = pair.second;
					board->DebugCircle(a, b);
				}
				for (auto& pair : seq_anti) {
					int a = pair.first;
					int b = pair.second;
					board->DebugCircle(a, b);
				}
				Sleep(10);
				cleardevice();
			}
		}
	}
	return 0;
}

double AI::Evaluate(const vvector<PieceType> *board_state) {
	static double self_weight = 1.0;
	static double oppo_weight = 1.0;

	uint64_t hash = ZobristHash(board_state);
	if (transposition_table.count(hash))return transposition_table[hash];
	
	PieceType oppo_type = (self_type == kBlackPiece) ? kWhitePiece : kBlackPiece;

	return EvaluateForType(board_state, self_type) * self_weight
		- EvaluateForType(board_state, oppo_type) * oppo_weight;
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
		EvaluateForType(&sim_board_state,kWhitePiece);
		pos = { dist_int(generator),dist_int(generator) };
		if (board->get_piece_type(&pos) != kNoPiece)continue;
		board->PlacePiece(&pos, self_type);
		break;
	}
}