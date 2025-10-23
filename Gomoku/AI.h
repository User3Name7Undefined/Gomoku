#pragma once
#include <map>
#include <vector>
#include <array>

class Board;
enum PieceType;

typedef std::vector<std::vector<std::vector<unsigned long long>>> vvvull;
typedef std::vector<std::vector<unsigned long long>> vvull;
typedef std::vector<unsigned long long> vull;

class AI {
private:
    Board* board;
    PieceType use_type;
    const vvvull zobrist_table;
	std::map<unsigned long long, int> transposition_table;

	static vvvull GenerateZobristTable(const int board_dimension);
    void AlphaBeta();
	unsigned long long ZobristHash();

public:
    AI(const int _board_dimension);
    void Init(Board *_board, PieceType _use_type);
    void Move();
};