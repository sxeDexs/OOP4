#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <set>
#include <utility> 
#include <algorithm>
#include <sstream>
#include <random> 
#include <string>
#include <fstream>
#include "state/gameState.h"
#include "game.h"

void Game::start_new_game() {
    int width_field;
    int height_field;

    while (true) {
        game_message.start_message(OutputMessageVariants::INPUT_WIDTH);
        std::string input = user_input.input();
        std::stringstream ss(input);
        if (ss >> width_field) {
            break; 
        } else {
            game_message.start_message(OutputMessageVariants::INVALID_INPUT);
        }
    }

    while (true) {
        game_message.start_message(OutputMessageVariants::INPUT_HEIGHT);
        std::string input = user_input.input();
        std::stringstream ss(input);
        if (ss >> height_field) {
            break; 
        } else {
            game_message.start_message(OutputMessageVariants::INVALID_INPUT);
        }
    }
    
    field_user = GameField(width_field, height_field, false);
    field_enemy = GameField(width_field, height_field, true);
    ship_manager_enemy = field_enemy.calculation_count_ships();
    ship_manager_user = field_user.calculation_count_ships();
    int count_ships = field_user.count_ships;

    for (int i = 0; i < count_ships; i++) {
        Ship& ship = ship_manager_user.get_ship(i);
        int x, y;
        std::string orientation = "dont have";

        while (true) {
            game_message.start_message(OutputMessageVariants::INPUT_COORDINATE);
            std::string input_line = user_input.input();

            std::stringstream ss(input_line);
            ss >> x >> y;

            if (ss.fail() || ss.bad() || x < 0 || y < 0) {
                game_message.start_message(OutputMessageVariants::INVALID_COORDINATE);
                continue;
            }

            if (ss.peek() != EOF) { 
                ss >> orientation; 
            }

            try {
                field_user.place_ship(ship, x, y, orientation);
                break;
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
                game_message.start_message(OutputMessageVariants::RE_ENTER_COORDINATE);
            }
        }
    }

    generate_enemy_ships();
}

void Game::generate_enemy_ships() {
    srand(static_cast<unsigned int>(time(NULL)));

    int width = field_enemy.get_width();
    int height = field_enemy.get_height();
    std::vector<std::vector<int>> field_mark(height, std::vector<int>(width, 0)); 
    
    for (int i = 0; i < ship_manager_enemy.get_ships_count(); i++) {
        Ship& ship = ship_manager_enemy.get_ship(i);
        int length = ship.get_length();
        bool placed = false;
        
        while (!placed) {
            int x = rand() % width;
            int y = rand() % height;
            std::string orientation = (rand() % 2 == 0) ? "h" : "v"; 
            bool canPlace = true;

            if (x > width || y > height || x < 0 || y < 0 || x+length > width || y+length > height) {
                continue; 
            }

            for (int j = 0; j < length; j++) {
                int check_x = (orientation == "h") ? x + j : x;
                int check_y = (orientation == "h") ? y : y + j;

                if (check_x >= 0 && check_x < width && check_y >= 0 && check_y < height) {
                    if (field_mark[check_y][check_x] != 0) {
                        canPlace = false;
                        break; 
                    }
                } else {
                    canPlace = false;
                    break;
                }
            }

            if (canPlace) {
                for (int j = 0; j < length; j++) {
                    int place_x = (orientation == "h") ? x + j : x;
                    int place_y = (orientation == "h") ? y : y + j;
                    field_mark[place_y][place_x] = 1;
                }

                for (int j = -1; j <= length; j++) {
                    for (int k = -1; k <= 1; k++) {
                        int startX = (orientation == "v") ? x + k : x + j;
                        int startY = (orientation == "v") ? y + j : y + k;

                        if (startX >= 0 && startX < width && startY >= 0 && startY < height) {
                            field_mark[startY][startX] = 1;
                        }
                    }
                }  

                field_enemy.place_ship(ship, x, y, orientation); 
                placed = true; 
            }
        }
    }
}

void Game::apply_ability() {
    std::string message = ability_manager.next_abilities();
    bool trigger = 0;
    if(message == "DoubleDamage") {
        trigger = ability_manager.apply_ability(field_enemy, 0, 0, ship_manager_enemy);
    } else if (message == "Scanner") {
        int x, y;
        game_message.game_message(OutputMessageVariants::SCANNER_COORDINATE);
        std::string input = user_input.input();
        std::stringstream ss(input);
        ss >> x >> y;
        trigger = ability_manager.apply_ability(field_enemy, x, y, ship_manager_enemy);
    } else if (message == "Bombard") {
        trigger = ability_manager.apply_ability(field_enemy, 0, 0, ship_manager_enemy);
    }
    abil = make_pair(message, trigger);
}

void Game::user_attack() {
    trigger_bot_attack = true;
    int x = -1, y = -1;

    while (true) {
        game_message.game_message(OutputMessageVariants::ATTACK_COORDINATE);
        std::string input = user_input.input();

        std::stringstream ss(input);
        ss >> x >> y;
        
        if (ss.fail() || ss.bad() || ss.peek() != EOF) {
            game_message.game_message(OutputMessageVariants::INVALID_COORDINATE_FOR_ATTACK);
            continue;
        }

        try {
            field_enemy.attack_cell(x, y, ship_manager_enemy, ability_manager);
            break;
        } catch (const OutOfBoundsException&) {
            game_message.game_message(OutputMessageVariants::COORDINATE_OUT_OF_RANGE);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void Game::computer_turn() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist_x(0, field_user.get_width() - 1);
    std::uniform_int_distribution<int> dist_y(0, field_user.get_height() - 1);

    int x, y;

    do {
        x = dist_x(gen);
        y = dist_y(gen);
    } while (field_user.get_cell_status(x, y) == 1);

    field_user.attack_cell(x, y, ship_manager_user, ability_manager);
}

void Game::check_game_state() {
    if (ship_manager_user.all_ships_destroy()) {
        game_message.game_state_message(OutputMessageVariants::LOST);
        game_message.game_state_message(OutputMessageVariants::QUES_START_NEW_GAME);
        std::string answer = user_input.input();
        if(answer == "yes") {
            game_message.game_state_message(OutputMessageVariants::START_NEW_GAME);
            ability_manager.new_ability();
            start_new_game();
        } else {
            exit(0);
        }
    }  else if (ship_manager_enemy.all_ships_destroy()) {
        game_message.game_state_message(OutputMessageVariants::WIN);
        game_message.game_state_message(OutputMessageVariants::QUES_START_NEW_ROUND);
        std::string answer = user_input.input();
        if(answer == "yes") {
            game_message.game_state_message(OutputMessageVariants::START_NEW_ROUND);
            ship_manager_enemy.new_ships();
            field_enemy.clean(); 
            generate_enemy_ships();
        } else {
            exit(0);
        }
    }
}

void Game::play() {
    if(state.is_file_written()) {
        game_message.game_message(OutputMessageVariants::OPTION_LOAD_GAME);
        std::string answer = user_input.input();
        if(answer == "yes") {
            load_game();
        } else {
            start_new_game();
        }
    } else {
        start_new_game();
    }
}