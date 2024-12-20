#include "inputCommands.h"

InputCommands::InputCommands() { 
    const std::string& filename = "commands.json";

    if (std::ifstream file{filename}) {
        json j;
        file >> j;

        for (auto& element : j.items()) {
            const std::string command = element.key();
            const std::string key = element.value();

            if (key_map.find(key) != key_map.end()) {
                throw std::invalid_argument("Duplicate key assignment: " + key);
            }

            if (command_map.find(command) != command_map.end()) {
                throw std::invalid_argument("Duplicate command assignment: " + command);
            }

            command_map[command] = key;
            key_map[key] = command;
        }
    } else {
        std::cerr << "Error opening " << filename << ", loading default commands." << std::endl;
        if (std::ifstream default_file{"default.json"}) {
            json j;
            default_file >> j;

            for (auto& element : j.items()) {
                const std::string command = element.key();
                const std::string key = element.value();

                if (key_map.find(key) != key_map.end()) {
                    throw std::invalid_argument("Duplicate key assignment in default commands: " + key);
                }

                if (command_map.find(command) != command_map.end()) {
                    throw std::invalid_argument("Duplicate command assignment in default commands: " + command);
                }

                command_map[command] = key;
                key_map[key] = command; 
            }
        } else {
            throw std::runtime_error("Error opening default command file");
        }
    }
}

std::string InputCommands::get_input() {
    while (true) {
        std::cout << "Enter command: ";
        std::string input = user_input.input();

        try {
            return get_command(input);
        } catch (const std::invalid_argument& e) {
            std::cerr << e.what() << ". Please try again." << std::endl;
        }
    }
}

std::string InputCommands::get_command(const std::string& input) {
    if (command_map.find(input) == command_map.end()) {
        throw std::invalid_argument("Unknown command: " + input);
    }
    return command_map[input];
}