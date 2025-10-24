#include <vector>
#include <map>
#include <deque>
#include<random>

#include "AI.h"
#include "Board.h"

#define INF 998244353

const std::map<std::deque<int>, int> AI::shape_score = {
	//seven
	{ { 2,0,1,1,1,0,2 }, kSleepingThree },
	{ { 2,0,1,1,1,0,0 }, kActiveThree }, { {0,0,1,1,1,0,2}, kActiveThree},
	{ { 0,0,1,1,1,0,0 }, kActiveThree },
	//six
	{ { 0,1,1,1,1,0 }, kActiveFour },
	{ { 0,1,1,1,1,2 }, kSleepingFour }, { { 2,1,1,1,1,0 }, kSleepingFour },
	{ { 0,1,0,1,1,0 }, kActiveThree }, { { 0,1,1,0,1,0 }, kActiveThree },
	{ { 0,0,1,1,1,2 }, kSleepingThree }, { { 2,1,1,1,0,0 }, kSleepingThree },
	{ { 0,1,0,1,1,2 }, kSleepingThree }, { { 2,1,1,0,1,0 }, kSleepingThree },
	{ { 0,1,1,0,1,2 }, kSleepingThree }, { { 2,1,0,1,1,0 }, kSleepingThree },
	{ { 0,0,1,1,0,0 }, kActiveTwo },
	{ { 0,0,1,1,0,2 }, kActiveTwo }, { { 2,0,1,1,0,0 }, kActiveTwo },
	{ { 0,1,0,0,1,0 }, kActiveTwo },
	{ { 0,0,0,1,1,2 }, kSleepingTwo }, { { 2,1,1,0,0,0 }, kSleepingTwo },
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

AI::AI(const int board_dimension, const int search_depth) :kBoardDimension(board_dimension), kSearchDepth(search_depth),
generator(GenerateRandomGenerator()), zobrist_table(GenerateZobristTable(board_dimension, generator)) {
	
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

uint64_t AI::ZobristHash(const vvector<PieceType>* board_state) {
	uint64_t hash = 0;
	for (int i = 0; i < kBoardDimension; ++i) {
		for (int j = 0; j < kBoardDimension; ++j) {
			PieceType type = (*board_state)[i][j];
			hash ^= zobrist_table[i][j][type];
		}
	}
	return hash;
}

int AI::CheckSeven(const std::deque<int>* seq) {
	if (shape_score.count(*seq))return shape_score.at(*seq);
	else return 0;
}

int AI::CheckSix(const std::deque<int>* seq) {
	if (shape_score.count(*seq))return shape_score.at(*seq);
	return 0;
}

int AI::CheckFive(const std::deque<int>* seq) {
	if (shape_score.count(*seq))return shape_score.at(*seq);
	return 0;
}

int AI::Evaluate(const vvector<PieceType>* board_state, PieceType type) {
	//Regard type as self type, evaluate the score.

	uint64_t hash = ZobristHash(board_state);
	if (transposition_table[type].count(hash))return transposition_table[type][hash];

	int score = 0;
	auto convert = [&](int x,int y) {
		if (x == -1 || y == -1 || x == kBoardDimension || y == kBoardDimension) return 2;
		if ((*board_state)[x][y] == kNoPiece)return 0;
		else return (*board_state)[x][y] == type ? 1 : 2;
		};
	auto Push = [&](std::deque<int>* seq, int x, int y) {
		seq->push_back(convert(x, y));
		};
	auto Check = [&](std::deque<int> *seq, int len) {
		switch (len) {
		case 5:
			score += CheckFive(seq);
			break;
		case 6:
			score += CheckSix(seq);
			break;
		case 7:
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

				if (seq_h.size() > len) {
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

	for (auto& pair : edge) {
		for (int len = 5; len <= 7; ++len) {
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

double AI::AlphaBeta(PieceType type, double limit, int depth, GridPos* chosen_pos) {	//kBlackPiece->max kWhitePiece->min
	//If depth exceed the limit, return.
	if (depth > kSearchDepth) {
		double ret;
		if (self_type == kBlackPiece)
			ret = Evaluate(&sim_board_state, kBlackPiece) -
			Evaluate(&sim_board_state, kWhitePiece) * defense_Preference;
		else
			ret = Evaluate(&sim_board_state, kBlackPiece) * defense_Preference -
			Evaluate(&sim_board_state, kWhitePiece);

		return ret;
	}

	//Find out candidate points.
	vector<std::pair<int, int>> candidate_points;
	vvector<int>prefix(kBoardDimension, vector<int>(kBoardDimension, 0));
	for (int i = 0; i < kBoardDimension; ++i) {
		for (int j = 0; j < kBoardDimension; ++j) {
			if (i > 0)prefix[i][j] += prefix[i - 1][j];
			if (j > 0)prefix[i][j] += prefix[i][j - 1];
			if (i > 0 && j > 0)prefix[i][j] -= prefix[i - 1][j - 1];
			prefix[i][j] += ((sim_board_state)[i][j] != kNoPiece);
		}
	}

	auto query_pre = [&](int lx, int rx, int ly, int ry) {
		int ans = 0;
		ans += prefix[rx][ry];
		if (lx > 0)ans -= prefix[lx - 1][ry];
		if (ly > 0)ans -= prefix[rx][ly - 1];
		if (lx > 0 && ly > 0)ans += prefix[lx - 1][ly - 1];
		return ans;
		};

	for (int i = 0; i < kBoardDimension; ++i) {
		for (int j = 0; j < kBoardDimension; ++j) {
			if (sim_board_state[i][j] != kNoPiece)continue;
			int lx = max(0, i - 4); int rx = min(i + 4, kBoardDimension - 1);
			int ly = max(0, j - 4); int ry = min(j + 4, kBoardDimension - 1);
			bool flag = false;
			if (query_pre(lx, rx, ly, ry) > 0) {	//Near other points.
				candidate_points.push_back({ i,j });
			}
		}
	}

	if (candidate_points.empty()) {	//AI moves first.
		candidate_points.push_back({ kBoardDimension / 2 + 1,kBoardDimension / 2 + 1 });
	}

	double this_limit = type == kBlackPiece ? -INF : INF;//Black -> max, White -> min

	for (auto& point : candidate_points) {
		int row = point.first;
		int col = point.second;
		sim_board_state[row][col] = type;	//Simulate the move.
		double ans = AlphaBeta(type == kBlackPiece ? kWhitePiece : kBlackPiece, this_limit, depth + 1, chosen_pos);	//Calculate next layer.
		sim_board_state[row][col] = kNoPiece;//Trace back.

		if (type == kBlackPiece) {	//Max layer.
			if (this_limit < ans) {	//Maximize this_limit.
				this_limit = ans;
				chosen_pos->row = row;
				chosen_pos->col = col;
			}
			if (this_limit > limit) return this_limit;	//Prune. No need to search next layer anymore.
		}
		else if (type == kWhitePiece) {	//Min layer.
			if (this_limit > ans) {	//Minimize this_limit.
				this_limit = ans;
				chosen_pos->row = row;
				chosen_pos->col = col;
			}
			if (this_limit < limit) return this_limit;	//Prune. No need to search next layer anymore.
		}
	}

	return this_limit;
}

void AI::Init(Board* _board, PieceType _self_type) {
	board = _board;
	self_type = _self_type;
}

#include <iostream>

void AI::Move() {
	GridPos pos;
	
	sim_board_state = board->get_board_state();	//Initialize the simulation board.
	printf("The best move's evaluation is %.2f.\n", AlphaBeta(self_type, self_type == kBlackPiece ? -INF : INF, 0, &pos));	//Choose the best point.
	printf("Choose to put at {%d,%d}.\n\n", pos.row, pos.col);
	board->PlacePiece(&pos, self_type);
	sim_board_state = board->get_board_state();
	std::cout << ZobristHash(&sim_board_state) << std::endl;
}