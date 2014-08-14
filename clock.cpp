#include "include/Angel.h"
#include <cmath>
#include <vector>
#include <ctime>

#include "drawable.h"
#include "line.h"
#include "cube.h"
#include "sphere.h"
#include "cylinder.h"



#include "material.h"
#include "light_source.h"

const GLfloat WindowWidth = 600;
const GLfloat WindowHeight = 600;
time_t now = time(0);
GLuint model_view_loc;
GLuint projection_loc;



//some basic colors
color4 blue  = color4(0,0,1,1);
color4 red   = color4(1,0,0,1);
color4 green = color4(0,1,0,1);
color4 black = color4(0,0,0,1);
color4 white = color4(1,1,1,1);
color4 magnita = color4(1,0,1,1);
int refreshMillis = 100; 
int Time = 0 ; 


// Viewing Variables

//default values
float radiusDefault = 300;
GLfloat leftDefault = -400, rightDefault = 400;
GLfloat bottomDefault = -400, topDefault = 400;
GLfloat zNearDefault = 30, zFarDefault = 20000;
float defaultTheta = 0, defaultPhi = 0;


// current variables
float theta = defaultTheta;
float phi = defaultPhi;
float radius = radiusDefault;

enum ViewingMode {
    ORTHO, PERSPECTIVE_WITH_FRUSTUM, PERSPECTIVE_WITH_FOV
} viewMode;

// viewing volume
GLfloat left = leftDefault, right = rightDefault;
GLfloat bottom = bottomDefault, top =  topDefault;
GLfloat zNear = zNearDefault, zFar = zFarDefault;
float zoomFactor = 100;
float fovy = 20; // field of view in angles with respect to y axis

vec4 eye;

std::vector<Drawable*> shapes;
std::vector<LightSource*> lights;
std::vector<Sphere*> Hours;

std::vector<FilledCube*> ClockArms
;

//----------------------------------------------------------------------------

void build_model(){

    //LIGHTS
    // add a single light
    lights.push_back(new LightSource(
                   // vec4(100, 100, 100, 1.0),
                    vec4(0, 200, 100, 1.0),
                    color4(0.5, 0.5, 0.5, 1.0),
                    color4(1.0, 1.0, 1.0, 1.0),
                    color4(1.0, 1.0, 1.0, 1.0)
                ));
    /*
    // Grid
    float gsize = 150;
    for (int i=-gsize;i<=gsize;i+=10) {
        Drawable* line = new Line(vec4(i,-gsize,0,1),vec4(i,gsize,0,1),color3(0.5,0.5,0.5));
        shapes.push_back(line);
        line = new Line(vec4(-gsize,i,0,1),vec4(gsize,i,0,1),color3(0.5,0.5,0.5));
        shapes.push_back(line);
    }
    */

    Drawable* line1 = new Line(vec4(-50,0,0,1),vec4(50,0,0,1),red);
    Drawable* line2 = new Line(vec4(0,-50,0,1),vec4(0,50,0,1),green);
    Drawable* line3 = new Line(vec4(0,0,-50,1),vec4(0,0,50,1),blue);

  //  shapes.push_back(line1);
   // shapes.push_back(line2);
    //shapes.push_back(line3);


    float l = 50;
    //cube has a default material of red plastic
    FilledCube* cube = new FilledCube(vec4(0,0,0,1),l,l,10);

    //change cube material to gold
    cube->material = Material(
            color4(1,1,0,1.0),
            color4(0.75164,0.7,0.22648,1.0),
            color4(0.628281,0.55802,0.266065,1.0),
            32.2f
            );
   // shapes.push_back(cube);
    
    Cylinder* Elbeta3a = new Cylinder(vec4(0,0,0,1),25,10);
    Elbeta3a->material = Material(
            color4(1,1,0,1.0),
            color4(0.75164,0.7,0.22648,1.0),
            color4(0.628281,0.55802,0.266065,1.0),
            32.2f
            );
    shapes.push_back(Elbeta3a);


      Sphere* s0 = new FilledSphere(vec4(0, 20, 6, 1), 2.5, 4);
    Hours.push_back(s0);

      Sphere* s1 = new FilledSphere(vec4(0, 20, 6, 1), 2.5, 4);
    Hours.push_back(s1);
        Sphere* s2 = new FilledSphere(vec4(0, 20, 6, 1), 2.5, 4);
    Hours.push_back(s2);
        Sphere* s3 = new FilledSphere(vec4(0, 20, 6, 1), 2.5, 4);
    Hours.push_back(s3);
        Sphere* s4 = new FilledSphere(vec4(0, 20, 6, 1), 2.5, 4);
    Hours.push_back(s4);
        Sphere* s5 = new FilledSphere(vec4(0, 20, 6, 1), 2.5, 4);
    Hours.push_back(s5);
        Sphere* s6= new FilledSphere(vec4(0, 20, 6, 1), 2.5, 4);
    Hours.push_back(s6);
        Sphere* s7 = new FilledSphere(vec4(0, 20, 6, 1), 2.5, 4);
    Hours.push_back(s7);
        Sphere* s8 = new FilledSphere(vec4(0, 20, 6, 1), 2.5, 4);
    Hours.push_back(s8);
        Sphere* s9 = new FilledSphere(vec4(0, 20, 6, 1), 2.5, 4);
    Hours.push_back(s9);
        Sphere* s10 = new FilledSphere(vec4(0, 20, 6, 1), 2.5, 4);
    Hours.push_back(s10);
        Sphere* s11 = new FilledSphere(vec4(0, 20, 6, 1), 2.5, 4);
    Hours.push_back(s11);

    for (int i = 0; i < 12; ++i)
    {
    double angle = 360- 90 - (i/12.0 * 360 + 0/60.0 * 30) + 90;
    Hours[i]->move(angle);    
}
 






       Sphere* alaram = new FilledSphere(vec4(0, 25, 0, 1), 5, 4);
    shapes.push_back(alaram);
         Sphere* center = new FilledSphere(vec4(0, 0, 6, 1), 2, 4);
    shapes.push_back(center);

 
    FilledCube* seconds = new FilledCube(vec4(0,8,6,1),1,16,0.5);

    //change cube material to gold
    seconds->material = Material(
            color4(1,0,0,1.0),
            color4(0.75164,0.7,0.22648,1.0),
            color4(0.628281,0.55802,0.266065,1.0),
            32.2f
            );
     ClockArms.push_back(seconds); 


           FilledCube* minutes = new FilledCube(vec4(0,7,6.2,1),1,14,0.5);

    //change cube material to gold
    minutes->material = Material(
            color4(0,1,0,1.0),
            color4(0.75164,0.7,0.22648,1.0),
            color4(0.628281,0.55802,0.266065,1.0),
            32.2f
            );
   ClockArms.push_back(minutes); 

              FilledCube* hours = new FilledCube(vec4(0,5,6.4,1),1,10,0.5);

    //change cube material to gold
    hours->material = Material(
            color4(0,0,1,1.0),
            color4(0.75164,0.7,0.22648,1.0),
            color4(0.628281,0.55802,0.266065,1.0),
            32.2f
            );
    ClockArms.push_back(hours); 

      now = time(0);
    tm *ltm = localtime(&now);
     double angleSec = 360 - 90  - ltm->tm_sec/60.0 * 360 + 90;
    //for minutes
    double angleMinute = 360 - 90 - (ltm->tm_min /60.0 * 360 + ltm->tm_sec/60.0 * 6) + 90;
     //for hours
     double angleHour = 360- 90 - (ltm->tm_hour/12.0 * 360 + ltm->tm_min /60.0 * 30) + 90;
        ClockArms[0]->move(angleSec);

        ClockArms[1]->move(angleMinute);
        ClockArms[2]->move(angleHour);


    //   std::cout << "minute : " << ltm->tm_min << " , hour : " << ltm->tm_hour << " , sec , " << ltm->tm_sec << std::endl;


}

//-----------------------------------------------------------


 
void setup_view() {

    //eye and at are points
    eye.x = radius*sin(theta)*cos(phi);
    eye.y = radius*sin(theta)*sin(phi);
    eye.z = radius*cos(theta);
    eye.w = 1.0;

    std::cout << "looking from" << eye << std::endl;
    vec4 at( 0.0, 0.0, 0.0, 1.0 );
    vec4 up( 0.0, 1.0, 0.0, 0.0 );

    mat4 mv;
    mat4 mp;

    mv = LookAt(eye, at ,up);

    float zf = zoomFactor;

    if (viewMode == PERSPECTIVE_WITH_FOV)
        mp = Perspective(fovy, WindowWidth/WindowHeight, zNear, zFar);
    else if (viewMode == PERSPECTIVE_WITH_FRUSTUM)
        mp = Frustum(left/zf, right/zf, bottom/zf, top/zf, zNear, zFar);
    else
        mp = Ortho(left/zf, right/zf, bottom/zf, top/zf, -zNear, -zFar);

    glUniformMatrix4fv(model_view_loc, 1, GL_TRUE, mv);
    glUniformMatrix4fv(projection_loc, 1, GL_TRUE, mp);

    std::cout << "left : " << left << " , right : " << right << std::endl;
    std::cout << "top : " << top << " , bottom : " << bottom << std::endl;
    std::cout << "near : " << zNear << " , far : " << zFar << std::endl;
    std::cout << "theta " << theta << std::endl;
    std::cout << "phi " << phi << std::endl;
    std::cout << "zoom Factor " << zoomFactor << std::endl;
    std::cout << "--------------" << std::endl;
}

void reset_view() {

    radius = radiusDefault;
    if (viewMode == ORTHO){
        radius = 1.0;
        zoomFactor = 1;
    }else if (viewMode == PERSPECTIVE_WITH_FRUSTUM) {
        zoomFactor = 100;
    } else {
        fovy = 60;
    }

    left = leftDefault; right = rightDefault;
    bottom = bottomDefault; top =  topDefault;
    zNear = zNearDefault; zFar = zFarDefault;

}

//-----------------------------------------------------------
void init( void )
{ 
    // Load shaders and use the resulting shader program
    Drawable::shaderProgram = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( Drawable::shaderProgram );

    model_view_loc = glGetUniformLocation( Drawable::shaderProgram, "model_view" );
    projection_loc = glGetUniformLocation( Drawable::shaderProgram, "projection" );

    // enable depth test
    glEnable(GL_DEPTH_TEST);

    build_model();
    viewMode = PERSPECTIVE_WITH_FRUSTUM;
    
    reset_view();
    setup_view();
   
    glClearColor( 0, 0, 0, 1.0 ); // black background
}

//-----------------------------------------------------------

void display( void )
{
   
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    for (unsigned int i=0;i<shapes.size();i++){
        shapes[i]->shade(lights, eye);
        shapes[i]->render();
    }

     for (unsigned int i=0;i<Hours.size();i++){
        Hours[i]->shade(lights, eye);
        Hours[i]->render();
    }
  
    now = time(0);
     tm *ltm = localtime(&now);
     //for sec
     double angleSec = 360 -90- ltm->tm_sec/60.0 * 360 + 90;
    //for minutes
     double angleMinute = 360 -90- (ltm->tm_min /60.0 * 360 + ltm->tm_sec/60.0 * 6) + 90;
     //for hours
      double angleHour = 360 -90- (ltm->tm_hour/12.0 * 360 + ltm->tm_min /60.0 * 30) + 90;
      ClockArms[0]->shade(lights, eye);
         ClockArms[0]->move(angleSec);
        ClockArms[0]->render();

          ClockArms[1]->shade(lights, eye);
        ClockArms[1]->move(angleMinute);
        ClockArms[1]->render();
          ClockArms[2]->shade(lights, eye);
        ClockArms[2]->move(angleHour);
        ClockArms[2]->render();




          //  std::cout << "minute : " << ltm->tm_min << " , hour : " << ltm->tm_hour << " , sec , " << ltm->tm_sec << std::endl;




    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void keyboard( unsigned char key, int x, int y )
{
    float deltaAng = 10/180.0 * M_PI;

    switch( key ) {
        case 033: // Escape Key
        case 'q': case 'Q':
            exit( EXIT_SUCCESS );
            break;

        case 'x': left *= 1.1; right *= 1.1; break;
        case 'X': left *= 0.9; right *= 0.9; break;
        case 'y': bottom *= 1.1; top *= 1.1; break;
        case 'Y': bottom *= 0.9; top *= 0.9; break;
        case 'z': zNear  *= 1.1; zFar *= 1.1; break;
        case 'Z': zNear *= 0.9; zFar *= 0.9; break;
        case 'r': radius *= 1.1; break;
        case 'R': radius *= 0.9; break;

        case 'a': theta += deltaAng; break;
        case 'd': theta -= deltaAng; break;
        case 'w': phi += deltaAng; break;
        case 's': phi -= deltaAng; break;

        case 'p': 
                  viewMode = PERSPECTIVE_WITH_FRUSTUM;
                  reset_view();
                  break;
        case 'P': 
                  viewMode = PERSPECTIVE_WITH_FOV;
                  reset_view();
                  break;
        case 'o':
                  viewMode = ORTHO;
                  reset_view();
                  break;
        case 'f':
                  fovy+=5;
                  break;
        case 'F':
                  fovy-=5;
                  break;
        case 'v':
                  zoomFactor*=1.1;
                  break;
        case 'V':
                  zoomFactor*= 0.9;
                  break;
        case ' ':  // reset values to their defaults
                  reset_view();
    }

    setup_view();
    glutPostRedisplay();
}

//----------------------------------------------------------------------------
void cleanup() {
    //destroy shaders
    glUseProgram(0);
    glDeleteProgram(Drawable::shaderProgram);
    //destroy shapes and its vertices
    for (unsigned int i=0;i<shapes.size();i++){
        delete shapes[i];
    }
}
//----------------------------------------------------------------------------
void Timer(int value) {
glutPostRedisplay(); // Post a paint request to activate display()
glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
Time += refreshMillis;
}


int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA  | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize( WindowWidth, WindowHeight);

    glutCreateWindow( "Alaram Clock" );

    glewInit();

    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutTimerFunc(refreshMillis, Timer, 0); // First timer call immediately
    glutCloseFunc( cleanup );

    glLineWidth(1);
    //glEnable(GL_LINE_SMOOTH);

    glutMainLoop();
    return 0;
}
