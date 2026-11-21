//
// Created by uni on 11/19/26.
//

#include <glm/gtc/matrix_transform.hpp>
#include "GeometryPrinter.h"
#include "constants.h"

GeometryPrinter::GeometryPrinter (const int width, const int height): shaders("shaders/triangle.vert", "shaders/triangle.frag"), width(width), height(height) {
    glGenVertexArrays(1, &cube_VAO);
    glBindVertexArray(cube_VAO);

    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, cube_geometry.size() * sizeof(glm::vec3), cube_geometry.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube_line_indices.size() * sizeof(GLuint), cube_line_indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glVertexAttribPointer(
        0, // attribute
        3, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        sizeof(glm::vec3), // stride - 0= tightly packed
        nullptr // array buffer offset
    );
}

GeometryPrinter::~GeometryPrinter () {
    glDeleteVertexArrays(1, &cube_VAO);
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteBuffers(1, &indexBufferID);
}

int GeometryPrinter::draw (const float theta) const {
    /**
         *      * detect and track target
         *      * estimate pose
         *      * coordinate system conversion
         *
         */

    glEnable(GL_DEPTH_TEST);

    glBindVertexArray(cube_VAO);

    shaders.use();
    shaders.setVec4("color", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

    const glm::vec3 axis(0.0f, 0.0f, 1.0f);
    const glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), theta, axis);

    const glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f,
        100.0f
    );
    const glm::mat4 view = glm::lookAt(
        glm::vec3(4, 3, 3),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );
    const glm::mat4 model = glm::mat4(1.0f);

    const glm::mat4 MVPmatrix = projection * view * model * rotation;
    shaders.setMat4("MVP", MVPmatrix);

    glDrawElements(
        GL_LINES,
        cube_line_indices.size(),
        GL_UNSIGNED_INT,
        nullptr
    );

    return 0;
}
