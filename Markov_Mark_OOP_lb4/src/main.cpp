#include <iostream>
#include <stdexcept>
#include "game.h"
#include "input/inputCommands.h"
#include "input/gameControl.h"
#include "output/fieldRender.h"
#include "output/messageRender.h"

class Game;

int main() {
    try {
        Game game;
        GameControl<InputCommands, FieldRender, MessageRender> controller(game);

        controller.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
