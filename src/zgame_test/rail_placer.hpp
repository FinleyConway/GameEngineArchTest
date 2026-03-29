#pragma once

#include <array>

#include "core/input/input.hpp"
#include "core/input/mouse.hpp"
#include "math/vector2.hpp"
#include "scene/entity.hpp"
#include "scene/interfaces/updatable.hpp"
#include "scene/scene.hpp"
#include "scene/components/camera.hpp"

#include "zgame_test/grid_utils.hpp"
#include "zgame_test/rail_map.hpp"
#include "zgame_test/rail_types.hpp"

class RailPlacer : public test::Updatable
{
private:
    void update(test::Entity e, float dt) {
        select_rail_type();
        place_rail(e);
    }

    void place_rail(test::Entity e) {
        if (m_selected_type == Type::None) return;

        e.write_singleton<RailMap>([&](RailMap& rail_map) {
            if (test::Input::is_mouse_down(test::MouseButton::Left)) {
                test::Vector2f world_position; 

                e.read_singleton<test::Scene>([&](test::Scene& scene) {
                    test::Entity camera_e = scene.get_main_camera();

                    camera_e.read<test::Camera>([&](const test::Camera& camera) {
                        world_position = camera.get_screen_to_world(camera_e, test::Input::get_mouse_position());
                    });
                });

                rail_map.set_rail(
                    GridUtils::pixel_to_grid(world_position, rail_map.get_cell_size()), 
                    m_selected_type
                );
            }
        });
    }

    void select_rail_type() {
        float mouse_wheel = test::Input::get_mouse_axis();
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