#ifndef DRAW_FIELD_H
#define DRAW_FIELD_H

#include <iostream>
#include <utility> 
#include "../shipManager.h"
#include "../ship.h"
#include "../gameField.h"

class DrawField {
public:
    void draw_with_fog_war(GameField& field, ShipManager& manager, bool trigger);

    void draw_all_ship(GameField& field);

    void draw_state(ShipManager& manager);

};

#endif