
#include "sphere.h"

Sphere::Sphere(vec4 center,GLfloat radius,int levels) {

    wireframe = true;
    // 4 faces * 4^levels/face * 3 vertices/triangle
    pointsNum = 4 * pow(4, levels) * 3;

    center[3] = 0; //convert center to a vector
    
    this->vIndex = 0;
    this->levels = levels;
    this->center = center;
    this->radius = radius;

    points = new vec4[pointsNum];
    colors = new color4[pointsNum];
    normals = new vec4[pointsNum];


    /*              A Sphere with 0 subdivisions
     *              ============================
     *
     *                          ,|,
     *                        ,7``\'VA,
     *                      ,7`   |, `'VA,
     *                    ,7`     `\    `'VA,
     *                  ,7`        |,      `'VA,
     *                ,7`          `\         `'VA,
     *              ,7`             |,           `'VA,
     *            ,7`               `\       ,..ooOOTK`
     *          ,7`                  |,.ooOOT''`    AV
     *        ,7`            ,..ooOOT`\`           /7
     *      ,7`      ,..ooOOT''`      |,          AV
     *     ,T,..ooOOT''`              `\         /7
     *    `'TTs.,                      |,       AV
     *         `'TTs.,                 `\      /7
     *              `'TTs.,             |,    AV
     *                   `'TTs.,        `\   /7
     *                        `'TTs.,    |, AV
     *                             `'TTs.,\/7
     *                                 `'T`
     */

    float base = 0.5;
float height = 20;

glBegin(GL_TRIANGLE_FAN);
for(float j=0; j<=height; j+=0.1)
{
    glVertex3f(0,j,0);
    for(int i=0; i<360; i++)
    {
        glVertex3f(radius*sin((float)i),j, radius*cos((float)i));
    }   
}
glEnd();
glPopMatrix();
    float theta = acos(-1/3.0);
    float phi = 2*M_PI/3;
    vec4 v[4] = { 
                 vec4(radius*sin(0.0)*cos(0.0), radius*sin(0.0)*sin(0.0), radius*cos(0.0), 1.0),
                 vec4(radius*sin(theta)*cos(0), radius*sin(theta)*sin(0), radius*cos(theta), 1.0),
                 vec4(radius*sin(theta)*cos(phi), radius*sin(theta)*sin(phi), radius*cos(theta), 1.0),
                 vec4(radius*sin(theta)*cos(2*phi), radius*sin(theta)*sin(2*phi), radius*cos(theta), 1.0)
                };

    //divide each triangle
    createPoints(v[0], v[1], v[2], levels);
    createPoints(v[3], v[2], v[1], levels);
    createPoints(v[0], v[3], v[1], levels);
    createPoints(v[0], v[3], v[2], levels);

    for (int i=0;i<pointsNum;i++)
        points[i] += center;

    for (int i=0;i<pointsNum;i++)
        colors[i] = material.diffuseK;

    this->init();
}

void Sphere::triangle(const vec4&a, const vec4& b, const vec4& c) {

    points[vIndex]  = a; vIndex++;
    points[vIndex]  = b; vIndex++;
    points[vIndex]  = c; vIndex++;
}

inline vec4 projectToSphere(const vec4& p, const float radius) {
    vec4 r;
    float len = length(p);
    if (len > 0.0f)
        r = p / len;

    r *= radius;
    r[3] = 1.0; // w = 1 in points in homogenious coordinates
    return r;
}

void Sphere::createPoints(const vec4&a, const vec4& b, const vec4& c, int depth) {
    if (depth == 0) {
        triangle(a, b, c);
    } else {
        // get midpoints of each side
        // Note: dividing by 2.0 here has no effect
        // as we are going to normalize the points later
        vec4 v0 = (a + b);
        vec4 v1 = (a + c);
        vec4 v2 = (b + c);

        //move them to the circle by the following steps
        // ProjectToSphere function
        //   1- convert point to vector (direction w=0)
        //   2- normalize to get a unit vector
        //   4- multiply the result with radius
        //   3- set w = 1 to convert it to a point again

        v0 = projectToSphere(v0, radius);
        v1 = projectToSphere(v1, radius);
        v2 = projectToSphere(v2, radius);

        // create sub triangles
        createPoints(a, v0, v1, depth - 1);
        createPoints(v0, b, v2, depth - 1);
        createPoints(v1, v2, c, depth - 1);
        createPoints(v0, v1, v2, depth - 1);
    }
}

void Sphere::calculateNormals() {
    // calculate normal for each vertex
    // normal at each vertex = unit vector with direction 
    // equal to a vector from center of sphere to this point
    // 
    // TODO: TASK 1-B
    // 
    // for point p in points
    //  normal at point p = normalize(p - center)



      for (int i = 0 ; i < pointsNum ; i++){
      normals[i]=normalize(points[i]-center);
    }
    
}

void Sphere::render() {
    glBindVertexArray( vao );

    // Draw wireframe of each triangle (as a line loop)
    for (int i=0;i<pointsNum;i+=3)
        glDrawArrays( GL_LINE_LOOP, i, 3);
    
}

Sphere::~Sphere() {
    delete[] points;
    delete[] colors;
    delete[] normals;
}

// ============================================
FilledSphere::FilledSphere(vec4 center, GLfloat radius, int levels) :
    Sphere (center, radius, levels) {

    wireframe = false;
}


void Sphere::move(float angle){
mat4 R ; 

R = RotateZ(angle);
        center=R*center;

for (int i=0;i<pointsNum;i++)
        points[i] =  R*points[i];


}



void FilledSphere::render() {
    glBindVertexArray( vao );
    glDrawArrays( GL_TRIANGLES, 0, pointsNum);
}
