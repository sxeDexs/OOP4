#include "drawField.h"

void DrawField::draw_with_fog_war(GameField& field, ShipManager& manager, bool trigger) {
    std::cout << std::endl;
    if(trigger == 0) 
        std::cout << "User field: " << std::endl;
    else 
        std::cout << "Enemy field: " << std::endl;

    std::cout << "   ";
    for (int x = 0; x < field.get_width(); ++x) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (int y = 0; y < field.get_height(); ++y) {
        std::cout << y << "  ";

        for (int x = 0; x < field.get_width(); ++x) {
            bool is_damaged = false;
            bool is_hit = false;

            for (int i = 0; i < field.count_ships; ++i) {
                Ship& ship = manager.get_ship(i);
                int ship_length = ship.get_length();
                bool is_vertical = ship.is_vertical_orientation();

                if (is_vertical) {
                    if (x == ship.get_x()) {
                        for (int j = 0; j < ship_length; ++j) {
                            if (y == ship.get_y() + j) {
                                if (ship.get_segment_state(j) == 2) {
                                    is_damaged = true;
                                } else if (ship.get_segment_state(j) == 1) {
                                    is_hit = true;
                                }
                                break;
                            }
                        }
                    }
                } else {
                    if (y == ship.get_y()) {
                        for (int j = 0; j < ship_length; ++j) {
                            if (x == ship.get_x() + j) {
                                if (ship.get_segment_state(j) == 2) {
                                    is_damaged = true;
                                } else if (ship.get_segment_state(j) == 1) {
                                    is_hit = true;
                                }
                                break;
                            }
                        }
                    }
                }
                if (is_damaged || is_hit) break;
            }

            if (field.get_cell_status(y, x) == 0) {
                std::cout << ". ";
            } else if (field.get_cell_status(y, x) == 1) {
                std::cout << "~ ";
            } else if (is_damaged) {
                std::cout << "D ";
            } else if (is_hit) {
                std::cout << "H ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}


void DrawField::draw_all_ship(GameField& field) {
    std::cout << std::endl;
    std::cout << "Ships on the field: " << std::endl;

    std::cout << "   ";
    
    for (int x = 0; x < field.get_width(); ++x) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    for (int y = 0; y < field.get_height(); ++y) {
        std::cout << y << "  ";

        for (int x = 0; x < field.get_width(); ++x) {
            if (field.get_cell_status(y, x) == 2) {
                std::cout << "S ";
            } else if (field.get_cell_status(y, x) == 0 || field.get_cell_status(y, x) == 1) {
                std::cout << "~ ";
            }
        }
        std::cout << std::endl;
    }
}


void DrawField::draw_state(ShipManager& manager) {
    std::vector<std::unique_ptr<Ship>>& ships = manager.get_ships();
    for(int i = 0; i < ships.size(); i++) {
        Ship& ship = *ships[i];
        int len_ship = ship.get_length();
        int count_destroy = 0;
        std::cout << "Ship " << i+1 <<": ";
        for(int i = 0; i < len_ship; i++) {
            int state = ship.get_segment_state(i);
            if(state == 0) {
                std::cout << "i"; // intact
            } else if (state == 1) {
                std::cout << "h"; // hit
            } else if (state == 2) {
                std::cout << "d"; // destroyed
                count_destroy++;
            }
            std::cout << " ";
        }
        if(count_destroy == len_ship) {
            std::cout << " " << "Ship destroy";
        }
        std::cout << std::endl;
    }
}