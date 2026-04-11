# GameEngineArchTest
A 2D Game Engine built using Raylib and EnTT

## Building
See the official Raylib build instructions:
https://github.com/raysan5/raylib#build-and-installation

```bash
git clone https://github.com/FinleyConway/GameEngineArchTest.git
cd GameEngineArchTest
cmake -S . -B build && cmake --build build
./build/bin/test # run engine
```

>[!NOTE]
>Wayland is hardcoded, set GLFW_BUILD_WAYLAND to OFF for X11 legacy systems.
