cmake_minimum_required(VERSION 3.16)
project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RAYLIB_PATH "C:/raylib")

include_directories(${RAYLIB_PATH}/include)
link_directories(${RAYLIB_PATH}/lib)

add_executable(main 
    main.cpp
    Grid.cpp
    Tween.cpp
    Cell.cpp
    Segment.cpp
    Snake.cpp
    Apple.cpp
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(WIN32)
    target_link_libraries(main raylib opengl32 gdi32 winmm)
else()
    target_link_libraries(main raylib)
endif()
