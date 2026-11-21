//
// Created by uni on 11/19/26.
//

#ifndef VCPROJECT_GEOMETRYPRINTER_H
#define VCPROJECT_GEOMETRYPRINTER_H

#include <glad/glad.h>

#include "ShaderProgram.h"

class GeometryPrinter {
public:
    GeometryPrinter(int, int);
    ~GeometryPrinter ();
    int draw (float) const;

private:
    ShaderProgram shaders;
    GLuint cube_VAO;
    GLuint vertexBufferID;
    GLuint indexBufferID;
    int width;
    int height;
};


#endif //VCPROJECT_GEOMETRYPRINTER_H
