#pragma once

#include <entt/entt.hpp>

namespace test {
    class Scene;

    class Entity
    {
    public:
        Entity() = default;

        template<typename T, typename... Args>
        void add(Args&&... args);

        template<typename T>
        const T& get();

        template<typename T>
        const T* try_get();

        template<typename T, typename Fn>
        void mutate(Fn&& fn);

        template<typename T>
        bool has();

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