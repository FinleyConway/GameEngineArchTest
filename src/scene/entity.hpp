#pragma once

#include <entt/entt.hpp>

namespace test
{
    class Scene;

    class Entity
    {
    public:
        Entity() = default;

        template<typename T, typename... Args>
        void add(Args&&... args);

        template<typename T, typename Fn>
        void read(Fn&& fn) const;

        template<typename T, typename Fn>
        void read_singleton(Fn&& fn) const;

        template<typename T, typename Fn>
        void write(Fn&& fn);

        template<typename T, typename Fn>
        void write_singleton(Fn&& fn);

        template<typename T>
        bool has() const;

        template<typename T>
        void remove();

        void kill();

        bool valid() const;

    private:
        friend class Scene;

        Entity(entt::entity handle, Scene* scene);

    private:
        entt::entity m_handle = entt::null;
        Scene* m_scene = nullptr;
    };
}