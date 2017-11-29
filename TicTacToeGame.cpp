//
// Created by blazeq on 2017. 11. 29..
//

#include "TicTacToe.h"

namespace tic_tac_toe {

using namespace std;

namespace {

bool _willDraw(Game& g, int depth) {
    switch (g.getGameState()) {
        case GameState::DRAW: {
            return true;
        }
        case GameState::PLAYING: {
            if (depth == 0) {
                return false;
            }
            auto emptySlots = g.getEmptySlots();
            for (auto slot : emptySlots) {
                g.mark(slot);
                if (!_willDraw(g, depth - 1)) {
                    return false;
                }
                g.rollback();
            }
            return true;
        }
        default : {
            return false;
        }
    }
};

} // namespace

Game::Game()
: _xTurn(true)
{
}

SlotState Game::getSlotState(int slot) const {
    if (slot < 0 || SLOT_COUNT <= slot) {
        return SlotState::INVALID;
    }

    return _slotStates[slot];
}

bool Game::mark(int slot) {
    if (slot < 0 || SLOT_COUNT <= slot) {
        return false;
    }

    if (_slotStates[slot] != SlotState::EMPTY) {
        return false;
    }

    _slotStates[slot] = _xTurn ? SlotState::X : SlotState::O;
    _xTurn = !_xTurn;
    _slotStack.push(slot);
    return true;
}

bool Game::rollback() {
    if (_slotStates.empty()) {
        return false;
    }

    int lastMarked = _slotStack.top();
    _slotStack.pop();

    _slotStates[lastMarked] = SlotState::EMPTY;
    _xTurn = !_xTurn;
    return true;
}

bool Game::isXTurn() const {
    return _xTurn;
}

const std::vector<SlotState>& Game::getSlotStates() const {
    return _slotStates;
}

GameState Game::getGameState() const {
    auto isAll = [&](SlotState slotState, int s1, int s2, int s3) {
        return _slotStates[s1] == slotState && _slotStates[s2] == slotState && _slotStates[s3] == slotState;
    };

    auto hasLine = [&](SlotState slotState) {
        return  isAll(slotState, 0, 1, 2) ||
                isAll(slotState, 3, 4, 5) ||
                isAll(slotState, 6, 7, 8) ||
                isAll(slotState, 0, 3, 6) ||
                isAll(slotState, 1, 4, 7) ||
                isAll(slotState, 2, 5, 8) ||
                isAll(slotState, 0, 4, 8) ||
                isAll(slotState, 2, 4, 6);
    };

    auto isFull = [&]() {
        for (int i = 0; i < SLOT_COUNT; ++i) {
            if (_slotStates[i] == SlotState::EMPTY)
                return false;
        }
        return true;
    };

    if (hasLine(SlotState::X)) {
        return GameState::X_WIN;
    } else if (hasLine(SlotState::O)) {
        return GameState::O_WIN;
    } else if (isFull()) {
        return GameState::DRAW;
    } else {
        return GameState::PLAYING;
    }
}

std::vector<int> Game::getEmptySlots() const {
    std::vector<int> emptySlots;
    for (int i = 0; i < SLOT_COUNT; ++i) {
        if (_slotStates[i] == SlotState::EMPTY) {
            emptySlots.push_back(i);
        }
    }

    return emptySlots;
}

std::vector<int> Game::getSlotsThatMustBeBlocked() const {
    std::vector<int> result;
    Game game = *this;
    SlotState opposite  = game.isXTurn() ? SlotState::O : SlotState::X;
    GameState oppositeWin = game.isXTurn() ? GameState::O_WIN : GameState::X_WIN;

    for (int i = 0; i < SLOT_COUNT; ++i) {
        if (game.getSlotState(i) == SlotState::EMPTY) {
            game._slotStates[i] = opposite;
            if (game.getGameState() == oppositeWin) {
                result.push_back(i);
            }
            game._slotStates[i] = SlotState::EMPTY;
        }
    }

    return result;
}

void Game::reset() {
    _xTurn = true;
    for (auto& slot : _slotStates) {
        slot = SlotState::EMPTY;
    }
}

bool Game::willDraw(int limit) const {
    Game game = *this;
    return _willDraw(game, limit);
}

} // namespace tic_tac_toe