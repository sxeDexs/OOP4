#ifndef MESSAGE_RENDERER_H
#define MESSAGE_RENDERER_H

#include <iostream>
#include <utility> 
#include "../game.h"
#include "../abilityManager.h"

class MessageRender {
public:
    void attack_message(Game &game);

    void apply_ability(Game &game);

    void next_ability(Game &game);

    void get_ability(Game &game);

    void help();
};

#endif