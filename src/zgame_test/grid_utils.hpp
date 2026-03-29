#pragma once

#include "maize.h"

class GridUtils
{
public:
    static mz::Vector2i pixel_to_grid(mz::Vector2f p, int32_t cell_size) {
        int32_t grid_x = 0;
        int32_t grid_y = 0;

        if (cell_size != 0) {
            grid_x = std::floor(p.x / cell_size);
            grid_y = std::floor(p.y / cell_size);
        }

        return mz::Vector2i(grid_x, grid_y);
    }

    static mz::Vector2f grid_to_pixel(mz::Vector2i g, int32_t cell_size) {
        return mz::Vector2i(
            static_cast<float>(g.x * cell_size), 
            static_cast<float>(g.y * cell_size)
        );
    }
};