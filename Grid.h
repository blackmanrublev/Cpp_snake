#pragma once


#include <vector>
#include <random>
#include <string>

enum class Space {Empty, Snake, Apple};

constexpr const char* toString(Space s)
{
    switch (s) 
    {
        case Space::Empty: return "";
        case Space::Snake: return "Snake";
        case Space::Apple: return "Apple";
    }
    return "?";
}

struct Cell
{
    int x;
    int y;
    int world_x;
    int world_y;
    Space space = Space::Empty;
};

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

    int getSize() const;

    int getWidth() const;

    int getHeight() const;

    std::vector<Cell>& getSpaces();
};