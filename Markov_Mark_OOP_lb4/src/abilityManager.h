#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H

#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random> 
#include <string> 
#include "abilities/doubleDamage.h"
#include "abilities/bombard.h"
#include "abilities/scanner.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class GameField; 
class ShipManager;
 
class AbilityManager {
private:
    std::queue<std::unique_ptr<Ability>> abilities;
    int len_queue = 3;
    bool is_grand_random_ability;
 
public:
    AbilityManager() {
        std::vector<std::unique_ptr<Ability>> available_abilities;
        available_abilities.emplace_back(std::make_unique<DoubleDamage>());
        available_abilities.emplace_back(std::make_unique<Scanner>());
        available_abilities.emplace_back(std::make_unique<Bombard>());

        std::random_device rd;
        std::mt19937 g(rd());

        shuffle(available_abilities.begin(), available_abilities.end(), g);

        for(auto &ability : available_abilities) {
            abilities.push(move(ability));
        }
    }

    bool apply_ability(GameField& field, int x, int y, ShipManager& manager);

    std::string next_abilities();

    void grand_random_ability();

    void new_ability();

    void from_json(const json& j);

    int get_len_queue() { return len_queue; }
    void set_len_queue(int value) {len_queue = value; }

    int get_is_grand_random_ability() { return is_grand_random_ability; }
    void set_is_grand_random_ability(int value) {is_grand_random_ability = value; }

    json to_json();

};

#endif