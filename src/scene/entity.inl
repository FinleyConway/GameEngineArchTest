#pragma once

#include <cassert>
#include <concepts>

#include "scene/scene.hpp"
#include "scene/interfaces/initialisable.hpp"
#include "scene/interfaces/updatable.hpp"
#include "scene/interfaces/singleton.hpp"

namespace mz 
{
    template<typename T, typename... Args>
    void Entity::add(Args&&... args) {
        if (!has<T>()) {
            // add component and apply it to the update group
            auto& component = m_scene->m_registry.template emplace<T>(m_handle, std::forward<Args>(args)...);

            if constexpr (std::derived_from<T, Singleton<T>>) {
                m_scene->template register_singleton<T>(&component);
            }

            if constexpr (std::derived_from<T, Initialisable>) {
                m_scene->template register_start_system<T, Initialisable>();
            }

            if constexpr (std::derived_from<T, Updatable>) {
                m_scene->template register_update_system<T, Updatable>();
            }
        }

        // add log "cannot add a component that a entity already has"
    }

    template<typename T>
    void Entity::add_tag() {
        if (has<T>()) {
            // add log "cannot add a tag that a entity already has"
            return;
        }

        m_scene->m_registry.template emplace<T>(m_handle);
    }

    template<typename T>
    const T* Entity::read() const {
        if constexpr (std::derived_from<T, Singleton<T>>) {
            const auto& s = m_scene->m_singletons;

            if (auto it = s.find(typeid(T)); it != s.end()) {
                return static_cast<const T*>(it->second);
            }
        }
        else
        {
            return m_scene->m_registry.template try_get<T>(m_handle);
        }

        return nullptr;
    }

    template<typename T>
    T* Entity::write() {
        if constexpr (std::derived_from<T, Singleton<T>>) {
            auto& s = m_scene->m_singletons;

            if (auto it = s.find(typeid(T)); it != s.end()) {
                return static_cast<T*>(it->second);
            }
        }
        else 
        {
            m_scene->m_registry.patch<T>(m_handle);

            return m_scene->m_registry.template try_get<T>(m_handle);
        }

        return nullptr;
    }

    template<typename T>
    bool Entity::has() const {
        return m_scene->m_registry.template all_of<T>(m_handle) && valid();
    }

    template<typename T>
    void Entity::remove() {
        if (!has<T>()) {
            // add log "cannot remove a component that a entity does not have"
            return;
        }
        
        m_scene->m_registry.template remove<T>(m_handle);
    }

    Entity Entity::create() {
        return m_scene->create_entity();
    }

    void Entity::kill() {
        m_scene->m_registry.destroy(m_handle);
        m_handle = entt::null;
    }

    bool Entity::valid() const {
        return m_scene->m_registry.valid(m_handle);
    }

    template<typename T, typename Fn>
    void Entity::get_entities_with(Fn&& fn) const {
        auto view = m_scene->m_registry.view<T>();

        for (auto entity : view) {
            std::forward<Fn>(fn)(Entity(entity, m_scene));
        }
    }

    Entity::Entity(entt::entity handle, Scene* scene)
        : m_handle(handle), m_scene(scene) {}
}