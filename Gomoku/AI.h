#pragma once
#include <map>
#include <vector>
#include <deque>
#include <array>
#include <random>

#include "TypeAliases.h"

class Board;
enum PieceType;

class AI {
private:
    Board* board;
    PieceType self_type;
    
    const int kBoardDimension;

    static std::mt19937_64 GenerateRandomGenerator();
    std::mt19937_64 generator;

    static vvvector<uint64_t> GenerateZobristTable(const int board_dimension, std::mt19937_64 gen);
    const vvvector<uint64_t> zobrist_table;
    uint64_t ZobristHash(const vvector<PieceType>* board_state);

    std::map<std::deque<int>, int> shape_score;
    int CheckSeven(const std::deque<int> *seq);
    int CheckSix(const std::deque<int> *seq);
    int CheckFive(const std::deque<int> *seq);
    int Evaluate(const vvector<PieceType>* board_state, PieceType type);
    std::map<uint64_t, int> transposition_table[2];

    std::vector<std::vector<PieceType>>sim_board_state;
    void AlphaBeta();

public:
    AI(const int _board_dimension);
    void Init(Board *_board, PieceType _self_type);
    void Move();
};