#pragma once

#include <vector>
#include <typeindex>
#include <functional>
#include <unordered_set>

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
        template<typename T, typename TInterface>
        void register_start_system() {
            auto type = std::type_index(typeid(T));
            if (m_registered_start_systems.contains(type)) return;

            m_registered_start_systems.insert(type);

            m_start_systems.emplace_back([](Scene& scene) {
                auto view = scene.m_registry.view<T>();

                for (auto entity : view) {
                    auto& comp = view.template get<T>(entity); 
                    static_cast<TInterface&>(comp).start(Entity(entity, &scene));
                }
            });
        }

        template<typename T, typename TInterface>
        void register_update_system() {
            auto type = std::type_index(typeid(T));
            if (m_registered_update_systems.contains(type)) return;

            m_registered_update_systems.insert(type);

            m_update_systems.emplace_back([](Scene& scene, float dt) {
                auto view = scene.m_registry.view<T>();

                for (auto entity : view) {
                    auto& comp = view.template get<T>(entity); 
                    static_cast<TInterface&>(comp).update(Entity(entity, &scene), dt);
                }
            });
        }

        void add_renderer_components(entt::entity entity) {
            m_render.on_renderer_add(m_registry, entity);
        }

    private:
        friend class Entity;

    private:
        entt::registry m_registry;
        std::vector<std::function<void(Scene&)>> m_start_systems;
        std::unordered_set<std::type_index> m_registered_start_systems;

        std::vector<std::function<void(Scene&, float)>> m_update_systems;
        std::unordered_set<std::type_index> m_registered_update_systems;

        Render m_render;
    };
}

#include "entity.inl"