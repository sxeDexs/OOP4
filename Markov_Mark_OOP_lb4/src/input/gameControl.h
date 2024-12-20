#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#include <iostream>
#include <map>
#include <functional>
#include "../output/drawField.h"
#include "../output/outputMessage.h"
#include "../output/gameRender.h"
#include "../output/stateRender.h"
#include "../state/gameState.h"
#include "../gameField.h"
#include "../game.h"

template<typename InputCommands, typename FieldRender, typename MessageRender>
class GameControl {
private:
    Game &game;
    InputCommands input_commands;
    StateRender<FieldRender, MessageRender> render_state;
    std::map<std::string, std::function<void()>> commands;

public:
    GameControl(Game &g) : game(g), render_state(g) { initialize_commands(); }
    
    void initialize_commands();
    
    void run();
};

template<typename InputCommands, typename FieldRender, typename MessageRender>
void GameControl<InputCommands, FieldRender, MessageRender>::initialize_commands() {
    commands["attack"] = [&]() { 
        game.user_attack();
        render_state.update("get_new_ability_message");
        render_state.update("new_game");
    };
    commands["state_my_ships"] = [&]() { render_state.update("state_my_ships"); };
    commands["state_enemy_ships"] = [&]() { render_state.update("state_enemy_ships"); };
    commands["quit"] = [&]() { game.quit(); };
    commands["fields"] = [&]() { render_state.update("fields"); };
    commands["show_enemy_ships"] = [&]() { render_state.update("show_enemy_ships"); };
    commands["show_my_ships"] = [&]() { render_state.update("show_my_ships"); };
    commands["next_ability"] = [&]() { render_state.update("next_ability"); };
    commands["save_game"] = [&]() { game.save_game(); };
    commands["load_game"] = [&]() { game.load_game(); };
    commands["apply_ability"] = [&]() { 
        game.apply_ability(); 
        render_state.update("apply_ability");
    };
    commands["help"] = [&]() { render_state.update("help"); };
}

template<typename InputCommands, typename FieldRender, typename MessageRender>
void GameControl<InputCommands, FieldRender, MessageRender>::run() {
    game.play();
    while (true) {
        std::string input = input_commands.get_input();
        if (commands.find(input) != commands.quit()) {
            commands[input]();
        } else {
            std::cout << "Unknown command!" << std::endl;
        }
        if (!game.trigger_bot_attack) continue;
        game.computer_turn();
        game.check_game_state();
        render_state.update("attack_message"); 
        render_state.update("fields");
    }   
}

#endif 