#pragma once

#include "math/vector2.hpp"

class GridUtils
{
public:
    static test::Vector2i pixel_to_grid(test::Vector2f p, int32_t cell_size) {
        int32_t grid_x = 0;
        int32_t grid_y = 0;

        if (cell_size != 0) {
            grid_x = std::floor(p.x / cell_size);
            grid_y = std::floor(p.y / cell_size);
        }

        return test::Vector2i(grid_x, grid_y);
    }

    static test::Vector2f grid_to_pixel(test::Vector2i g, int32_t cell_size) {
        return test::Vector2i(
            static_cast<float>(g.x * cell_size), 
            static_cast<float>(g.y * cell_size)
        );
    }
};