#pragma once

#include "scene/scene.hpp"
#include <memory>

namespace test 
{
    Scene::Scene(Renderer& renderer) : m_spatial_system(m_registry), m_render_system(renderer, m_spatial_system) { 
    }

    Entity Scene::create_entity() {
        entt::entity entity = m_registry.create();

        return Entity(entity, this);
    }

    void Scene::remove_entity(Entity entity) {
        entity.kill();
    }

    void Scene::start() {
        if (!m_started) {
            m_started = true;

            for (auto& system : m_start_systems) {
                system(*this);
            }
        }
    }

    void Scene::update(float dt) {
        for (auto& system : m_update_systems) {
            system(*this, dt);
        }
    }

    void Scene::render() {
        m_render_system.render(m_registry);
    }

    void Scene::end() {
        m_started = false;
    }

    template<typename T, typename TInterface>
    void Scene::register_start_system() {
        auto type = std::type_index(typeid(T));

        if (m_registered_start_systems.contains(type)) return; // add log?

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
    void Scene::register_update_system() {
        auto type = std::type_index(typeid(T));

        if (m_registered_update_systems.contains(type)) return; // add log?

        m_registered_update_systems.insert(type);

        m_update_systems.emplace_back([](Scene& scene, float dt) {
            auto view = scene.m_registry.view<T>();

            for (auto entity : view) {
                auto& comp = view.template get<T>(entity); 
                static_cast<TInterface&>(comp).update(Entity(entity, &scene), dt);
            }
        });
    }

    template<typename T>
    void Scene::register_singleton(T* component) {
        auto type = std::type_index(typeid(T));

        if (m_singletons.contains(type)) return; // add log?

        m_singletons.emplace(type, component);
    }
}