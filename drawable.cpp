#include "drawable.h"

#define EDIT_HERE 0000

GLuint Drawable::shaderProgram = 0;

Drawable::Drawable() {
    normalsCalculated = false;
    wireframe = false;
}

void Drawable::render() {} 
void Drawable::calculateNormals() {}

void Drawable::init() {
    // Create a vertex array object
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // BUFFERS
    // Create and initialize a buffer object
    // First vertex buffer
    glGenBuffers( 1, &vbuffer );
    glBindBuffer( GL_ARRAY_BUFFER, vbuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vec4) * pointsNum, points, GL_STATIC_DRAW );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( shaderProgram, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 4, GL_FLOAT, GL_FALSE, 0,
            BUFFER_OFFSET(0));

    // Second color buffer
    glGenBuffers( 1, &cbuffer );
    glBindBuffer( GL_ARRAY_BUFFER, cbuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vec4) * pointsNum, colors, GL_STATIC_DRAW );


    // Initialize the vertex color attribute from the vertex shader
    GLuint loc2 = glGetAttribLocation( shaderProgram, "vColor" );
    glEnableVertexAttribArray( loc2 );
    glVertexAttribPointer( loc2, 4, GL_FLOAT, GL_FALSE, 0,
            BUFFER_OFFSET(0));
}

void Drawable::update() {
    glBindVertexArray( vao );

    //vbuffer
    glBindBuffer( GL_ARRAY_BUFFER, vbuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vec4) * pointsNum, points, GL_STATIC_DRAW );

    //cbuffer
    glBindBuffer( GL_ARRAY_BUFFER, cbuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vec4) * pointsNum, colors, GL_STATIC_DRAW );
}


void Drawable::shade(std::vector<LightSource*> & lights, point4 eye) {

    //TODO: TASK 2
    //Complete lines marked with ???

    // no shading for wireframe
    if (wireframe)
        return;
    
    // First make sure normals are calculated
    if (!normalsCalculated){
        calculateNormals();
        normalsCalculated = true;
    }
    
    //calculate new light values
    // FOR EACH VERTEX
    for (int i=0;i<pointsNum;i++) { 
        color4 ambient, diffuse, specular;
        colors[i] = vec4(0,0,0,1);

        //FOR EACH LIGHT SOURCE
        for (unsigned int li=0;li<lights.size();li++) {
            LightSource& l = *lights[li];

            // 1- ambient term
            // ===============
            // TODO
           // ambient = EDIT_HERE;
            ambient = l.ambient*material.ambientK;

            // ---------------

            // 2- diffuse term
            // ===============
            // 2-A  calculate normal component of light ray
            // Kd = dot product of normals[i] and L vector (use
            // getDirectionfromPoint method in light source l) and dot() method

            //TODO
           // float Kd = EDIT_HERE error here
            float Kd = dot(normals[i] , l.getDirectionFromPoint(normals[i])); 

            // 2-B  lightDiffuse * material diffuseCoff
            // TODO
            color4 diffuse_product = l.diffuse * material.diffuseK ;

            // 2-C shininess and check if light is coming from the front or the
            // back face (back faces are not lighted)

            if (Kd < 0)
                diffuse = vec4(0.0,0.0,0.0,1.0);
            else
                diffuse = Kd * diffuse_product;

            // ---------------
            // 2- specular term
            // ===============
            // calculate halfaway vector
            vec4 e = normalize(eye  - points[i]);
            vec4 h = normalize(l.getDirectionFromPoint(points[i]) + e);
            // calculate dot product of halfaway vector and normal 
            // (approx of reflection vector)
            // TODO:
            // KS = dot product of halfaway vector (h) and normal at vertex i
            //float Ks = EDIT_HERE;
            float Ks = dot(h,normals[i]);


            // specular_product = lightSpecular * material SpecularK
            //color4 specular_product = EDIT_HERE;
            color4 specular_product = l.specular* material.specularK;


            if (Ks < 0)
                specular = color4(0.0,0.0,0.0,1.0);
            else
                specular = specular_product * pow(Ks, material.shininess);
        }

        //final color
        colors[i] += ambient + diffuse + specular;

        //Print(colors[i]);
        //clip
        if (colors[i].x > 1.0) colors[i].x = 1.0;
        if (colors[i].y > 1.0) colors[i].y = 1.0;
        if (colors[i].z > 1.0) colors[i].z = 1.0;

    }

    update();
}

Drawable::~Drawable (){
    // delete vertex array object
    glDeleteVertexArrays(1,&vao);

    // delete buffers
    glDeleteBuffers(1,&vbuffer);
    glDeleteBuffers(1,&cbuffer);

    // disable position and color attrib arays
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // unbind vao and buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
