#include<easyx.h>
#include "AI.h"
#include "Player.h"
#include "Board.h"
#include "Game.h"

int main(void) {
	AI ai;
	Player player;
	Board board(13, 895, 45, 61);
	initgraph(895, 895, EX_SHOWCONSOLE);
	while (true) {
		PlayerType first_turn = kPlayer; // or kComputer
		Game game(&player, &ai, &board, first_turn);
		game.Start();
		game.Run();
		game.End();
	}

	return 0;
}