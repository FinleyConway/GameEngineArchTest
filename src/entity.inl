#pragma once

#include <cassert>
#include <concepts>

#include "scene.h"
#include "component_interfaces.h"

namespace test {
    template<typename T, typename... Args>
    void Entity::add(Args&&... args) {
        // make sure tat the entity is alive
        if (valid()) {
            // check if it already exists
            if (has<T>()) {
                // if it does we log and return
                // add log
                return;
            }

            // add component and apply it to the update group
            m_scene->m_registry.template emplace<T>(m_handle, std::forward<Args>(args)...);

            if constexpr (std::derived_from<T, IInitialisable>) {
                m_scene->template register_start_system<T, IInitialisable>();
            }

            if constexpr (std::derived_from<T, IUpdatable>) {
                m_scene->template register_update_system<T, IUpdatable>();
            }

            if constexpr (std::derived_from<T, IRenderable>) {
                m_scene->add_renderer_components(m_handle);
            }
        }
    }

    template<typename T>
    const T& Entity::get() {
        if (!has<T>()) assert((void("Entity does not have this component"), false)); // at a log + assert, maybe spdlog in the future

        return m_scene->m_registry.template get<T>(m_handle);
    }

    template<typename T>
    const T* Entity::try_get() {
        if (!has<T>()) return nullptr;
        
        return &m_scene->m_registry.template get<T>(m_handle);
    }

    template<typename T, typename Fn>
    void Entity::mutate(Fn&& fn) {
        m_scene->m_registry.patch<T>(m_handle, std::forward<Fn>(fn));
    }

    template<typename T>
    bool Entity::has() {
        return m_scene->m_registry.template all_of<T>(m_handle);
    }

    template<typename T>
    void Entity::remove() {
        if (valid()) m_scene->m_registry.template remove<T>(m_handle);
    }

    inline void Entity::kill() {
        m_scene->m_registry.destroy(m_handle);
        m_handle = entt::null;
    }

    inline bool Entity::valid() const {
        return m_scene->m_registry.valid(m_handle);
    }

    inline Entity::Entity(entt::entity handle, Scene* scene)
        : m_handle(handle), m_scene(scene) {}
}