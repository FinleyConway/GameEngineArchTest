#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "camera.h"
#include "transform.h"
#include "sprite_renderer.h"

#include "spatial_index.h"

class Render 
{
public:
    Render(entt::registry& registry) : m_spatial_index(32.0f) {
        registry.on_update<Transform>().connect<&Render::on_transform_change>(this);
        registry.on_construct<SpriteRenderer>().connect<&Render::on_sprite_renderer_add>(this);
    }

    void render_entities(entt::registry& registery, sf::RenderTarget& target) {
        auto view = registery.view<Transform, Camera>();

        view.each([&](entt::entity entity, Transform& transform, Camera& camera) {
            render_entity_in_camera(registery,transform, camera, target);
        });
    }

private:
    void render_entity_in_camera(entt::registry& registery, const Transform& transform, const Camera& camera, sf::RenderTarget& target) {
        AABB bounds = {
            .x = transform.x,
            .y = transform.y,
            .w = static_cast<float>(target.getSize().x),
            .h = static_cast<float>(target.getSize().y),
        };

        m_spatial_index.query(bounds, [&](entt::entity entity) {
            if (auto* sprite_renderer = registery.try_get<SpriteRenderer>(entity)) {
                target.draw(sprite_renderer->get_sprite());
            }
        });
    }

    void on_sprite_renderer_add(entt::registry& registery, entt::entity entity) {
        auto& transform = registery.get<Transform>(entity);
        auto& sprite_renderer = registery.get<SpriteRenderer>(entity);

        sf::FloatRect bounds = sprite_renderer.get_sprite().getGlobalBounds();

        m_spatial_index.insert(entity, {
            .x = bounds.position.x,
            .y = bounds.position.y,
            .w = transform.x + bounds.size.x,
            .h = transform.y + bounds.size.y,
        });
    }

    // i should batch these to happen at once rather then on change since transform will change alot before drawing phase
    void on_transform_change(entt::registry& registery, entt::entity entity) { 
        if (auto* sprite_renderer = registery.try_get<SpriteRenderer>(entity)) {
            auto& transform = registery.get<Transform>(entity);

            sprite_renderer->get_sprite().setPosition({ transform.x, transform.y });

            sf::FloatRect bounds = sprite_renderer->get_sprite().getGlobalBounds();

            m_spatial_index.remove(entity);
            m_spatial_index.insert(entity, {
                .x = bounds.position.x,
                .y = bounds.position.y,
                .w = transform.x + bounds.size.x,
                .h = transform.y + bounds.size.y,
            });
        }
    }

private:
    SpatialIndex m_spatial_index;
};