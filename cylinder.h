#ifndef __CYLINDER_H__
#define __CYLINDER_H__

#include "drawable.h"
#include <vector>

class Cylinder : public Drawable {
    public:
        //constructors
        Cylinder(vec4 center, float radius, float height);

        //methods
        virtual void render();
        virtual void calculateNormals();

        //destructor
        ~Cylinder();
};



#endif
