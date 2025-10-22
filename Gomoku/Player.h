#pragma once
#include "graphics.h"

class Board;
enum ChessType;

enum VoiceType {
	kStartGame,
    kPlaceChess,
    kWin,
    kLose
};

class Player {
private:
    Board *board;
    ChessType use_type;
public:
    void Init(Board *_board);
    void Move();
    void Voice(VoiceType voice);
};