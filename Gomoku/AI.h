#pragma once
#include <map>
#include <vector>
#include <array>
#include <random>

class Board;
enum PieceType;

typedef std::vector<std::vector<std::vector<uint64_t>>> vvvull;
typedef std::vector<std::vector<uint64_t>> vvull;
typedef std::vector<uint64_t> vull;

class AI {
private:
    Board* board;
    PieceType use_type;
    
    const int kBoardDimension;


    static std::mt19937_64 GenerateRandomGenerator() {
        std::random_device rd;
        std::array<uint32_t, 8> seed_data{};
        for (auto& elem : seed_data) {
            elem = rd();
        }
        std::seed_seq seq(seed_data.begin(), seed_data.end());
        return std::mt19937_64(seq);
	}
    std::mt19937_64 generator;

    static vvvull GenerateZobristTable(const int board_dimension, std::mt19937_64 gen);
    const vvvull zobrist_table;

	std::map<uint64_t, int> transposition_table;

    void AlphaBeta();
    uint64_t ZobristHash();

public:
    AI(const int _board_dimension);
    void Init(Board *_board, PieceType _use_type);
    void Move();
};