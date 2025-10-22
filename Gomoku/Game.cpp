#include "Player.h"
#include "AI.h"
#include "Board.h"
#include "Game.h"

Game::Game(Player& p, AI& a, Board& b, PlayerType turn)
    : player(p), ai(a), board(b), turn(turn), state(kRunning){
}

void Game::Start() {
    board.Init();
}

void Game::Run() {
    while (1) {
        if (turn == kPlayer)
            player.Move();
        else
            ai.Move();

        if (CheckEnd())break;

        if (turn == kPlayer)
            turn = kComputer;
        else
            turn = kPlayer;
    }
}

bool Game::CheckEnd() {
    //if someone wins return true
    return false;
}

void Game::End() {
    if (state == kSomeoneWin) {
        //announce winner
    }
    else if (state == kDraw) {
        //announce draw
    }
}