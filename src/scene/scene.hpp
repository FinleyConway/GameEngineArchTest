#pragma once

#include <vector>
#include <typeindex>
#include <functional>
#include <unordered_set>

#include <entt/entt.hpp>

#include "scene/entity.hpp"
#include "rendering/render_system.hpp"
#include "spatial/spatial_system.hpp"

namespace test 
{
    class Renderer;

    class Scene
    {
    public: 
        Scene(Renderer& renderer);

        Entity create_entity();

        void remove_entity(Entity entity);

        void start();

        void update(float dt);

        void render();

    private:
        template<typename T, typename TInterface>
        void register_start_system();

        template<typename T, typename TInterface>
        void register_update_system();

    private:
        friend class Entity;

    private:
        entt::registry m_registry;
        std::vector<std::function<void(Scene&)>> m_start_systems;
        std::unordered_set<std::type_index> m_registered_start_systems;

        std::vector<std::function<void(Scene&, float)>> m_update_systems;
        std::unordered_set<std::type_index> m_registered_update_systems;

        SpatialSystem m_spatial_system;
        RenderSystem m_render_system;
    };
}

#include "scene/scene.inl"
#include "scene/entity.inl"