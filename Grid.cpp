#include "Grid.h"
#include "raylib.h"

Grid::Grid(int _size, int _width, int _height) : size(_size), width(_width), height(_height)
{
    width_in_cells = measureInCells(width);
    height_in_cells = measureInCells(height);
    r_x = std::uniform_int_distribution<int>(0, (width / size) - 1);
    r_y = std::uniform_int_distribution<int>(0, (height / size) - 1);

    int grid_x_count = width / size;
    int grid_y_count = height / size;

    for (int grid_y = 0; grid_y < grid_y_count; grid_y++)
    {
        for (int grid_x = 0; grid_x < grid_x_count; grid_x++)
        {
            Cell a(grid_x, grid_y, grid_x * size, grid_y * size);
            spaces.push_back(a);
        }
    }
}

void Grid::draw()
{
    for (const Cell &cell : spaces)
    {
        DrawRectangleLines(cell.getWorldX(), cell.getWorldY(), size, size, WHITE);

        DrawText(cell.getSpace().c_str(), cell.getWorldX(), cell.getWorldY(), 18, WHITE);
    }
}

int Grid::measureInCells(int a)
{
    return a / size;
}

int Grid::convertToIndex(const std::pair<int, int> coord)
{
    int i;
    if (measureInCells(coord.first) > width_in_cells - 1 || measureInCells(coord.second) > height_in_cells - 1 || measureInCells(coord.first) < 0 || measureInCells(coord.second) < 0)
    {
        return -1;
    }
    else
    {
        i = (coord.first / size) + (coord.second / size) * (width / size);
    }

    if ((i < 0) || i >= spaces.size())
    {
        return -1;
    }
    else
    {
        return i;
    }
}

std::pair<int, int> Grid::getRandomCell()
{
    for (int i = 0; i <= 15 + static_cast<int>(std::log10(static_cast<int>(spaces.size()))); i++)
    {
        int x = r_x(rng) * size;
        int y = r_y(rng) * size;
        if (spaces[convertToIndex({x, y})].getSpace() == "")
        {
            return {x, y};
        }
    }

    for (int i = 0; i < static_cast<int>(spaces.size()); i++)
    {
        if (spaces[i].getSpace() == "")
        {
            return {spaces[i].getWorldX(), spaces[i].getWorldY()};
        }
    }
}

int Grid::getSize(void) const
{
    return size;
}

int Grid::getWidth(void) const
{
    return width;
}

int Grid::getHeight(void) const
{
    return height;
}

std::vector<Cell>& Grid::getSpaces(void)
{
    return spaces;
}