cmake_minimum_required(VERSION 3.15)
project(jpg2BgrNv12Txt)

set(CMAKE_CXX_STANDARD 14)

add_executable(jpg2BgrNv12Txt main.cpp)
target_link_libraries(jpg2BgrNv12Txt
        "-Wl,-Bdynamic"
        -lopencv_core
        -lopencv_imgproc
        -lopencv_imgcodecs
        )