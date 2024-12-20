#ifndef BOMBARD_H
#define BOMBARD_H

#include "ability.h"

class Bombard : public Ability {
public:
    bool apply(GameField& filed, int x, int y, ShipManager& manager) override;
};

#endif
