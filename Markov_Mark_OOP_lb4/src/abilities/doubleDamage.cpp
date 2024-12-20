#include "doubleDamage.h"
#include "../gameField.h"
#include "../shipManager.h"

bool DoubleDamage::apply(GameField& field, int x, int y, ShipManager& manager) {
    field.set_double_damage(true);
    return 1;
}