cmake_minimum_required(VERSION 3.31)
project(OGL)

set(CMAKE_CXX_STANDARD 23)

add_executable(OGL src/main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(OGL
        OpenGL::GL
        OpenGL::GLU
        GLUT::GLUT
        GLEW::GLEW
)