#include "cylinder.h"

Cylinder::Cylinder(vec4 center, float radius, float height) {
    pointsNum =146;
     points= new vec4[pointsNum];

    color4 color = vec4(1,0,0,1);
    colors = new color4[pointsNum];
    normals = new vec4[pointsNum];
    vec4 Transition = vec4(0,0,height/2,0);

vec4 center1 = center + Transition;
    points[0] = center1;
    colors[0] = color;
    for (int i=1;i<37;i++){
        double angle = 360.0/(30) * i;
        double rad = angle / 180.0 * 3.1415;
        points[i] = center1 + vec4(radius*cos(rad),radius*sin(rad),0,0);
      //  colors[i] = color;
    }

    vec4 center2 = center - Transition;
    points[37] = center2;
    colors[37] = color;
    for (int i=38;i<74;i++){
        double angle = 360.0/(30) * i;
        double rad = angle / 180.0 * 3.1415;
        points[i] = center2 + vec4(radius*cos(rad),radius*sin(rad),0,0);
       // colors[i] = color;
    }
 
          for (int i=74;i<pointsNum;i+=2){
         double angle = 360.0/(30) * i;
        double rad = angle / 180.0 * 3.1415;
        points[i] = center1 + vec4(radius*cos(rad),radius*sin(rad),0,0);
        points[i+1] = center2 + vec4(radius*cos(rad),radius*sin(rad),0,0);

     //   colors[i] = color;
    }
   

     for (int i=0;i<pointsNum;i++)
        colors[i] = (this->material).diffuseK;

    this->init();
}

void Cylinder::calculateNormals() {
    for (int i=1;i<37;i++){
      normals[i]=normalize(points[i]-vec4(0,0,1,1));

     }

  
    for (int i=38;i<74;i++){
      normals[i]=normalize(points[i]-vec4(0,0,-1,1));

    }
 
    for (int i=74;i<pointsNum;i+=2){
      normals[i]=normalize(points[i]-vec4(0,0,0,1));

    }
   
}

void Cylinder::render() {
    glBindVertexArray( vao );
    glDrawArrays( GL_TRIANGLE_FAN, 0, 37);
        glDrawArrays( GL_TRIANGLE_FAN,37, 37);
                //glDrawArrays( GL_TRIANGLES,74, 72);
  for (int i=74;i<pointsNum;i++)
       glDrawArrays( GL_TRIANGLES, i, 3);

}



Cylinder::~Cylinder() {
    delete[] points;
    delete[] colors;
    delete[] normals;
}
