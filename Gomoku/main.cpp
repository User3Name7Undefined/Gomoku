#include<easyx.h>
#include "AI.h"
#include "Player.h"
#include "Board.h"
#include "Game.h"

int main(void) {
	AI ai;
	Player player;
	Board board(15, 895, 45);
	while (1) {
		PlayerType first_turn = kPlayer; // or kComputer
		Game game(player, ai, board, first_turn);
		game.Start();
		game.Run();
		game.End();
	}

	return 0;
}