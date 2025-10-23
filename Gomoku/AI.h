#pragma once
#include <map>
#include <vector>
#include <array>
#include <random>

#include "TypeAliases.h"

class Board;
enum PieceType;

class AI {
private:
    Board* board;
    PieceType use_type;
    
    const int kBoardDimension;

    static std::mt19937_64 GenerateRandomGenerator();
    std::mt19937_64 generator;

    static vvvector<uint64_t> GenerateZobristTable(const int board_dimension, std::mt19937_64 gen);
    const vvvector<uint64_t> zobrist_table;
    uint64_t ZobristHash(const vvector<PieceType>* board_state);

    std::map<vector<int>, int> shape_score;
    int CheckSeven(vvector<PieceType> *board_state);
    int CheckSix(vvector<PieceType> *board_state);
    int CheckFive(vvector<PieceType> *board_state);
    int Evaluate(const vvector<PieceType> *board_state);
    std::map<uint64_t, int> transposition_table;

    std::vector<std::vector<PieceType>>sim_board_state;
    void AlphaBeta();

public:
    AI(const int _board_dimension);
    void Init(Board *_board, PieceType _use_type);
    void Move();
};