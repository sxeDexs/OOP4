#ifndef GAME_H
#define GAME_H

#include "nlohmann/json.hpp"
#include <iostream>
#include <map>
#include <functional>
#include <utility> 
#include "shipManager.h"
#include "ship.h"
#include "abilityManager.h"
#include "output/drawField.h"
#include "output/outputMessage.h"
#include "input/input.h"
#include "state/gameState.h"
#include "outputMessageEnum.h"
#include "gameField.h"
#include "exception.h"

using json = nlohmann::json;

class Game {
private:
    GameField field_user;
    GameField field_enemy;
    ShipManager ship_manager_enemy;
    AbilityManager ability_manager;
    ShipManager ship_manager_user;
    GameState state;
    OutputMessage game_message;
    Input user_input;

public:
    bool trigger_bot_attack = false;
    std::pair<std::string, bool> abil;

    Game() : field_user(0, 0, false), field_enemy(0, 0, true), ship_manager_enemy(field_enemy.calculation_count_ships()), ship_manager_user(field_user.calculation_count_ships()), state("save.json") {}

    void start_new_game();

    void generate_enemy_ships();

    void computer_turn();

    std::pair<GameField&, ShipManager&> user_object() { return std::make_pair(std::ref(field_user), std::ref(ship_manager_user));  }

    std::pair<GameField&, ShipManager&> enemy_object() { return std::make_pair(std::ref(field_enemy), std::ref(ship_manager_enemy)); }

    AbilityManager& get_ability_manager() { return ability_manager; }

    GameState& get_game_state() { return state; }

    void user_attack();

    void quit() { exit(0); }
    
    void apply_ability();

    void check_game_state();

    void save_game() { state.save(field_user, field_enemy, ship_manager_user, ship_manager_enemy, ability_manager); }

    void load_game() { state.load(field_user, field_enemy, ship_manager_user, ship_manager_enemy, ability_manager); }

    void play();
};



#endif