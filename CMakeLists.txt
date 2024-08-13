cmake_minimum_required(VERSION 3.10)
project(project_4)

set(CMAKE_CXX_STANDARD 14)

# Set policy to suppress the OpenGL warning
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 OLD)
endif()

set(GLAD /path_to_directory/libs/glad)
set(EXTERNAL_LIB_DIR /path_to_directory/libs)

# Add source files from the project
set(PROJECT_SRC
        src/main.cpp
        src/loader.cpp
        src/shader.cpp
        src/drawing_lib.cpp
        src/object.cpp
        src/texture.cpp
)

# Add ImGui source files
set(EXTERNAL_SRC
        ${EXTERNAL_LIB_DIR}/tiny_obj_loader/tiny_obj_loader.cc

)

# Add ImGui source files
set(GLAD_SRC
        ${GLAD}/src/glad.c
)

include_directories(include)

include_directories(${GLAD}/include
        ${EXTERNAL_LIB_DIR}/tiny_obj_loader
        ${EXTERNAL_LIB_DIR}/stb_image_write)


find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED CONFIG)

add_executable(${PROJECT_NAME} ${PROJECT_SRC} ${GLAD_SRC} ${EXTERNAL_SRC})
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw dl)