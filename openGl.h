#ifndef openGl
#define openGl

extern int windowWidth;
extern int windowHeight;
extern float cameraAngle;
void initGLUT(int *argc, char** argv);
void initOpenGL(float angle,int w,int h);
void freeVBO();
void freeVAO();
void cleanShaders();
void initGLEW();






#endif