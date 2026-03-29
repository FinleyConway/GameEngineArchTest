#pragma once

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <functional>
#include <unordered_set>

#include <entt/entt.hpp>

#include "scene/entity.hpp"
#include "rendering/render_system.hpp"
#include "spatial/spatial_system.hpp"

namespace mz 
{
    class Renderer;

    class Scene
    {
    public: 
        Scene(Renderer& renderer);

        Entity create_entity();

        void start();

        void update(float dt);

        void render();

        void end();

    private:
        template<typename T, typename TInterface>
        void register_start_system();

        template<typename T, typename TInterface>
        void register_update_system();

        template<typename T>
        void register_singleton(T* component);

    private:
        friend class Entity;

    private:
        entt::registry m_registry;
        std::vector<std::function<void(Scene&)>> m_start_systems;
        std::unordered_set<std::type_index> m_registered_start_systems;

        std::vector<std::function<void(Scene&, float)>> m_update_systems;
        std::unordered_set<std::type_index> m_registered_update_systems;

        std::unordered_map<std::type_index, void*> m_singletons;

        SpatialSystem m_spatial_system;
        RenderSystem m_render_system;

        bool m_started = false;
    };
}

#include "scene/scene.inl"
#include "scene/entity.inl"