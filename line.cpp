#include "line.h"

Line::Line(vec4 s,vec4 e,color4 color) {
    wireframe = true;
    pointsNum = 2;
    points = new vec4[pointsNum];
    colors = new color4[pointsNum];
    points[0] = s;
    points[1] = e;
    colors[0] = color;
    colors[1] = color;
    this->init();
}

Line::Line(GLfloat x1, GLfloat y1, GLfloat z1,
        GLfloat x2, GLfloat y2, GLfloat z2, color4 color) {
    pointsNum = 2;
    points = new vec4[pointsNum];
    colors = new color4[pointsNum];
    points[0] = vec4(x1,y1,z1,1.0);
    points[1] = vec4(x2,y2,z1,1.0);
    colors[0] = color;
    colors[1] = color;
    this->init();
}

void Line::render() {
    glBindVertexArray( vao );
    glDrawArrays( GL_LINES , 0, pointsNum);
}

Line::~Line() {
    delete[] points;
    delete[] colors;
}
