#pragma once

#include <entt/entt.hpp>

namespace mz
{
    class Scene;

    class Entity
    {
    public:
        Entity() = default;

        template<typename T, typename... Args>
        void add(Args&&... args);

        template<typename T>
        void add_tag();

        template<typename T>
        const T* read() const;

        template<typename T>
        T* write();

        template<typename T>
        bool has() const;

        template<typename T>
        void remove();

        Entity create();

        void kill();

        bool valid() const;

        template<typename T, typename Fn>
        void get_entities_with(Fn&& fn) const;

    private:
        friend class Scene;

        Entity(entt::entity handle, Scene* scene);

    private:
        entt::entity m_handle = entt::null;
        Scene* m_scene = nullptr;
    };
}