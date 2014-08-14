#ifndef __sphere_H__
#define __sphere_H__

#include "drawable.h"
class Sphere : public Drawable {
    protected:

        int vIndex; // vertices counter

        int levels; // number of vertices = 4 ^ (levels + 1)

        color4 color;

        vec4 center;
        GLfloat radius;

        void triangle(const vec4&a, const vec4& b, const vec4& c);

        void createPoints(const vec4&a, const vec4& b, const vec4& c, int depth);
       
    public:
        // Sphere constructor
        // vec4 center : center of the sphere
        // float radius : radius of the sphere
        // int levels : number of subdivisions of the basic tetrahedron
        //              big level values will generate a smoother sphere
        //              but in return will generate large number of vertices
        // color4 color: sphere wireframe color
        Sphere(vec4 center, GLfloat radius, int levels);

        //methods
        virtual void render();
        virtual void calculateNormals();
                void move(float angle);


        //destructor
        ~Sphere();
};

class FilledSphere : public Sphere {
    private:
        void calculateLights(std::vector<LightSource*> &, point4);
    public:

        // FilledSphere constructor
        // vec4 center : center of the sphere
        // float radius : radius of the sphere
        // int levels : number of subdivisions of the basic tetrahedron
        //              big level values will generate a smoother sphere
        //              but in return will generate large number of vertices
        // color4 color: sphere wireframe color
        FilledSphere(vec4 center, GLfloat radius, int levels);

        //methods
        virtual void render();
};

#endif
