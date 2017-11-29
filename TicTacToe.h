//
// Created by blazeq on 2017. 11. 29..
//

#ifndef TICTACTOE_TICTACTOE_H
#define TICTACTOE_TICTACTOE_H

#include <vector>
#include <stack>

namespace tic_tac_toe {

const int SLOT_COUNT = 9;
enum class SlotState { INVALID = -1,  EMPTY, X, O };
enum class GameState { PLAYING, X_WIN, O_WIN, DRAW };

class Game {
public:
    Game();
    SlotState getSlotState(int slot) const;
    GameState getGameState() const;
    bool mark(int slot);
    bool rollback();
    bool isXTurn() const;
    const std::vector<SlotState>& getSlotStates() const;
    std::vector<int> getEmptySlots() const;
    std::vector<int> getSlotsThatMustBeBlocked() const;
    void reset();

    bool willDraw(int limit) const;

private:
    bool _xTurn;
    std::vector<SlotState> _slotStates{9, SlotState::EMPTY};
    std::stack<int> _slotStack;
};

void run(Game* debugGame = nullptr);
void play(bool userIsX);

} // namespace tic_tac_toe

#endif //TICTACTOE_TICTACTOE_H
