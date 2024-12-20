#ifndef INPUT_COMMANDS_H
#define INPUT_COMMANDS_H

#include <iostream>
#include <map>
#include <functional>
#include <utility> 
#include "../shipManager.h"
#include "../ship.h"
#include "../state/gameState.h"
#include "../gameField.h"
#include "input.h"
#include "../exception.h"
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

class InputCommands {
private:
    Input user_input;
    std::map<std::string, std::string> command_map; 
    std::map<std::string, std::string> key_map;     

public:
    InputCommands();

    std::string get_input();

    std::string get_command(const std::string& input);
};

#endif