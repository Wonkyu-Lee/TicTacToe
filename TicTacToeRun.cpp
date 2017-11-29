//
// Created by blazeq on 2017. 11. 29..
//

#include <iostream>
#include <cassert>
#include "TicTacToe.h"

namespace tic_tac_toe {

using namespace std;

void showSlotIndexes() {
    cout << "-----" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int slot = i * 3 + j;
            cout << slot << " ";
        }
        cout << endl;
    }
    cout << "-----" << endl;
};

void showBoard(const Game& game) {
    cout << "-----" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int slot = i * 3 + j;
            SlotState state = game.getSlotState(slot);
            char glyph;
            switch (state) {
                case SlotState::O: glyph = 'O'; break;
                case SlotState::X: glyph = 'X'; break;
                default: glyph = ' ';
            }
            cout << glyph << " ";
        }
        cout << endl;
    }
    cout << "-----" << endl;
};

bool askQuit() {
    cout << "Quit(y/n)? ";
    char answer;
    cin >> answer;
    bool quit = (answer == 'y');
    if (quit) {
        cout << "Bye~" << endl;
        return true;
    } else {
        cout << "Game start!" << endl;
        showSlotIndexes();
        return false;
    }
}

void run(Game* debugGame) {
    Game game;

    if (debugGame == nullptr) {
        cout << "Game start!" << endl;
        showSlotIndexes();
    } else {
        game = *debugGame;
        showBoard(game);
    }

    while (true) {
        GameState gameState = game.getGameState();
        if (gameState != GameState::PLAYING) {
            switch (gameState) {
                case GameState::O_WIN:
                    cout << "O win!" << endl;
                    break;
                case GameState::X_WIN:
                    cout << "X win!" << endl;
                    break;
                case GameState::DRAW:
                    cout << "Draw!" << endl;
                    break;
                default:
                    assert (false);
            }

            if (askQuit()) {
                break;
            } else {
                game.reset();
            }

        } else {
            if (game.willDraw(3)) {
                cout << "Eventually will draw!" << endl;
                if (askQuit()) {
                    break;
                } else {
                    game.reset();
                }
            }
        }

        while (true) {
            cout << (game.isXTurn() ? "X" : "O") << "'s turn -> ";
            int slot = -1;
            cin >> slot;
            if (game.mark(slot)) {
                break;
            } else {
                cout << "Error! Wrong slot!" << endl;
                continue;
            }
        }

        showBoard(game);
    }
}

void play(bool userIsX) {
    std::srand((unsigned int)time(nullptr));
    Game game;

    cout << "Game start!" << endl;
    showSlotIndexes();

    while (true) {
        bool userTurn = (game.isXTurn() && userIsX) || (!game.isXTurn() && !userIsX);

        GameState gameState = game.getGameState();
        if (gameState != GameState::PLAYING) {
            switch (gameState) {
                case GameState::O_WIN:
                    cout << "O win!" << endl;
                    break;
                case GameState::X_WIN:
                    cout << "X win!" << endl;
                    break;
                case GameState::DRAW:
                    cout << "Draw!" << endl;
                    break;
                default:
                    assert (false);
            }

            if (askQuit()) {
                break;
            } else {
                game.reset();
            }

        } else {
            bool gameOver = false;
            if (game.willDraw(3)) {
                cout << "Eventually will draw!" << endl;
                gameOver = true;
            }
            if (userTurn) {
                auto mustSLots = game.getSlotsThatMustBeBlocked();
                if (1 < mustSLots.size()) {
                    char who = (game.isXTurn() ? 'X' : 'O');
                    cout << "Eventually " << who <<" will lose!" << endl;
                    gameOver = true;
                }
            }

            if (gameOver) {
                if (askQuit()) {
                    break;
                } else {
                    game.reset();
                }
            }
        }

        cout << (game.isXTurn() ? "X" : "O") << "'s turn -> ";
        if (userTurn) {
            while (true) {
                int slot = -1;
                cin >> slot;
                if (game.mark(slot)) {
                    break;
                } else {
                    cout << "Error! Wrong slot!" << endl;
                    cout << (game.isXTurn() ? "X" : "O") << "'s turn -> ";
                    continue;
                }
            }
        } else {
            auto mustSlots = game.getSlotsThatMustBeBlocked();
            int nextSlot;
            if (mustSlots.empty()) {
                auto emptySlots = game.getEmptySlots();
                size_t slot = std::rand() % emptySlots.size();
                nextSlot = emptySlots[slot];
            } else {
                nextSlot = mustSlots.front();
            }

            cout << nextSlot << endl;
            bool success = game.mark(nextSlot);
            assert (success);
        }

        showBoard(game);
    }
}

} // namespace tic_tac_toe