#include "material.h"


Material::Material() {

    //default is red plastic diffuse materials
    // Ar   Ag     Ab   Dr    Dg    Db     Sr    Sg   Sb    shine
    //0.0 | 0.0 | 0.0 | 0.5 | 0.0 | 0.0 | 0.7 | 0.6 | 0.6 | 32
    ambientK  = vec4(0.2,0.0,0.0,1);
    diffuseK  = vec4(0.5,0,0,1);
    specularK = vec4(0.7,0.6,0.6,1);
    shininess = 32.0f;
}

Material::Material(color4 ambientK, color4 diffuseK, color4 specularK,
         float shininess) {
    this->ambientK = ambientK;
    this->diffuseK = diffuseK;
    this->specularK = specularK;
    this->shininess = shininess;
}
