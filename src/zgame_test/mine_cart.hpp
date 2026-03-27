#pragma once

#include "scene/entity.hpp"
#include "scene/interfaces/updatable.hpp"
#include "scene/components/transform.hpp"
#include "math/vector2.hpp"

#include "rail.hpp"

Rail get_next_rail(test::Vector2i position);

class MineCart : public test::Updatable
{
private:
    void update(test::Entity e, float dt) {
        Rail rail = get_next_rail(get_direction_offset());
        
        Dir next_direction = rail.try_get_exit(m_current_travelling_dir);
        bool is_new_rail = !is_current_rail(rail);

        if (next_direction != Dir::None && is_new_rail) {
            
        }
    }

    void place_on_rail(test::Entity e, Dir init_direction, Rail rail, test::Vector2f position) {
        m_current_travelling_dir = init_direction;
        m_current_rail = rail;
        m_next_position = position;
        m_last_position = position;
        m_current_time = 0;

        e.write<test::Transform>([&](test::Transform& t) {
            t.set_position(position);
        });
    }

private:
    bool is_current_rail(Rail rail) const {
        return m_current_rail.get_type() == rail.get_type();
    }

    test::Vector2i get_direction_offset() const {
        switch (m_current_travelling_dir) {
            case Dir::N:    return test::Vector2i(+0, +1);
            case Dir::NE:   return test::Vector2i(+1, +1);
            case Dir::E:    return test::Vector2i(+1, +0);
            case Dir::SE:   return test::Vector2i(+1, -1);
            case Dir::S:    return test::Vector2i(+0, -1);
            case Dir::SW:   return test::Vector2i(-1, -1);
            case Dir::W:    return test::Vector2i(-1, +0);
            case Dir::NW:   return test::Vector2i(-1, +1);
            default:        return test::Vector2i(+0, +0);
        }
    }

private:
    test::Vector2f m_next_position;
    test::Vector2f m_last_position;
    float m_current_time = 0;

    Dir m_current_travelling_dir;
    Rail m_current_rail;
};