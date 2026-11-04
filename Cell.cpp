#include "Cell.h"


Cell::Cell(int _x, int _y, int _world_x, int _world_y) : x(_x), y(_y), world_x(_world_x), world_y(_world_y) {}

int Cell::getX(void) const
{
    return x;
}

int Cell::getY(void) const
{
    return y;
}

int Cell::getWorldX(void) const
{
    return world_x;
}

int Cell::getWorldY(void) const
{
    return world_y;
}

std::string Cell::getSpace(void) const
{
    return space;
}

void Cell::setSpace(std::string _space)
{
    space = _space;
}
