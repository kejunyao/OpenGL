
    cmake_minimum_required(VERSION 3.6.0)

    include_directories(src/main/cpp)

    add_library(
            OpenGL
            SHARED
            src/main/cpp/OpenGL.cpp
    )

    target_link_libraries(
            OpenGL
            OpenSLES
            log
    )



