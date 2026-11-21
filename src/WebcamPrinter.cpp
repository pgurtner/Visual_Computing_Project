//
// Created by uni on 11/19/26.
//

#include "WebcamPrinter.h"
#include "constants.h"

WebcamPrinter::WebcamPrinter (const cv::VideoCapture& cam): cam(cam), shaders("shaders/frame.vert", "shaders/frame.frag") {
    setup_camera_buffers();
    setup_texture_buffers();
}

WebcamPrinter::~WebcamPrinter () {
    glDeleteVertexArrays(1, &camera_VAO);
    glDeleteBuffers(1, &camera_VBO);
    glDeleteBuffers(1, &camera_EBO);
    glDeleteTextures(1, &texture);
}

void WebcamPrinter::setup_camera_buffers () {
    glGenVertexArrays(1, &camera_VAO);
    glBindVertexArray(camera_VAO);

    glGenBuffers(1, &camera_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, camera_VBO);
    glBufferData(GL_ARRAY_BUFFER, camera_canvas.size() * sizeof(float), camera_canvas.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &camera_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, camera_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, camera_canvas_indices.size() * sizeof(GLuint), camera_canvas_indices.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, camera_VBO);
    glVertexAttribPointer(
        0, // attribute
        2, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        4 * sizeof(float),
        nullptr // array buffer offset
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),
        reinterpret_cast<void*>(2 * sizeof(float))
    );
    glEnableVertexAttribArray(1);
}

void WebcamPrinter::setup_texture_buffers () {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    const int frame_width = static_cast<int>(cam.get(cv::CAP_PROP_FRAME_WIDTH));
    const int frame_height = static_cast<int>(cam.get(cv::CAP_PROP_FRAME_HEIGHT));

    // according to Chattie, calling this with pixels=nullptr already allocates GPU memory, so this is intended
    // glTexImage2D can allocate memory, while glTexSubImage only updates
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        frame_width,
        frame_height,
        0,
        GL_BGR,
        GL_UNSIGNED_BYTE,
        nullptr
    );
}

int WebcamPrinter::draw () {
    glDisable(GL_DEPTH_TEST);

    auto ret = cam.read(frame);
    if (!ret) {
        std::cerr << "Error: Could not capture frame." << std::endl;
        return -1;
    }

    glBindVertexArray(camera_VAO);

    shaders.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        0, 0,
        frame.cols,
        frame.rows,
        GL_BGR,
        GL_UNSIGNED_BYTE,
        frame.data
    );

    shaders.setInt1("frameTexture", 0);

    glDrawElements(
        GL_TRIANGLES,
        6,
        GL_UNSIGNED_INT,
        nullptr
    );

    glClear(GL_DEPTH_BUFFER_BIT);

    return 0;
}