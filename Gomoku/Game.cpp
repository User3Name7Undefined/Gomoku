#include "Player.h"
#include "AI.h"
#include "Board.h"
#include "Game.h"

Game::Game(Player *p, AI *a, Board *b, PlayerType turn)
    : player(p), ai(a), board(b), turn(turn){
}

void Game::Start() {
    board->Init();
	player->Init(board, turn == kPlayer?kBlackPiece : kWhitePiece);
	ai->Init(board, turn == kComputer?kBlackPiece : kWhitePiece);
    printf("Player use %s\n", turn == kPlayer ? "black" : "white");
    printf("Computer use %s\n", turn == kComputer ? "black" : "white");
}

void Game::Run() {
    while (1) {
        if (turn == kPlayer)
            player->Move(), printf("Need move\n");
        else
            ai->Move();

        if (board->CheckEnd()!=0)break;

        if (turn == kPlayer)
            turn = kComputer;
        else
            turn = kPlayer;
    }
}

void Game::End() {
    printf("Game over\n");
    if (turn == kPlayer) {
        player->Voice(kWin);
    } else {
        player->Voice(kLose);
    }
    Sleep(5000);
}