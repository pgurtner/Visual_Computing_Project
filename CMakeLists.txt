cmake_minimum_required(VERSION 3.16)
project(VCProject LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV 4.4 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_subdirectory(src)

target_include_directories(Main PRIVATE
        external/glad/include
)

target_link_libraries(Main
        PRIVATE
        ${OpenCV_LIBS}
        OpenGL::GL
        glfw
)

target_link_libraries(CameraCalibration
        PRIVATE
        ${OpenCV_LIBS}
)

target_link_libraries(PhoneTest
        PRIVATE
        ${OpenCV_LIBS}
)