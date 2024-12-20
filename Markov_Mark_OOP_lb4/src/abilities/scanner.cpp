#include "scanner.h"
#include "../gameField.h"
#include "../shipManager.h"

bool Scanner::apply(GameField& field, int x, int y, ShipManager& manager) {
    bool foundShip = false;

    for(int i = x; i < x + 2; ++i) {
        for(int j = y; j < y + 2; ++j) {
            if(i < field.get_height() && j < field.get_width()) {
                if(field.get_cell_status(j, i) == 2) {
                    foundShip = true;
                    break;
                }
            }
        }
        if (foundShip) break;
    } 

    if (foundShip) {
        return 1;
    } else {
        return 0;
    }
} 
