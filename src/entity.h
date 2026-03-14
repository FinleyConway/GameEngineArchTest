#pragma once

#include <entt/entt.hpp>

class Scene;

class Entity
{
public:
    Entity() = default;

    template<typename T, typename... Args>
    void add(Args&&... args);

    template<typename T>
    T& get();

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