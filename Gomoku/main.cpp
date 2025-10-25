#include<easyx.h>
#include "AI.h"
#include "Player.h"
#include "Board.h"
#include "Game.h"

int main(void) {
	AI ai(15,3);
	Player player;
	Board board(15, 800, 40, 40, double(720)/14, 40);

	initgraph(800, 800, EX_SHOWCONSOLE);

	while (true) {
		PlayerType first_turn = kComputer; // or kComputer
		Game game(&player, &ai, &board, first_turn);
		game.Start();
		game.Run();
		game.End();
	}

	return 0;
}