#pragma once

#include <array>

#include "maize.h"

#include "zgame_test/grid_utils.hpp"
#include "zgame_test/rail_types.hpp"
#include "zgame_test/rail_map.hpp"

class RailPlacer : public mz::Updatable
{
private:
    void update(mz::Entity e, float dt) {
        select_rail_type();
        place_rail(e);
    }

    void place_rail(mz::Entity e) {
        if (m_selected_type == Type::None) return;

        if (auto* rail_map = e.write<RailMap>()) {
            if (mz::Input::is_mouse_down(mz::MouseButton::Left)) {
                mz::Vector2f world_position = mz::Camera::get_screen_to_world(
                    mz::Camera::get_main(e), 
                    mz::Input::get_mouse_position()
                );

                rail_map->set_rail(
                    GridUtils::pixel_to_grid(world_position, rail_map->get_cell_size()), 
                    m_selected_type
                );
            }
        }
    }

    void select_rail_type() {
        float mouse_wheel = mz::Input::get_mouse_axis();
        int delta = (mouse_wheel > 0.0f) ? 1 : (mouse_wheel < 0.0f ? -1 : 0);

        if (delta != 0) {
            m_selected_index = (m_selected_index + delta) % 12;
            if (m_selected_index < 0) m_selected_index += 12;
        }

        m_selected_type = all_types()[m_selected_index];
    }

    std::array<Type, 11> all_types() const {
        return {
            Type::NorthSouth,
            Type::WestEast,
            Type::NorthEast,
            Type::NorthWest,
            Type::SouthEast,
            Type::SouthWest,
            Type::TJunctionDown,
            Type::TJunctionUp,
            Type::TJunctionLeft,
            Type::TJunctionRight,
            Type::CrossJunction
        };
    }

private:
    int8_t m_selected_index = 0;
    Type m_selected_type = Type::None;
};