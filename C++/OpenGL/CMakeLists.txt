cmake_minimum_required(VERSION 3.15)
project(OpenGL VERSION 0.1.0)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(my_opengl_project main.cpp)

target_link_libraries(my_opengl_project PUBLIC
        ${OPENGL_LIBRARIES}
        glfw
        glad::glad
        glm::glm
)
