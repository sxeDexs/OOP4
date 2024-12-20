#ifndef SHIP_MANAGER_H
#define SHIP_MANAGER_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include "ship.h"
#include "gameField.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Ship;
class ShipManager {

private:
    std::vector<std::unique_ptr<Ship>> ships;
    int count;
public:
    ShipManager(int count, const std::vector<int>& sizes) : count(count) {
        if (count != sizes.size()) {
            throw std::invalid_argument("Count of ships must match sizes vector.");
        }
        for (int size : sizes) {
            ships.emplace_back(std::make_unique<Ship>(size, size % 2 == 0));
        }
    }

    int get_ships_count() {return count;}

    Ship& get_ship(int index) const { return *ships[index]; }

    bool all_ships_destroy();

    json to_json() const;

    std::vector<std::unique_ptr<Ship>> & get_ships(){
        return ships;
    }

    void from_json(const json& j, GameField& field);

    void new_ships();
};

#endif