#pragma once

#include <optional>

// #include "raylib.h"
#include "scene/entity.hpp"
#include "scene/interfaces/initialisable.hpp"
#include "scene/interfaces/updatable.hpp"
#include "scene/components/transform.hpp"
#include "math/vector2.hpp"

#include "zgame_test/grid_utils.hpp"
#include "zgame_test/rail.hpp"
#include "zgame_test/rail_map.hpp"

class MineCart : public test::Initialisable, public test::Updatable
{
struct NextRailInfo;

public:
    void place_on_rail(test::Entity e, Dir init_direction, Rail rail, test::Vector2f position) {
        m_current_travelling_dir = init_direction;
        m_current_rail = rail;
        m_next_position = position;
        m_last_position = position;
        m_current_time = 1;

        e.write<test::Transform>([&](test::Transform& t) {
            t.set_position(position);
        });
    }

private:
    void start(test::Entity e) override {
        place_on_rail(e, Dir::N, Rail(Type::NorthSouth), { 0, 32 });
    }

    void update(test::Entity e, float dt) override {
        m_current_time += dt;

        float t = m_current_time / m_travel_time;

        if (t >= 1.0f) {
            m_last_position = m_next_position;

            get_next_rail_info(e);

            m_current_time = 0.0f;
            t = 0.0f;
        }

        test::Vector2f current_pos = m_last_position.lerp(m_next_position, t);

        e.write<test::Transform>([&](test::Transform& tform) {
            tform.set_position(current_pos);
        });

        // DrawText(std::format("{}", (int)m_current_travelling_dir).c_str(), 5, 5, 12, WHITE);
        // DrawText(std::format("{}", (int)m_current_rail.get_type()).c_str(), 5, 15, 12, WHITE);
        // DrawText(std::format("{}", m_last_position.to_string()).c_str(), 5, 25, 12, WHITE);
        // DrawText(std::format("{}", m_next_position.to_string()).c_str(), 5, 35, 12, WHITE);
        // DrawText(std::format("{}", t).c_str(), 5, 45, 12, WHITE);
    }

    void get_next_rail_info(test::Entity e) {
        e.read_singleton<RailMap>([&](const RailMap& rail_map) {
            test::Vector2i grid_position = GridUtils::pixel_to_grid(
                m_last_position, rail_map.get_cell_size()
            );

            if (auto next = get_next_rail(rail_map, grid_position)) {
                apply_next_rail(next.value(), rail_map);
            }
        });
    }
    
    std::optional<NextRailInfo> get_next_rail(const RailMap& rail_map, test::Vector2i grid_position) {
        // get the next travelling direction
        Dir entry_dir = opposite_dir(m_current_travelling_dir);
        Dir exit_dir = m_current_rail.try_get_exit(entry_dir);

        if (exit_dir == Dir::None) return std::nullopt; // no exit

        // get the next rail based on the next travelling direction
        test::Vector2i next_grid_pos = grid_position + direction_to_offset(exit_dir);
        auto maybe_rail = rail_map.get_rail(next_grid_pos);
        
        if (!maybe_rail) return std::nullopt; // no rail

        // get and return the next rail information
        const Rail& next_rail = maybe_rail.value();
        Dir next_entry = opposite_dir(exit_dir);

        if (!next_rail.is_direction_active(next_entry)) return std::nullopt;

        return NextRailInfo(next_rail, exit_dir, next_grid_pos);
    }

    void apply_next_rail(const NextRailInfo& info, const RailMap& rail_map) {
        m_current_rail = info.rail;
        m_current_travelling_dir = info.travel_dir;
        m_next_position = GridUtils::grid_to_pixel(info.next_grid_pos, rail_map.get_cell_size());
        m_current_time = 0.0f;
    }

    test::Vector2i direction_to_offset(Dir dir) const {
        switch (dir) {
            case Dir::N:    return test::Vector2i(+0, +1);
            case Dir::E:    return test::Vector2i(+1, +0);
            case Dir::S:    return test::Vector2i(+0, -1);
            case Dir::W:    return test::Vector2i(-1, +0);
            default:        return test::Vector2i(+0, +0);
        }
    }

    Dir opposite_dir(Dir dir) const {
        switch (dir) {
            case Dir::N:  return Dir::S;
            case Dir::S:  return Dir::N;
            case Dir::E:  return Dir::W;
            case Dir::W:  return Dir::E;
            default:      return Dir::None;
        }
    }

private:
    struct NextRailInfo 
    {
        Rail rail;
        Dir travel_dir;
        test::Vector2i next_grid_pos;
    };

private:
    test::Vector2f m_next_position;
    test::Vector2f m_last_position;
    float m_current_time = 1.0f;
    float m_travel_time = 0.5f;
    Rail m_current_rail;
    Dir m_current_travelling_dir;
};