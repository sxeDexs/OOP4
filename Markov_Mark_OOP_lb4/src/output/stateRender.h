#ifndef STATE_RENDER_H
#define STATE_RENDER_H

#include <string>
#include "../game.h"

template<typename FieldRender, typename MessageRender>
class StateRender {
private:
    GameRender<FieldRender, MessageRender> game_render; 
    std::string current_state; 

public:
    StateRender(Game &game) : game_render(game), current_state("") {}

    void update(const std::string &state);

    std::string get_current_state() const;
};

template<typename FieldRender, typename MessageRender>
void StateRender<FieldRender, MessageRender>::update(const std::string &state) {
    current_state = state;
    game_render.update(state);
}

template<typename FieldRender, typename MessageRender>
std::string StateRender<FieldRender, MessageRender>::get_current_state() const {
    return current_state;
}

#endif