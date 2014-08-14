#ifndef __LINE_H__
#define __LINE_H__

#include "drawable.h"

class Line : public Drawable {
    public:

        //constructors
        Line(vec4 s,vec4 e,color4 color);
        Line(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,color4 color);

        Line(GLfloat x1, GLfloat y1, GLfloat z1,
                GLfloat x2, GLfloat y2, GLfloat z2, color4 color);

        //methods
        void render();

        //destructor
        ~Line();
};

#endif
