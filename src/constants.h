//
// Created by uni on 11/21/26.
//

#ifndef VCPROJECT_CONSTANTS_H
#define VCPROJECT_CONSTANTS_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

// for portability
constexpr float PI = 3.14159265358979323846f;

const std::vector<glm::vec3> cube_geometry = {
    {-1, -1, -1},
    {1, -1, -1},
    {1, 1, -1},
    {-1, 1, -1},

    {-1, -1, 1},
    {1, -1, 1},
    {1, 1, 1},
    {-1, 1, 1}
};

const std::vector<GLuint> cube_line_indices = {
    // Back face
    0, 1,
    1, 2,
    2, 3,
    3, 0,

    // Front face
    4, 5,
    5, 6,
    6, 7,
    7, 4,

    // Connecting edges
    0, 4,
    1, 5,
    2, 6,
    3, 7
};

const std::vector<float> camera_canvas = {
    // position      // UV
    -1.0f, -1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f, 0.0f
};

const std::vector<GLuint> camera_canvas_indices = {
    0, 1, 2,
    2, 3, 0
};


#endif //VCPROJECT_CONSTANTS_H
