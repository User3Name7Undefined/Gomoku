#include "Player.h"
#include "Board.h"

void Player::Init(Board *_board, PieceType _use_type) {
	board = _board;
	use_type = _use_type;
	Voice(kStartGame);
}

void Player::Move() {
	ExMessage msg;
	PiecePos pos;
	while(true){
		getmessage(&msg, EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN && board->Click(msg.x,msg.y,&pos)) {
			if (board->get_piece_type(&pos) != kNoPiece)continue;

			board->PlacePiece(&pos, use_type);
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