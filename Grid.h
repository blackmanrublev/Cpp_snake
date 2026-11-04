#pragma once


#include <vector>
#include "Cell.h"
#include <random>

class Grid
{
    std::vector<Cell> spaces;
    int size;
    int width;
    int height;
    int width_in_cells;
    int height_in_cells;
    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> r_x;
    std::uniform_int_distribution<int> r_y;

public:
    Grid(int _size, int _width, int _height);

    void draw();

    int measureInCells(int a);

    int convertToIndex(const std::pair<int, int> coord);

    std::pair<int, int> getRandomCell();

    int getSize(void) const;

    int getWidth(void) const;

    int getHeight(void) const;

    std::vector<Cell>& getSpaces(void);
};