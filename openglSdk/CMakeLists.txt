
    cmake_minimum_required(VERSION 3.6.0)

    include_directories(src/main/cpp)

    add_library(
            NativeOpenGL
            SHARED
            src/main/cpp/egl/EglHelper.cpp
            src/main/cpp/NativeOpenGL.cpp
    )

    target_link_libraries(
            NativeOpenGL

            EGL
            GLESv2
            android

            log
    )



