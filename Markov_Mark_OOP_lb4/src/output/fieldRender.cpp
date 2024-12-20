#include "fieldRender.h"

void FieldRender::draw_field(Game &game) {
    DrawField field;
    auto user_data = game.user_object();
    auto enemy_data = game.enemy_object();

    field.draw_with_fog_war(user_data.first, user_data.second, 0);
    field.draw_with_fog_war(enemy_data.first, enemy_data.second, 1);
}

void FieldRender::state_ship(Game &game, bool trigger) {
    DrawField field;
    auto user_data = game.user_object();
    auto enemy_data = game.enemy_object();

    if(trigger == 0) {
        field.draw_state(enemy_data.second);
    } else {
        field.draw_state(user_data.second);
    }
}

void FieldRender::show_all_ship(Game &game, bool trigger) {
    DrawField field;
    auto user_data = game.user_object();
    auto enemy_data = game.enemy_object();

    if(trigger == 0) {
        field.draw_all_ship(enemy_data.first);
    } else {
        field.draw_all_ship(user_data.first);
    }
}