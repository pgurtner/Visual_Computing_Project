add_executable(Main
        main.cpp
        ShaderProgram.cpp
        ShaderProgram.h
        WebcamPrinter.cpp
        WebcamPrinter.h
        GeometryPrinter.cpp
        GeometryPrinter.h
        constants.h

        ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c
)

add_executable(CameraCalibration
        camera_calibration.cpp
)

add_executable(PhoneTest
        phone_camera_test.cpp
)

add_custom_command(TARGET Main POST_BUILD # workaround for clion
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:Main>/shaders"
)

add_custom_command(TARGET Main POST_BUILD # workaround for clion
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/images"
        "$<TARGET_FILE_DIR:Main>/images"
)

add_custom_command(TARGET CameraCalibration POST_BUILD # workaround for clion
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/images"
        "$<TARGET_FILE_DIR:CameraCalibration>/images"
)

add_custom_command(TARGET PhoneTest POST_BUILD # workaround for clion
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/images"
        "$<TARGET_FILE_DIR:PhoneTest>/images"
)