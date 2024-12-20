#include "messageRender.h"


void MessageRender::attack_message(Game &game) {
    OutputMessage message;
    auto user_data = game.user_object();
    auto enemy_data = game.enemy_object();

    message.user_attack_message(enemy_data.first);
    message.enemy_attack_message(user_data.first);
} 

void MessageRender::apply_ability(Game &game) {
    OutputMessage message;
    message.apply_abiliy_message(game.abil);
}

void MessageRender::next_ability(Game &game) {
    OutputMessage message;
    AbilityManager& ability_manager = game.get_ability_manager();
    std::string name_ability = ability_manager.next_abilities();
    message.next_ability_message(name_ability);
}

void MessageRender::get_ability(Game &game) {
    OutputMessage message;
    AbilityManager& ability_manager = game.get_ability_manager();
    int value = ability_manager.get_is_grand_random_ability();
    message.get_new_ability_message(ability_manager, value);
}

void MessageRender::help() {
    OutputMessage message;
    message.help_message();
}