#pragma once
#include <string>

class Cell
{
    int x;
    int y;
    int world_x;
    int world_y;
    std::string space;

public:
    Cell(int _x, int _y, int _world_x, int _world_y);

    int getX() const;

    int getY(void) const;

    int getWorldX(void) const;

    int getWorldY(void) const;

    std::string getSpace(void) const;

    void setSpace(std::string _space);
};