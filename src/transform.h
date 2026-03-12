#pragma once

#include <iostream>
#include <string>

#include "component.h"

class Trasform : public Component<Trasform> 
{
public:
    float x = 0;
    float y = 0;

public:
    std::string to_str() {
        return std::format("[x:{}, y:{}]", x, y);
    }
};

class Player : public Component<Player>
{
public:
    void update() override {
        if (auto* t = entity().get_component<Trasform>()) {
            std::cout << "My name is player " << entity().get_id() << "! Im at position: " << t->to_str() << std::endl;
        }
    }
};