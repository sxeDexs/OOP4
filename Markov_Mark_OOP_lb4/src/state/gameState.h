#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include "../shipManager.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include "../nlohmann/json.hpp"
#include "../ship.h"
#include "../abilityManager.h"
#include "fileHandler.h"
#include "../gameField.h"

using json = nlohmann::json;

class GameState {
private:
    std::string filename;
    json saved_data;

public:
    GameState(const std::string& fname) : filename(fname) { }

    void save( GameField& field_user, GameField& field_enemy, 
    ShipManager& ship_manager_user, ShipManager& ship_manager_enemy,
    AbilityManager& ability_manager);

    void load(GameField& field_user, GameField& field_enemy, 
    ShipManager& ship_manager_user, ShipManager& ship_manager_enemy,
    AbilityManager& ability_manager);

    void write_state();

    bool is_file_written() const {
        std::ifstream file(filename);
        return file.peek() != std::ifstream::traits_type::eof();
    }

    friend std::ostream& operator<<(std::ostream& os, const GameState& game_state) {
        FileHandler file_handler(game_state.filename);
        file_handler.openForRead();

        json j;
        file_handler.read(j);
        
        os << j.dump(4) << std::endl;
        
        return os;
    }

    friend std::istream& operator>>(std::istream& is, GameState& game_state) {
        json j;
        
        is >> j; 
        game_state.saved_data = j;
        if (j.is_null()) {
            throw std::runtime_error("Failed to read valid JSON data.");
        }
        
        game_state.write_state();

        return is;
    }

};

#endif