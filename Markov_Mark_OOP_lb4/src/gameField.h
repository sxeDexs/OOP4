#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Ship;
class ShipManager;
class AbilityManager;

class GameField {
enum cell_status {
    unknown_state,
    empty_state,
    ship_state
};
private:
    int width, height;
    cell_status** field;
    bool double_damage = false;
    bool bot_attacked = false;
    int last_attemp_user = 0;
    int last_attemp_enemy = 0;
public:
    int count_ships;

    GameField(int width_f, int height_f, int bot_attacked = false) : width(width_f), height(height_f), bot_attacked(bot_attacked) {
        if(width_f == 0 && height_f ==  0) {
            
        } else {
            if(width_f > 20 || height_f > 20) {
                throw std::invalid_argument("Too big field.");
            }
            if(width_f < 5 || height_f < 5) {
                throw std::invalid_argument("Too small field.");
            }
        }

        field = new cell_status*[height_f];
        for (int i = 0; i < height_f; ++i) {
            field[i] = new cell_status[width_f];
            std::fill(field[i], field[i] + width_f, unknown_state);
        }
    }

    GameField(const GameField& other) : width(other.width), height(other.height), count_ships(other.count_ships) {
        field = new cell_status*[height];
        for (int i = 0; i < height; ++i) {
            field[i] = new cell_status[width];
            std::copy(other.field[i], other.field[i] + width, field[i]);
        }
    }
    GameField(GameField&& other) noexcept : width(other.width), height(other.height), field(other.field), count_ships(other.count_ships) {
        other.field = nullptr;
    }

    GameField& operator=(const GameField& other);

 
    GameField& operator=(GameField&& other) noexcept;
    void place_ship(Ship& ship, int x, int y, std::string orientation);

    ShipManager calculation_count_ships();

    int get_cell_status(int x, int y);

    bool attack_cell(int x, int y, ShipManager& manager, AbilityManager& manager_ability);

    int get_height() const {return height;}
    int get_width() const {return width;}

    bool get_double_damage() {return double_damage;}
    void set_double_damage(bool value) {double_damage = value;}

    bool get_last_attemp_user() { return last_attemp_user; }
    void set_last_attemp_user(bool value) { last_attemp_user = value; }

    bool get_last_attemp_enemy() { return last_attemp_enemy; }
    void set_last_attemp_enemy(bool value) { last_attemp_enemy = value; }

    void clean();

    json to_json() const;

    GameField from_json_size(const json& j);

    void from_json_coord(const json& j);

    bool get_bot_attacked() { return bot_attacked; }
    void set_bot_attacked(bool value) { bot_attacked = value; }

    ~GameField() {
        for (int i = 0; i < height; ++i) {
            delete[] field[i];
        }
        delete[] field;
    }

};

#endif