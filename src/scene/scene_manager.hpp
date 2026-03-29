#pragma once

#include <memory>
#include <unordered_map>

#include "scene/scene.hpp"

namespace mz
{
    class SceneManager
    {
    public:
        void add_scene(const std::string& identifier, std::unique_ptr<Scene> scene) {
            m_scenes.emplace(identifier, std::move(scene));
        }

        void set_current_scene(const std::string& identifier) {
            if  (m_current_scene != nullptr) {
                m_current_scene->end();
            }

            if (m_scenes.contains(identifier)) {
                m_current_scene = m_scenes.at(identifier).get();
                m_current_scene->start();
            }
        }

        Scene* get_current_scene() {
            return m_current_scene;
        }

    private:
        std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;
        Scene* m_current_scene = nullptr; // this should be safe as scenes cannot be added once the calls run()
    };  
}