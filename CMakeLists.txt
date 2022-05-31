cmake_minimum_required(VERSION 3.23)
project(Terre)

set(CMAKE_CXX_STANDARD 20)

add_executable(Terre
        src/glad.c
        src/resources/shader/Program.cpp
        src/resources/shader/Program.hpp
        src/resources/shader/Shader.cpp
        src/resources/shader/Shader.hpp
        src/resources/Mesh.cpp
        src/resources/Mesh.h
        src/resources/Texture.cpp
        src/resources/Texture.h
        src/ui/custom/MainMenu.cpp
        src/main.cpp
        src/Game.h
        src/ui/Panel.h
        src/Game.cpp
        src/ui/Panel.cpp
        src/ui/elements/Image.h
        src/ui/elements/Image.cpp
        src/ui/elements/Element.h
        src/ui/elements/Element.cpp
        src/ui/custom/MainMenu.h
        src/main.cpp src/resources/shader/ShaderLoader.cpp src/resources/shader/ShaderLoader.h)

target_link_libraries(Terre SDL2)
target_include_directories(Terre PUBLIC include)

