#pragma once

#include "core/window.hpp"
#include "rendering/renderer.hpp"
#include "scene/scene_manager.hpp"

namespace test
{
    struct ApplicationConfig
    {
        Vector2i window_size;
        std::string window_title;
    };

    class Application
    {
    public:
        Application(const ApplicationConfig& config) : 
            m_window(config.window_size.x, config.window_size.y, config.window_title) {
        }

        template<typename Fn>
        void add_scene(const std::string& identifier, Fn&& fn) {
            auto scene = std::make_unique<Scene>(m_renderer);

            std::forward<Fn>(fn)(*scene.get());                          

            m_scene_manager.add_scene(identifier, std::move(scene));
        }

        void set_current_scene(const std::string& identifier) {
            m_scene_manager.set_current_scene(identifier);
        }

        void run() {
            while (m_window.is_window_open()) {
                if (auto* scene = m_scene_manager.get_current_scene()) {
                    scene->update(GetFrameTime());

                    m_renderer.draw_in_window([&]() {
                        scene->render();
                    }); 
                }
            }
        }

    private:
        Window m_window;
        Renderer m_renderer;
        SceneManager m_scene_manager;
    };
}