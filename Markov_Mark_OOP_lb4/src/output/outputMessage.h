#ifndef OUTPUT_MESSAGE_H
#define OUTPUT_MESSAGE_H

#include <iostream>
#include <map>
#include <functional>
#include <utility> 
#include "../shipManager.h"
#include "../ship.h"
#include "../abilityManager.h"
#include "../state/gameState.h"
#include "../gameField.h"
#include "../outputMessageEnum.h"

class OutputMessage {
public:
    void user_attack_message(GameField& field);

    void enemy_attack_message(GameField& field);

    void apply_abiliy_message(std::pair<std::string, bool> abil);

    void next_ability_message(std::string ability);

    void get_new_ability_message(AbilityManager& ability_manager, int value);

    void help_message();

    void start_message(OutputMessageVariants command);

    void game_message(OutputMessageVariants command);

    void game_state_message(OutputMessageVariants command);
};

#endif