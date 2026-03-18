#pragma once

#include <entt/entt.hpp>

#include "entity.h"
#include "render.h"

namespace test {
    class Scene
    {
    public: 
        explicit Scene() : m_render(m_registry) { }

        Entity create_entity() {
            entt::entity entity = m_registry.create();

            return Entity(entity, this);
        }

        void remove_entity(Entity entity) {
            entity.kill();
        }

        void start() {
            for (auto& system : m_start_systems) {
                system(*this);
            }
        }

        void update(float dt) {
            for (auto& system : m_update_systems) {
                system(*this, dt);
            }
        }

        void render() {
            m_render.render_entities(m_registry);
        }

    private:
        template<typename T>
        void register_start_system() {
            m_start_systems.emplace_back([](Scene& scene) {
                auto view = scene.m_registry.view<T>();

                if constexpr (std::is_empty_v<T>) { // EnTT optimizes empty components
                    for (auto entity : view) {
                        T comp{};
                        comp.start(Entity(entity, &scene));
                    }
                } 
                else {
                    for (auto entity : view) {
                        auto& comp = view.template get<T>(entity);
                        comp.start(Entity(entity, &scene));
                    }
                }
            });
        }

        template<typename T>
        void register_update_system() {
            m_update_systems.emplace_back([](Scene& scene, float dt) {
                auto view = scene.m_registry.view<T>();

                if constexpr (std::is_empty_v<T>) { // EnTT optimizes empty components
                    for (auto entity : view) {
                        T comp{};
                        comp.update(Entity(entity, &scene), dt);
                    }
                } 
                else {
                    for (auto entity : view) {
                        auto& comp = view.template get<T>(entity);
                        comp.update(Entity(entity, &scene), dt);
                    }
                }
            });
        }

    private:
        friend class Entity;

    private:
        entt::registry m_registry;
        std::vector<std::function<void(Scene&)>> m_start_systems;
        std::vector<std::function<void(Scene&, float)>> m_update_systems;

        Render m_render;
    };
}

#include "entity.inl"