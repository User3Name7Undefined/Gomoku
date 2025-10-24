#include "Player.h"
#include "Board.h"

void Player::Init(Board *_board, PieceType _self_type) {
	board = _board;
	self_type = _self_type;
	Voice(kStartGame);
}

void Player::Move() {
	ExMessage msg;
	GridPos pos;
	while(true){
		getmessage(&msg, EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN && board->Click(msg.x,msg.y,&pos)) {
			if (board->get_piece_type(&pos) != kNoPiece)continue;

			board->PlacePiece(&pos, self_type);
			//Voice(kPlacePiece);
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