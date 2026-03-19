cmake_minimum_required(VERSION 3.22...3.30)
project(test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(vendor/entt)
add_subdirectory(vendor/raylib)

add_executable(${PROJECT_NAME}
    src/main.cpp

    src/core/input/input.cpp

    src/rendering/render_system.cpp
    src/rendering/sprite.cpp
    src/rendering/texture.cpp

    src/spatial/spatial_index.cpp
    src/spatial/spatial_system.cpp

    src/utils/to_rl.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    EnTT::EnTT
    raylib
)