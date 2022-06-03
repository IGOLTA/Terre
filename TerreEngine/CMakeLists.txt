add_library(TerreEngine SHARED
        src/glad.c
        src/ui/Panel.cpp src/ui/elements/Element.cpp src/ui/elements/Image.cpp
        src/resources/Texture.cpp src/resources/Mesh.cpp src/resources/shader/Program.cpp src/resources/shader/Shader.cpp src/resources/shader/ShaderLoader.cpp
        src/level/Tilemap.cpp
        )

target_link_libraries(TerreEngine SDL2)
target_include_directories(TerreEngine PUBLIC include)
