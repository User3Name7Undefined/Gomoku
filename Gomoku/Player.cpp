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
			Voice(kPlacePiece);
			break;
		}
	}
	
}

void Player::Voice(VoiceType voice){
	switch (voice) {
	case kStartGame:
		mciSendString("play asset/player_game_start.mp3", NULL, 0, NULL);
		break;
	case kPlacePiece: {
		int chosen = rand() % 5;
		switch (chosen) {
		case 0:mciSendString("play asset/player_battle1.mp3", NULL, 0, NULL); break;
		case 1:mciSendString("play asset/player_battle2.mp3", NULL, 0, NULL); break;
		case 2:mciSendString("play asset/player_battle3.mp3", NULL, 0, NULL); break;
		case 3:mciSendString("play asset/player_battle4.mp3", NULL, 0, NULL); break;
		case 4:mciSendString("play asset/player_battle5.mp3", NULL, 0, NULL); break;
		}
		break;
	}
	case kWin:
		mciSendString("play asset/player_win.mp3", NULL, 0, NULL);
		break;
	case kLose:
		mciSendString("play asset/player_lose.mp3", NULL, 0, NULL);
		break;
	}
}