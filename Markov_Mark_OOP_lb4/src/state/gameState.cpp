#include "gameState.h"


void GameState::save(GameField& field_user, GameField& field_enemy, 
            ShipManager& ship_manager_user, ShipManager& ship_manager_enemy,
            AbilityManager& ability_manager) {
    json j;

    j["field_user"] = field_user.to_json();
    j["field_enemy"] = field_enemy.to_json();
    j["ship_manager_user"] = ship_manager_user.to_json();
    j["ship_manager_enemy"] = ship_manager_enemy.to_json();
    j["ability_manager"] = ability_manager.to_json();

    FileHandler file_handler(filename);
    file_handler.openForWrite();
    file_handler.write(j);
}

void GameState::load(GameField& field_user, GameField& field_enemy, 
            ShipManager& ship_manager_user, ShipManager& ship_manager_enemy,
            AbilityManager& ability_manager) {
    FileHandler file_handler(filename);
    file_handler.openForRead();

    json j;
    file_handler.read(j);

    field_user = field_user.from_json_size(j["field_user"]);
    field_enemy = field_enemy.from_json_size(j["field_enemy"]);
    ship_manager_enemy = field_enemy.calculation_count_ships();
    ship_manager_user = field_user.calculation_count_ships();
    ship_manager_user.from_json(j["ship_manager_user"], field_user);
    ship_manager_enemy.from_json(j["ship_manager_enemy"], field_enemy);
    field_user.from_json_coord(j["field_user"]); 
    field_enemy.from_json_coord(j["field_enemy"]);
    ability_manager.from_json(j["ability_manager"]);
}

void GameState::write_state() {
    FileHandler file_handler(filename);
    file_handler.openForWrite();
    file_handler.write(saved_data);
}