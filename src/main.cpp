//
// Created by uni on 11/19/26.
//
#include <iostream>

#include<opencv2/opencv.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GeometryPrinter.h"
#include "WebcamPrinter.h"
#include "constants.h"


int main () {
    const auto cam = cv::VideoCapture(0);
    if (!cam.isOpened()) {
        std::cerr << "Could not access the webcam.";
        return 1;
    }

    const int frame_width = static_cast<int>(cam.get(cv::CAP_PROP_FRAME_WIDTH));
    const int frame_height = static_cast<int>(cam.get(cv::CAP_PROP_FRAME_HEIGHT));

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }

    // enforce specific OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // todo: what does this do?
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);


    const std::string windowName = "Window";
    const auto window = glfwCreateWindow(frame_width, frame_height, windowName.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to open GLFW window.\n";
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // todo: this feels very unclean, is this how versions are enforced in OpenGL?
    GLint major = 0;
    GLint minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    if (major < 4 || (major == 4 && minor < 6))
    {
        std::cerr << "OpenGL 4.6 or newer required. Got "
                  << major << "." << minor << '\n';

        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }


    {
        WebcamPrinter webcam_printer{cam};
        GeometryPrinter geometry_printer{frame_width, frame_height};
        float theta = 0.0;

        while (!glfwWindowShouldClose(window)) {
            glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            theta += 0.02;
            if (theta >= 2 * PI) {
                theta = 0.0;
            }

            // draw webcam, needs: frame
            webcam_printer.draw();
            geometry_printer.draw(theta);

            // draw cube
            // detect features, needs: frame
            // match features, needs: features
            // project and draw cube points, needs: K, R, t

            // general OpenGL stuff
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    // has to happen after printer destructors are called
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

