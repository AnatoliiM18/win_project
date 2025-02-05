#[[
mkdir build
cd build
cmake ..
]]

cmake_minimum_required(VERSION 3.20)

project(win_app
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME}
    WIN32
    src/main.cpp
    src/logger.h
    src/logger.cpp
)

find_package(EASTL CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    EASTL
)

add_compile_definitions(UNICODE _UNICODE)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
