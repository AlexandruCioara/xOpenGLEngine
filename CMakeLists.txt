cmake_minimum_required(VERSION 3.11)
project(xOpenGLEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -lglfw3dll -lopengl32")

include_directories(${PROJECT_SOURCE_DIR}/Include)

link_directories(${PROJECT_SOURCE_DIR}/Libraries)
set(SOURCE_FILES main.cpp src/SourceFiles/glad.c src/SourceFiles/DisplayManager.cpp src/SourceFiles/Shader.cpp src/HeaderFiles/Shader.h)
add_executable(xOpenGLEngine ${SOURCE_FILES})

target_link_libraries(xOpenGLEngine glfw3 opengl32)