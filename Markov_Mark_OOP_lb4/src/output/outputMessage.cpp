#include "outputMessage.h"

void OutputMessage::user_attack_message(GameField& field) {
    if(field.get_last_attemp_user() == 0) {
        std::cout << "You miss!" << std::endl;
    } else {
       std::cout << "You hit!" << std::endl;
    }
}

void OutputMessage::enemy_attack_message(GameField& field) {
    if(field.get_last_attemp_enemy() == 0) {
        std::cout << "Bot miss!" << std::endl;
    } else {
        std::cout << "Bot hit!" << std::endl;
    }
}

void OutputMessage::apply_abiliy_message(std::pair<std::string, bool> ability) {
    if(ability.first == "DoubleDamage") {
        std::cout << "DoubleDamage" << std::endl;
        if(ability.second == 1) std::cout << "Next hit deals double damage" << std::endl;
    } else if(ability.first == "Scanner") {
        std::cout << "Scanner" << std::endl;
        if(ability.second == 0) std::cout << "No ships in the area" << std::endl;
        else if (ability.second == 1) std::cout << "Ship detected in the area" << std::endl;
    } else if (ability.first == "Bombard") {
        std::cout << "Bombard" << std::endl;
    } else {
        std::cout << "No abilities available." << std::endl;
    }
}

void OutputMessage::next_ability_message(std::string ability) {
    std::cout << "Next ability: ";
    std::cout << ability << std::endl;
}

void OutputMessage::get_new_ability_message(AbilityManager& ability_manager, int value) {
    if(value == 1) {
        std::cout << "New ability gained." << std::endl;
        ability_manager.set_is_grand_random_ability(0);
    }
}

void OutputMessage::help_message() {
    std::cout << "attack - a" << "\n" 
    << "state_my_ships - ms" << "\n" 
    << "state_enemy_ships - es" << "\n" 
    << "quit - q" << "\n"
    << "show_enemy_ships - hack to view enemy ships" << "\n" 
    << "show_my_ships - view just my ships" << "\n"
    << "fields - view the playing fields" << "\n" 
    << "abilities - look next ability" << "\n" 
    << "stop_game - the command to control serialization" << "\n"
    << "apply_ability - apply ability" << std::endl;
}

void OutputMessage::start_message(OutputMessageVariants command) {
    switch(command) {
        case OutputMessageVariants::INPUT_WIDTH:
            std::cout << "Enter field width: ";
            break;
        case OutputMessageVariants::INPUT_HEIGHT:
            std::cout << "Enter field height: ";
            break;
        case OutputMessageVariants::INVALID_INPUT:
            std::cout << "Invalid input. Please enter a positive integer." << std::endl;
            break;
        case OutputMessageVariants::INPUT_COORDINATE:
            std::cout << "Enter coordinates of the ship and orientation: ";
            break;
        case OutputMessageVariants::INVALID_COORDINATE:
            std::cout << "Invalid input for coordinates. Please enter valid integers." << std::endl;
            break;
        case OutputMessageVariants::RE_ENTER_COORDINATE:
            std::cout << "Please re-enter coordinates of the ship and orientation." << std::endl;
            break;
    }
}

void OutputMessage::game_message(OutputMessageVariants command) {
     switch(command) {
        case OutputMessageVariants::ATTACK_COORDINATE:
            std::cout << "Coordinate for attack: ";
            break;
        case OutputMessageVariants::SCANNER_COORDINATE:
            std::cout << "Coordinate for ability: ";
            break;
        case OutputMessageVariants::OPTION_LOAD_GAME:
            std::cout << "Do you want load game?" << std::endl;
            break;
        case OutputMessageVariants::COORDINATE_OUT_OF_RANGE:
            std::cout << "Attack coordinates are out of range. Please enter valid coordinates." << std::endl;
            break;
        case OutputMessageVariants::INVALID_COORDINATE_FOR_ATTACK:
            std::cout << "Invalid input. Please enter valid integers for coordinates." << std::endl;
            break;
    }
}

void OutputMessage::game_state_message(OutputMessageVariants command) {
    switch(command) {
        case OutputMessageVariants::LOST:
            std::cout << "You lost!" << std::endl;
            break;
        case OutputMessageVariants::QUES_START_NEW_GAME:
            std::cout << "Do you want to start a new game: " << std::endl;
            break;
        case OutputMessageVariants::START_NEW_GAME:
            std::cout << "Starting a new game." << std::endl;
            break;
        case OutputMessageVariants::WIN:
            std::cout << "You won this round!" << std::endl;
            break;
        case OutputMessageVariants::QUES_START_NEW_ROUND:
            std::cout << "Do you want to start a new round: ";
            break;
        case OutputMessageVariants::START_NEW_ROUND:
            std::cout << "Starting the next round." << std::endl;
            break;
    }
}