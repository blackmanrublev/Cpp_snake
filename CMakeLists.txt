cmake_minimum_required(VERSION 3.5)
project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RAYLIB_PATH "C:/raylib")

include_directories(${RAYLIB_PATH}/include)
link_directories(${RAYLIB_PATH}/lib)

add_executable(main 
    main.cpp
    Grid.cpp
    Tween.cpp
    Segment.cpp
    Snake.cpp
    Apple.cpp
    ParticleEmitter.cpp
    # Profiler.cpp
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(WIN32)
    target_link_libraries(main raylib gdi32 winmm)
elseif (EMSCRIPTEN)
    target_link_libraries(main raylib.web)
    target_link_options(main PRIVATE
    "--shell-file=C:/emsdk/upstream/emscripten/html/shell_minimal.html"
    "-sUSE_GLFW=3"
    # "-sWASM=1"
    "-sGL_ENABLE_GET_PROC_ADDRESS=1"
    "-sFILESYSTEM=0"
    "-sENVIRONMENT=web"
    "-sSINGLE_FILE"
    "-sEVAL_CTORS"
    "-sMALLOC=emmalloc"
    "-Oz"
    "--closure=1"
    )
    target_compile_options(main PRIVATE
    "-Oz"
    "-fno-rtti"
    "-fno-exceptions"
    "-flto"
    )
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it. 
else()
    target_link_libraries(main raylib)
endif ()
