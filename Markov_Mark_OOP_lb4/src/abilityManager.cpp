#include "abilityManager.h"
#include "ship.h"
#include "shipManager.h"
#include "abilities/ability.h"
#include "exception.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

bool AbilityManager::apply_ability(GameField& field, int x, int y, ShipManager& manager) {
    try {
        if(!abilities.empty()) {
            int trig = abilities.front()->apply(field, x, y, manager);
            abilities.pop();
            len_queue -= 1;
            return trig;
        } else {
            throw NoAbilitiesException("No abilities available.");
        }
    } catch (NoAbilitiesException& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
} 

std::string AbilityManager::next_abilities() {
    std::string message;
    if(!abilities.empty()) {
        if (dynamic_cast<DoubleDamage*>(abilities.front().get())) {
            message = "DoubleDamage";
        } else if (dynamic_cast<Scanner*>(abilities.front().get())) {
            message = "Scanner";
        } else if (dynamic_cast<Bombard*>(abilities.front().get())) {
            message = "Bombard";
        }
    } else {
        message = "No abilities available.";
    }

    return message;
}
 
void AbilityManager::grand_random_ability() {
    is_grand_random_ability = 1;
    srand(time(NULL));
    std::vector<std::unique_ptr<Ability>> new_ability;
    int random = rand(); 
    len_queue += 1;

    if(random % 3 == 0) {
        new_ability.emplace_back(std::make_unique<DoubleDamage>());
    } else if (random % 3 == 1) {
        new_ability.emplace_back(std::make_unique<Scanner>());
    } else if (random % 3 == 2) {
        new_ability.emplace_back(std::make_unique<Bombard>());
    }
    abilities.push(move(new_ability[0]));
} 

json AbilityManager::to_json() {
    json j;
    std::vector<json> ability_list;
    std::vector<std::string> temp_ability;
    
    for(int i = 0; i < len_queue; i++) {
        if (dynamic_cast<DoubleDamage*>(abilities.front().get())) {
            ability_list.push_back({"type", "DoubleDamage"});
            temp_ability.push_back("DoubleDamage");
        } else if (dynamic_cast<Scanner*>(abilities.front().get())) {
            ability_list.push_back({"type", "Scanner"});
            temp_ability.push_back("Scanner");
        } else if (dynamic_cast<Bombard*>(abilities.front().get())) {
            ability_list.push_back({"type", "Bombard"});
            temp_ability.push_back("Bombard");
        }
        abilities.pop();
    }

    j["abilities"] = ability_list;

    for(int i = 0; i < temp_ability.size(); i++) {
        if(temp_ability[i] == "Bombard") {
            abilities.push(std::move(std::make_unique<Bombard>()));
        } else if (temp_ability[i] == "DoubleDamage") {
            abilities.push(std::move(std::make_unique<DoubleDamage>()));
        } else if (temp_ability[i] == "Scanner") {
            abilities.push(std::move(std::make_unique<Scanner>()));
        }
    }

    j["len_queue"] = len_queue;

    return j;
}

void AbilityManager::new_ability() {
    std::queue<std::unique_ptr<Ability>> empty;
    std::swap(abilities, empty);
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

void AbilityManager::from_json(const json& j) {
    std::queue<std::unique_ptr<Ability>> empty;
    std::swap(abilities, empty);

    const auto& abilities_array = j["abilities"];
    for (const auto& ability_data : abilities_array) {
        std::string type = ability_data[1];

        if (type == "Bombard") {
            abilities.push(std::make_unique<Bombard>());
        } else if (type == "Scanner") {
            abilities.push(std::make_unique<Scanner>());
        } else if (type == "DoubleDamage") {
            abilities.push(std::make_unique<DoubleDamage>());
        } else {
            throw std::invalid_argument("Unknown ability type.");
        }
    }

    len_queue = j["len_queue"];
}