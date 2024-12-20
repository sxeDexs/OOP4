#include "gameField.h"
#include "abilities/ability.h"
#include "abilityManager.h"
#include "ship.h"
#include "shipManager.h"
#include "exception.h"


bool GameField::attack_cell(int x, int y, ShipManager& manager, AbilityManager& manager_ability) { 
    try{
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw OutOfBoundsException("Attack coordinates are out of range.", width, height);
        }
        for (int i = 0; i < count_ships; ++i) {

            Ship& ship = manager.get_ship(i);
            int ship_length = ship.get_length();
            bool is_vertical = ship.is_vertical_orientation();

            if (is_vertical) {
                if (x == ship.get_x()) {
                    for (int j = 0; j < ship_length; ++j) {
                        if (y == ship.get_y() + j) {
                            if(ship.get_segment_state(j) == 2) {
                                std::cerr << "This segment has already been destroyed." << std::endl;
                                return 0;
                            }
                            ship.damage_segment(j);
                            if(double_damage) ship.damage_segment(j);
                            if (get_double_damage()) set_double_damage(false);
                            if(ship.is_destroy() && bot_attacked == true) manager_ability.grand_random_ability();
                             if(bot_attacked) {
                                last_attemp_user = 1;
                            } else {
                                last_attemp_enemy = 1;
                            }
                            return 1;
                        }
                    }
                }
            } else {
                if (y == ship.get_y()) {
                    for (int j = 0; j < ship_length; ++j) {
                        if (x == ship.get_x() + j) {
                            if(ship.get_segment_state(j) == 2) {
                                std::cerr << "This segment has already been destroyed." << std::endl; 
                                return 0;
                            }
                            ship.damage_segment(j);
                            if(double_damage) ship.damage_segment(j);
                            if (get_double_damage()) set_double_damage(false);
                            if(ship.is_destroy() && bot_attacked == true) manager_ability.grand_random_ability();
                            if(bot_attacked) {
                                last_attemp_user = 1;
                            } else {
                                last_attemp_enemy = 1;
                            }
                            return 1;
                        }
                    }
                }
            }
        }
        field[y][x] = empty_state;
        if(get_bot_attacked()) {
            last_attemp_user = 0;
        } else {
            last_attemp_enemy = 0;
        }
        if (get_double_damage()) {set_double_damage(false);}
        return 0;
    } catch (OutOfBoundsException& e) {
        std::cerr << "The field has a width of " << e.get_width_state() << " and a height of " << e.get_height_state() << std::endl; 
        throw;
    } 
    return 0;
}
 
ShipManager GameField::calculation_count_ships() {
    int count_cell = width * height;
    if(count_cell == 0) return ShipManager(1, {3});
    int count_ships_cell = count_cell / 5;
    std::vector<int> ship_sizes;

    if (count_ships_cell >= 20) { 
        ship_sizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; 
        count_ships = 10;
    } else if (count_ships_cell >= 15) {
        ship_sizes = {3, 3, 2, 2, 1, 1, 1};
        count_ships = 7;
    } else {
        ship_sizes = {2, 2, 1, 1}; 
        count_ships = 4;
    }
    return ShipManager(ship_sizes.size(), ship_sizes);
}

void GameField::place_ship(Ship& ship, int x, int y, std::string orientation) {
    while (true) {
        try {
            if(orientation == "h") {
                ship.set_orientation(0);
            } else if (orientation == "v") {
                ship.set_orientation(1);
            } else if (orientation == "dont have") {

            } else {
                throw OrientationShipException("The ship must have horizontal(h) or vertical(v).");
            }

            int length = ship.get_length();

            if(x > width || y > height || x < 0 || y < 0 || x+length > width || y+length > height) {
                throw OutOfBoundsException("The coordinates are out of the field.", width, height);
            }
            
            for (int i = -1; i <= length; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int check_x = ship.is_vertical_orientation() ? x + j : x + i;
                    int check_y = ship.is_vertical_orientation() ? y + i : y + j;
                    
                    if (check_y >= 0 && check_y < height && check_x >= 0 && check_x < width) {
                        if (field[check_y][check_x] != unknown_state) {
                            std::cout << check_y << " " << check_x << std::endl;
                            throw InvalidShipPlacementException("The place is occupied or too close to another ship.", check_x, check_y);
                        }
                    }
                }
            }

            if (ship.is_vertical_orientation()) {
                for (int i = 0; i < length; ++i) {
                    field[y + i][x] = ship_state;
                }
            } else {
                for (int i = 0; i < length; ++i) {
                    field[y][x + i] = ship_state;
                }
            }
            ship.set_x(x);
            ship.set_y(y);
            break;
        } catch (OutOfBoundsException& e) {
            std::cerr << "The field has a width of " << e.get_width_state() << " and a height of " << e.get_height_state() << std::endl; 
            throw; 
        } catch (InvalidShipPlacementException& e) {
            std::cerr << "The ship is already located at coordinates x - " << e.get_x_state() << " y - " << e.get_y_state() << std::endl;
            throw;
        } catch (OrientationShipException& e) {
            throw; 
        }
    }
}

int GameField::get_cell_status(int x, int y) {
    return field[x][y];
}


GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) {

        for (int i = 0; i < height; ++i) {
            delete[] field[i];
        }
        delete[] field;

        width = other.width;
        height = other.height;
        field = other.field;
        count_ships = other.count_ships;

        other.field = nullptr;
        other.width = 0;
        other.height = 0;
        other.count_ships = 0;
    }
    return *this;
}

GameField& GameField::operator=(const GameField& other) {
    if (this == &other) return *this;

    for (int i = 0; i < height; ++i) {
        delete[] field[i];
    }
    delete[] field;

    width = other.width;
    height = other.height;
    count_ships = other.count_ships;

    field = new cell_status*[height];
    for (int i = 0; i < height; ++i) {
        field[i] = new cell_status[width];
        std::copy(other.field[i], other.field[i] + width, field[i]);
    }
    
    return *this;
}

void GameField::clean() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) { 
            field[y][x] = unknown_state;
        }
    }
}

json GameField::to_json() const {
    json j;
    j["width"] = width;
    j["height"] = height;
    j["bot_attacked"] = bot_attacked;

    for (int i = 0; i < height; ++i) {
        std::vector<int> row;
        for (int j = 0; j < width; ++j) {
            row.push_back(static_cast<int>(field[i][j]));
        }
        j["field"].push_back(row);
    }

    return j;
}

GameField GameField::from_json_size(const json& j) {
    GameField field(j["width"], j["height"]);
    field.set_bot_attacked(j["bot_attacked"]);
    return field;
}

void GameField::from_json_coord(const json& j) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) { 
            field[y][x] = j["field"][y][x];
        }
    }
}