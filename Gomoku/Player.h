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
    PieceType self_type;
public:
    void Init(Board *_board, PieceType _self_type);
    void Move();
    void Voice(VoiceType voice);
};