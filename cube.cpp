#include "cube.h"

Cube::Cube(vec4 center, float width, float height,float depth) {
    wireframe = true;
    pointsNum = 24;

    points = new vec4[pointsNum];
    colors = new color4[pointsNum];
    normals = new vec4[pointsNum];

    /*
     *      7 +--------+ 6
     *       /        /|
     *      /        / |
     *      +--------+ |
     *      |3      2| |
     *      |        | + 5
     *      |        | /
     *      |        |/
     *      +--------+
     *      0        1
     */
    int dx[] = {-1,+1,+1,-1,-1,+1,+1,-1};
    int dy[] = {-1,-1,+1,+1,-1,-1,+1,+1};
    int dz[] = {-1,-1,-1,-1,+1,+1,+1,+1};
    vec4 v[8];
    for (int i=0;i<8;i++) {
        v[i] = center;
        v[i].x += dx[i] * width/2;
        v[i].y += dy[i] * height/2;
        v[i].z += dz[i] * depth/2;
    }

    //indices array
    //NOTE: that indexed buffer objects are not used
    unsigned int indices[] = {
        //near plane
        0,1,1,2,2,3,3,0,
        //far plane
        4,5,5,6,6,7,7,4,
        //sides
        0,4,1,5,2,6,3,7
    };

    for (int i=0;i<pointsNum;i++)
        points[i] = v[indices[i]];

    for (int i=0;i<pointsNum;i++)
        colors[i] = (this->material).diffuseK;

    this->init();
}

void Cube::calculateNormals() {
    //wireframe cubes aren't shaded
    //no need for normals calculations
}

void Cube::render() {
    glBindVertexArray( vao );
    glDrawArrays(GL_LINES, 0, pointsNum);
}

Cube::~Cube() {
    delete[] points;
    delete[] colors;
    delete[] normals;
}

//--------------------------------------------------
// FILLED Cube CLASS

FilledCube::FilledCube(vec4 center, float width, float height,float depth) {
    pointsNum = 36;
    points = new vec4[pointsNum];
    colors = new color4[pointsNum];
    normals = new vec4[pointsNum];

    /*
     *      7 +--------+ 6
     *       /        /|
     *      /        / |
     *      +--------+ |
     *      |3      2| |
     *      |        | + 5
     *      |        | /
     *      |        |/
     *      +--------+
     *      0        1
     */

    int dx[] = {-1,+1,+1,-1,-1,+1,+1,-1};
    int dy[] = {-1,-1,+1,+1,-1,-1,+1,+1};
    int dz[] = {+1,+1,+1,+1,-1,-1,-1,-1};
    vec4 v[8];
    for (int i=0;i<8;i++) {
        v[i] = center;
        v[i].x += dx[i] * width/2;
        v[i].y += dy[i] * height/2;
        v[i].z += dz[i] * depth/2;
    }

    //indices array
    //triangles indices (triangles that form the cube faces)
    // NOTE: IBO are not used here for simplicity (vertices are repeated so we
    // can have normal per vertex) indices array is just used to simplify
    // vertices creation
    // NOTE2: indices are arranged such that the cross product of any two lines
    // in a triangle gives a normal to the triangle outwards 
    unsigned int indices[] = {
        //near plane
        0,1,2,0,2,3,
        //far plane
        4,6,5,4,7,6,
        //up plane
        3,2,6,3,6,7,
        //bottom plane
        0,5,1,0,4,5,
        //right side
        1,5,2,2,5,6,
        //left side
        0,3,4,3,7,4
    };

    for (int i=0;i<pointsNum;i++)
        points[i] = v[indices[i]];


    //XXX: Note that this is just a dummy color till the updateColors method 
    //is called with the lights sources available in the scene
    for (int i=0;i<pointsNum;i++)
        colors[i] = (this->material).diffuseK;

    this->init();
}

void FilledCube::calculateNormals() {
    //TODO: TASK 1-A
    //
    // Calculate normals of the cube
    //
    // for each 3 consecutive vertices v0,v1,v2
    //   normal at v0 = normal at v1 = normal at v2 = (v1 - v0) X (v2 - v0)
    //
    //   (remember normals are vectors (w = 0))
    for (int i = 0 ; i < pointsNum ; i+=3){
      normals[i]= normalize(cross(points[i+1]-points[i],points[i+2]-points[i]));
      normals[i+1]=normalize(cross(points[i+1]-points[i],points[i+2]-points[i]));
      normals[i+2]=normalize(cross(points[i+1]-points[i],points[i+2]-points[i]));

      normals[i].w=normals[i+1].w=normals[i+2].w=0;

    }
}

void FilledCube::render() {
    glBindVertexArray( vao );
    glDrawArrays(GL_TRIANGLES, 0, pointsNum);
}


void FilledCube::move(float angle){
mat4 R ; 
if(currentAngle){
  R=RotateZ(-currentAngle);
  for (int i=0;i<pointsNum;i++)
        points[i] =  R*points[i];
}
R = RotateZ(angle);
for (int i=0;i<pointsNum;i++)
        points[i] =  R*points[i];
          this->init();
currentAngle = angle;

}
FilledCube::~FilledCube() {
    delete[] points;
    delete[] colors;
    delete[] normals;
}
