#include "TicTacToe.h"

int main()
{
    //tic_tac_toe::play(false);

    tic_tac_toe::Game game;
    game.mark(4);
    game.mark(0);
    game.mark(5);
    game.mark(3);
    game.mark(6);
    game.mark(2);

    tic_tac_toe::run(&game);
    return 0;
}