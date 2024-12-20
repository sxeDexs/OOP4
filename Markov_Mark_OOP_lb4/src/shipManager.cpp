#include "shipManager.h"

bool ShipManager::all_ships_destroy() {
    int count_destroy_ships = 0;
    for(int i = 0; i < ships.size(); i++) {
        Ship& ship = *ships[i];
        int len_ship = ship.get_length();
        int count_destroy = 0;
        for(int i = 0; i < len_ship; i++) {
            int state = ship.get_segment_state(i);
            if (state == 2) {
                count_destroy++;
            }
        }
        if(count_destroy == len_ship) {
            count_destroy_ships++;
        }
    }
    if(count == count_destroy_ships) return true;
    return false;
}

json ShipManager::to_json() const {
    json j;
    j["count"] = count;

    std::vector<json> coord_ships;
    
    for(int i = 0; i < ships.size(); i++) {
        Ship& ship = *ships[i];
        int x = ship.get_x();
        int y = ship.get_y();
        bool orint = ship.is_vertical_orientation();
        coord_ships.push_back({x, y, orint});
    }

    j["coordinate_ships"] = coord_ships;

    json ships_array = json::array();
    for(int i = 0; i < ships.size(); i++) {
        Ship& ship = *ships[i];
        int len_ship = ship.get_length();
        std::vector<int> segment_array;
        for(int i = 0; i < len_ship; i++) {
            segment_array.push_back(ship.get_segment_state(i));
        }
        ships_array.push_back(segment_array);
    }
    j["ships"] = ships_array;
    return j;
}

void ShipManager::from_json(const json& j, GameField& field) {
    count = j["count"];
    const auto& ships_array = j["ships"];
    const auto& coord_ships = j["coordinate_ships"];

    for(int i = 0; i < count; i++) {
        Ship& ship = *ships[i];
        std::string orint;
        if(coord_ships[i][2] == true) {
            orint = "v";
        } else {
            orint = "h";
        }
        field.place_ship(ship, coord_ships[i][0], coord_ships[i][1], orint);
    }

    for(int i = 0; i < count; i++) {
        Ship& ship = *ships[i];
        int len_ship = ship.get_length();
        for(int l = 0; l < len_ship; l++) {
            ship.set_segment_state(l, ships_array[i][l]);
        }
    }
}

void ShipManager::new_ships() {
    for(int i = 0; i < ships.size(); i++) {
        Ship& ship = *ships[i];
        int len_ship = ship.get_length();
        for(int j = 0; j < len_ship; j++) {
            ship.set_segment_state(j, 0);
        }
    }
}