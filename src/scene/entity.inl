#pragma once

#include <cassert>
#include <concepts>

#include "scene/scene.hpp"
#include "scene/interfaces/initialisable.hpp"
#include "scene/interfaces/updatable.hpp"

namespace test 
{
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

            if constexpr (std::derived_from<T, Initialisable>) {
                m_scene->template register_start_system<T, Initialisable>();
            }

            if constexpr (std::derived_from<T, Updatable>) {
                m_scene->template register_update_system<T, Updatable>();
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
        if (!has<T>()) {
            // add log
            return;
        }

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