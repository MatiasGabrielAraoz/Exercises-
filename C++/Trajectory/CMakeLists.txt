cmake_minimum_required(VERSION 3.16)
project(Trajectory)

find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED raylib)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ${RAYLIB_LINK_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${RAYLIB_INCLUDE_DIRS}
)

# Usar la ubicación exacta de raygui
set(RAYGUI_INCLUDE_DIR "$ENV{HOME}/vcpkg/installed/x64-linux/include")

if(EXISTS "${RAYGUI_INCLUDE_DIR}/raygui.h")
    message(STATUS "✅ raygui encontrado en: ${RAYGUI_INCLUDE_DIR}")
    target_include_directories(${PROJECT_NAME} PRIVATE ${RAYGUI_INCLUDE_DIR})
else()
    message(FATAL_ERROR "❌ No se encontró raygui.h en ${RAYGUI_INCLUDE_DIR}")
endif()