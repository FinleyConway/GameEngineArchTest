cmake_minimum_required(VERSION 3.22...3.30)
project(test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor/entt)
add_subdirectory(vendor/SFML)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(test PRIVATE 
    EnTT::EnTT
    SFML::Graphics
)