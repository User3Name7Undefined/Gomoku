#include "Player.h"
#include "Board.h"

void Player::Init(Board *_board) {
	Voice(kStartGame);
	board = _board;
}

void Player::Move() {
	ExMessage msg;
	ChessPos pos;
	while(true){
		getmessage(&msg, EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN && board->Click(msg.x,msg.y,&pos)) {
			board->ChessDown(&pos, use_type);
			//Voice(kPlaceChess);
			Voice(kStartGame);
			break;
		}
	}
	
}

void Player::Voice(VoiceType voice){
	switch (voice) {
	case kStartGame:
		mciSendString("play asset/player_game_start.mp3", NULL, 0, NULL);
		break;
	}
}