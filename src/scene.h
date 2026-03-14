#pragma once

#include <entt/entt.hpp>

#include "entity.h"

class Scene
{
public:
    Entity create_entity() {
        entt::entity entity = m_registry.create();

        return Entity(entity, this);
    }

    void remove_entity(Entity entity) {
        entity.kill();
    }

    void update(float dt) {
        for (auto& system : m_update_systems)
            system(*this, dt);
    }


private:
    template<typename T>
    void register_update_system() {
        m_update_systems.emplace_back([](Scene& scene, float dt) {
            auto view = scene.m_registry.view<T>();

            for (auto entity : view) {
                auto& comp = view.template get<T>(entity);
                comp.update(Entity(entity, &scene), dt);
            }
        });
    }

private:
    friend class Entity;

private:
    entt::registry m_registry;
    std::vector<std::function<void(Scene&, float)>> m_update_systems;
};

#include "entity.inl"