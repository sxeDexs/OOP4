#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include <iostream>
#include "../game.h"

class Game;

template<typename FieldRender, typename MessageRender>
class GameRender {
private:
    FieldRender render_field;
    MessageRender render_message;
    Game &game;

public:
    GameRender(Game &g) : game(g) {}

    void render(const std::string &command);

    void update(const std::string &command);
};

template<typename FieldRender, typename MessageRender>
void GameRender<FieldRender, MessageRender>::render(const std::string &command) {
    if (command == "fields") {
        render_field.draw_field(game);

    } else if (command == "attack_message") {
        render_message.attack_message(game);

    } else if (command == "state_my_ships") {
        render_field.state_ship(game, 1);

    } else if (command == "state_enemy_ships") {
        render_field.state_ship(game, 0);

    } else if (command == "show_enemy_ships") {
        render_field.show_all_ship(game, 0);

    } else if (command == "show_my_ships") {
        render_field.show_all_ship(game, 1);

    } else if (command == "apply_ability") {
        render_message.apply_ability(game);

    } else if (command == "next_ability") {
        render_message.next_ability(game);

    } else if (command == "get_new_ability_message") {
        render_message.get_ability(game);
        
    } else if (command == "help") {
        render_message.help();
    } 
}

template<typename FieldRender, typename MessageRender>
void GameRender<FieldRender, MessageRender>::update(const std::string &command) {
    render(command);
}

#endif 