//
// Created by uni on 11/19/26.
//

#ifndef VCPROJECT_WEBCAMPRINTER_H
#define VCPROJECT_WEBCAMPRINTER_H

#include <opencv2/opencv.hpp>
#include <glad/glad.h>
#include "ShaderProgram.h"

class WebcamPrinter {
    public:
    explicit WebcamPrinter(const cv::VideoCapture&);
    ~WebcamPrinter ();

    void setup_camera_buffers();
    void setup_texture_buffers();
    int draw ();

private:
    cv::VideoCapture cam;
    cv::Mat frame;
    ShaderProgram shaders;
    GLuint camera_VAO;
    GLuint camera_VBO;
    GLuint camera_EBO;
    GLuint texture;
};


#endif //VCPROJECT_WEBCAMPRINTER_H
