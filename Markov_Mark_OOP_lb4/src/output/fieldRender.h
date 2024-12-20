#ifndef FIELD_RENDERER_H
#define FIELD_RENDERER_H

#include <iostream>
#include <utility> 
#include "../game.h"

class FieldRender {
public:
    void draw_field(Game &game);

    void state_ship(Game &game, bool trigger);

    void show_all_ship(Game &game, bool trigger);

};

#endif