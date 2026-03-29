#pragma once

#include <cassert>
#include <concepts>

#include "scene/scene.hpp"
#include "scene/interfaces/initialisable.hpp"
#include "scene/interfaces/updatable.hpp"
#include "scene/interfaces/singleton.hpp"

namespace test 
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

    template<typename T, typename Fn>
    void Entity::read(Fn&& fn) const {
        if (!has<T>()) {
            // add log "cannot read from a component that a entity does not have"
            return;
        }

        std::forward<Fn>(fn)(m_scene->m_registry.template get<T>(m_handle));
    }

    template<typename T, typename Fn>
    void Entity::read_singleton(Fn&& fn) const {
        if constexpr (std::is_same_v<T, Scene>) {
            if (!m_scene) return;

            std::forward<Fn>(fn)(*m_scene);
        } 
        else 
        {
            auto it = m_scene->m_singletons.find(typeid(T));
            
            if (it == m_scene->m_singletons.end()) return;

            std::forward<Fn>(fn)(*static_cast<T*>(it->second));
        }
    }

    template<typename T, typename Fn>
    void Entity::write(Fn&& fn) {
        if (!has<T>()) {
            // add log "cannot write to a component that a entity does not have"
            return;
        }

        m_scene->m_registry.patch<T>(m_handle, std::forward<Fn>(fn));
    }

    template<typename T, typename Fn>
    void Entity::write_singleton(Fn&& fn) {
        auto it = m_scene->m_singletons.find(typeid(T));

        if (it == m_scene->m_singletons.end()) {
            // add log "singleton not created"
            return;
        }

        std::forward<Fn>(fn)(*static_cast<T*>(it->second));
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