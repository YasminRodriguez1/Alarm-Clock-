#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include "include/Angel.h"
#include "material.h"
#include "light_source.h"
#include <vector>

class Drawable {
    public:
        static GLuint shaderProgram;

        int pointsNum;
        vec4* points;
        color4* colors;
        vec4* normals;

        Material material;

        Drawable();

        //methods
        // copy points and colors back to opengl buffers
        void update();

        // updates objects colors based on light sources
        void shade(std::vector<LightSource*>&, point4);

        //calculate a unit normal vector for each vertex
        virtual void calculateNormals();

        virtual void render();

        //destructor
        ~Drawable();

    protected:

        bool normalsCalculated;
        bool wireframe;

        //vertex array object
        GLuint vao;

        //vertex buffer
        GLuint vbuffer;

        //color buffer
        GLuint cbuffer;

        void init();
};

#endif
