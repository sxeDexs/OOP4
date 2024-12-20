#ifndef ABILITY_H
#define ABILITY_H


class ShipManager;
class GameField;

class Ability {
public:
    virtual bool apply(GameField& field, int x, int y, ShipManager& manager) = 0;
    virtual ~Ability() {}
};

#endif
