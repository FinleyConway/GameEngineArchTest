#pragma once

namespace test {
    class Entity;

    template<typename T>
    concept Initialisable = requires(T t, Entity e) {
        t.start(e);
    };

    template<typename T>
    concept Updatable = requires(T t, Entity e, float dt) {
        t.update(e, dt);
    };
}