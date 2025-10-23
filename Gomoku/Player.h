#pragma once
#include "graphics.h"

class Board;
enum PieceType;

enum VoiceType {
	kStartGame,
    kPlacePiece,
    kWin,
    kLose
};

class Player {
private:
    Board *board;
    PieceType use_type;
public:
    void Init(Board *_board, PieceType _use_type);
    void Move();
    void Voice(VoiceType voice);
};