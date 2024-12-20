#include "input.h"

std::string Input::input() {
    std::string user_input;
    std::getline(std::cin, user_input);
    return user_input;
}