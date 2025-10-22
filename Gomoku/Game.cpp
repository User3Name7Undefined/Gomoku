#include "Game.h"

Game::Game(Player& p, AI& a, Board& b, PlayerType turn)
    : player(p), ai(a), board(b), turn(turn) {
}

void Game::Start() {

}

void Game::Run() {
    while (1) {
        if (turn == PLAYER)
            player.Move();
        else
            ai.Move();

        if (CheckEnd())break;

        if (turn == PLAYER)
            turn = COMPUTER;
        else
            turn = PLAYER;
    }
}

bool Game::CheckEnd() {
    //if someone wins return true
    return false;
}

void Game::End() {
    if (state == SOMEONE_WIN) {
        //announce winner
    }
    else if (state == DRAW) {
        //announce draw
    }
}