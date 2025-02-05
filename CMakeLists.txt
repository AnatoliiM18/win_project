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
    src/renderer.h
    src/renderer.cpp
)

find_package(directx-headers CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
    d3d12.lib
    dxgi.lib
    dxguid.lib
    uuid.lib
    kernel32.lib
    user32.lib
    comdlg32.lib
    advapi32.lib
    shell32.lib
    ole32.lib
    oleaut32.lib
    runtimeobject.lib
    Microsoft::DirectX-Headers
)

add_compile_definitions(UNICODE _UNICODE)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})