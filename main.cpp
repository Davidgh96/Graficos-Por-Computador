
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <valarray>
 #include <math.h>
#include <SOIL.h>

void destroyFunc();
void initFunc();
void funReshape(int w, int h);
void funDisplay();
void funKeyboard(unsigned char key, int x, int y);
void funKeyboardSpecial(int key, int x, int y);
void funIdle();
void funMouse(int button, int state, int x, int y);
void funTimer(int ignore);
void funMotion(int x, int y);
void drawLights();

void BrazoRojo();
void BrazoAzul();
void BrazoVerde();
void ArticuacionVerde();
void ArticulacionAzul();
void ejes();
void base();
void dedos();
void dedo();
void mano();
using namespace std;

// Variables globales
int w = 600;
int h = 600;
GLfloat desZ=1.0;
GLfloat rotY=0.0;
GLfloat rotX=0.0;
GLfloat rotXAzul=0.0;
GLfloat  rotMano=0.0;
GLfloat rojo=0.0;
GLfloat newX=0.0;
GLfloat newY=0.0;
GLfloat speed=30;
GLboolean leftbutton=false;
GLfloat zoom=1.0;
GLfloat DL0[] = { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat PL1[] = {-2.0f,0.0f,0.0f, 1.0f };
GLfloat PL2[] = { 2.0f, 0.0f,2.0f, 1.0f };
GLfloat DL2[] = {-2.0f, 0.0f,-2.0f };
int contadorD,contadorP,contadorF=0;
#define NT 4
GLuint  objTexture[NT];


int main(int argc, char** argv) {

 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Sesion 4");
    
 // Inicializamos GLEW
    GLenum err = glewInit();
    if(GLEW_OK != err) printf("Error: %s\n", glewGetErrorString(err));
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    printf("This system supports OpenGL Version: %s\n", oglVersion);
    
 // Inicializaciones especÃ­ficas
    initFunc();
    
 // ConfiguraciÃ³n CallBacks
    glutReshapeFunc(funReshape);
    glutDisplayFunc(funDisplay);
    glutKeyboardFunc(funKeyboard);
    glutMouseFunc(funMouse);
    glutMotionFunc(funMotion);
    glutTimerFunc(speed,funTimer,0);
    glutIdleFunc(funIdle);
    glutSpecialFunc(funKeyboardSpecial);
    
   
    
 // Bucle principal
    glutMainLoop();
     // Destrucción de objetos
    destroyFunc();
    return 0;
}

void initFunc() {
   
 // Test de profundidad
    glEnable(GL_DEPTH_TEST);

     // Modelo de Iluminación
    glEnable(GL_LIGHTING);
    
 // Parámetros de la Luz ambiental global
    GLfloat IA[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, IA);

 // Parámetros de la Luz 0 (direccional=sol)
    GLfloat Ia0[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Id0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat Is0[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT , Ia0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE , Id0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Is0);
    glEnable(GL_LIGHT0);

 // Parámetros de la Luz 1 (posicional=bombilla)
    GLfloat Ia1[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Id1[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat Is1[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT , Ia1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE , Id1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, Is1);
    glLightf (GL_LIGHT1, GL_CONSTANT_ATTENUATION , 0.90f);
    glLightf (GL_LIGHT1, GL_LINEAR_ATTENUATION   , 0.05f);
    glLightf (GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01f);
    glEnable(GL_LIGHT1);

 // Parámetros de la Luz 2 (Spotligth=foco)
    GLfloat Ia2[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Id2[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat Is2[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glLightfv(GL_LIGHT2, GL_AMBIENT , Ia2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE , Id2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, Is2);
    glLightf (GL_LIGHT2, GL_SPOT_EXPONENT, 75.0f);
    glLightf (GL_LIGHT2, GL_SPOT_CUTOFF,   15.0f);
    glEnable(GL_LIGHT2);

 // Modelo de Sombreado
    glShadeModel(GL_SMOOTH);
    
 // Normalizado de coordenadas normales
    glEnable(GL_NORMALIZE);
 
    glGenTextures(NT,objTexture);
    const char *fileName[NT] = {"imgChess.bmp","imgLadrillo.bmp","imgMarmol.bmp","imgEarthSOIL.bmp"};
    for(unsigned i=0; i<NT; i++) {
     // Seleccionamos la textura a configurar
        glBindTexture(GL_TEXTURE_2D, objTexture[i]);
     // Cargamos la textura (SOIL)
        int textureW, textureH;
        unsigned char* texture = SOIL_load_image(fileName[i], &textureW, &textureH, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureW, textureH, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
        glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(texture); 
     // Configuramos la textura
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE/*GL_MODULATE*/);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    // Transparencia
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);   

 

}
void destroyFunc() {
    
    glDeleteTextures(NT,objTexture);
    
}


void funReshape(int wnew, int hnew) {
    
// Configuración del Viewport
    glViewport(0, 0, wnew, hnew);

 // Captura de w y h
    w = wnew;
    h = hnew;
  
    
}

void funDisplay() {
    
 // Borramos el buffer de color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
 // Para configurar la matriz matriz P
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
 // Matriz de ProyecciÃ³n P (CÃ¡mara)
    GLfloat fovy = 60.0f, aspectRatio = (GLfloat)w/(GLfloat)h, nplane = 0.1f, fplane = 20.0f;
    gluPerspective(fovy*zoom,aspectRatio,nplane,fplane);
    
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (CÃ¡mara)
    GLfloat eye[3] = {3.0*sin(newX*M_PI/180.0f), 3.0*sin(newY*M_PI/180.0f), 3.0f};
    GLfloat center[3] = {0.0,  0.0, 0.0};
    GLfloat up[3]     = {0.0,  1.0,  0.0};
   
    gluLookAt(    eye[0],    eye[1],    eye[2],
               center[0], center[1], center[2],
                   up[0],     up[1],     up[2]); 
     drawLights();

 // Dibujamos los objetos (M)
    ejes();
    base();
 // Intercambiamos los buffers
    glutSwapBuffers();
    
}
void drawLights(){
     // Luz 0: Direccional
    glLightfv(GL_LIGHT0, GL_POSITION, DL0);
    
 // Luz 1: Posicional
    glLightfv(GL_LIGHT1, GL_POSITION, PL1);

 // Luz 2: Foco
    glLightfv(GL_LIGHT2, GL_POSITION, PL2);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, DL2);
}
void dedo(){
    // Definimos el material de la esfera
    GLfloat Ka[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Kd[] = { 0.0f, 0.8f, 0.0f, 1.0f };
    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
    
    glPushMatrix();
    glTranslatef(0.0,-0.15+0.02,0.05);
    glutSolidCylinder(0.02,0.15,10,4);
    glPopMatrix();
}
void dedos(){
  
    glRotatef(0.0,0.0,0.0,1.0);dedo();
    glRotatef(90.0,0.0,0.0,1.0);dedo();
    glRotatef(90.0,0.0,0.0,1.0);dedo();
    glRotatef(90.0,0.0,0.0,1.0);dedo();
    
    
}
void mano(){
      // Definimos el material de la esfera
    GLfloat Ka[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Kd[] = { 0.0f, 0.8f, 0.0f, 1.0f };
    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
    
     glutSolidCylinder(0.15,0.05,20,2);
     dedos();
    
}

void BrazoAzul(){

    // Definimos el material de la esfera
    GLfloat Ka[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Kd[] = { 0.0f, 0.8f, 0.0f, 1.0f };
    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
    
    glutSolidCylinder(0.1,1.0,20,10);
    glTranslatef(0.0,0.0,1.0);
    ArticuacionVerde();


}
void BrazoVerde(){

    

    // Definimos el material de la esfera
    GLfloat Ka[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Kd[] = { 0.0f, 0.8f, 0.0f, 1.0f };
    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
    
    glutSolidCylinder(0.075,0.7,20,10);
    
    glTranslatef(0.0,0.0,0.7);
    BrazoRojo();
    

    
}
void BrazoRojo(){
    // Definimos el material de la esfera
    GLfloat Ka[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Kd[] = { 0.0f, 0.8f, 0.0f, 1.0f };
    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
    
   glTranslatef(0.0,0.0,rojo);
   glutSolidCylinder(0.05,0.5,20,10);
   glTranslatef(0.0,0.0,0.5);
   glRotatef(rotMano,0.0,0.0,1.0);
   mano();
    
 
    
}
void ArticuacionVerde(){
    // Definimos el material de la esfera
    GLfloat Ka[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Kd[] = { 0.0f, 0.8f, 0.0f, 1.0f };
    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);

    glRotatef(rotX,1.0,0.0,0.0);
    glutSolidSphere(0.15,20,20);
    BrazoVerde();


}
void ArticulacionAzul(){
    // Definimos el material de la esfera
    GLfloat Ka[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Kd[] = { 0.0f, 0.8f, 0.0f, 1.0f };
    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
    
    glRotatef(rotXAzul,1.0,0.0,0.0);
    glutSolidSphere(0.2,20,20);
    BrazoAzul();


}
void base(){
      glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glBindTexture(GL_TEXTURE_2D, objTexture[1]);
    // Definimos el material de la esfera
    GLfloat Ka[] = { 0.1f, 0.1f, 0.1f, 0.5f };
    GLfloat Kd[] = { 0.0f, 0.8f, 0.0f, 0.5f };
    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 0.5f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
//     glDepthMask(GL_FALSE);
    glRotatef(rotY,0.0,1.0,0.0);
   glPushMatrix(); 
    glTranslatef(0.0,0.2,0.0);
    glRotated(90,1.0,0.0,0.0);
    glutSolidCylinder(0.5,0.2,100,5);   
   glPopMatrix();
//     glDepthMask(GL_TRUE);
    glTranslatef(0.0,0.4,0.0);
    ArticulacionAzul();
     glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_2D);
    
}

void ejes(){
    glPushMatrix(); 
    glEnable (GL_LINE_STIPPLE);
    
        glLineStipple(1,255);
        glLineWidth(2);
        glColor3f(0.5,0.5,0.5);
       
    glBegin(GL_LINES);
    glVertex3i(-10,0,0);
    glVertex3i(10,0,0);
    
    glVertex3i(0,-10,0);
    glVertex3i(0,10,0);
    
    glVertex3i(0,0,-20);
    glVertex3i(0,0,20);
     
    glEnd();
    glLineWidth(1);
    glDisable (GL_LINE_STIPPLE);
    glPopMatrix();
}
void funKeyboard(unsigned char key, int x, int y) {
   
    switch(key) {
        case 'd':
            if(rojo>=-0.5){
                rojo-=0.01f;
            }
                break;
        case 'D':
            if(rojo<=0.0){
                rojo+=0.01f;
            }
            break;        
        case 'r':rotY+=5.0f;break;
        case 'R':rotY-=5.0f;break;
       case 'z':
            if(contadorD % 2==1){
                glEnable(GL_LIGHT0);
            }else{
                glDisable(GL_LIGHT0);
            }
            contadorD++;
            break;
        case 'p':
            if(contadorP % 2==1){
                glEnable(GL_LIGHT1);
            }else{
                glDisable(GL_LIGHT1);
            }
            contadorP++;
            break;
        case 'f':
            if(contadorF % 2==1){
                glEnable(GL_LIGHT2);
            }else{
                glDisable(GL_LIGHT2);
            }
            contadorF++;
            break;
        default:
            ;  
            
     }
    
    
    
    glutPostRedisplay();
        
}
void funKeyboardSpecial(int key, int x, int y){
    switch(key) {

        case GLUT_KEY_UP:
            if(rotXAzul>=-180){
            rotXAzul -= 5.0f;
            }
            break;
        case GLUT_KEY_DOWN:
            if(rotXAzul<=0){
            rotXAzul += 5.0f;
            }
            break;
        case GLUT_KEY_LEFT:
            if(rotX>=-130){
            rotX -= 5.0f;
            }
            break;
        case GLUT_KEY_RIGHT:
            if(rotX<=130){
            rotX += 5.0f;
            }
            break;
        default:
            ;  
            
     }
    
    
    
    glutPostRedisplay();
    
}
void funMouse(int button, int state, int x, int y){
   leftbutton =button == GLUT_LEFT_BUTTON && state ==GLUT_DOWN;
   switch(button){
       case 3: zoom -=zoom >0.5 ?0.05:0.0;break;
       case 4: zoom +=zoom<1.5 ? 0.05 :0.0;break;
   }
   
    
}
void funMotion(int x, int y){
    if(leftbutton){
        newX=(GLfloat)(w/2- x);
        newY =(GLfloat)(y-h/2);
        if(newX>300.0)newX=300.0;
         if(newY>300.0)newY=300.0;
         if(newX<-300.0)newX=-300.0;
         if(newX<-300.0)newY=-300.0;
        newX/=5.0;
        newY/=5.0;
        glutPostRedisplay();
    }
    
}
void funTimer(int ignore){
    rotMano-=5.0;
    glutPostRedisplay();
    glutTimerFunc(speed,funTimer,0);
}
void funIdle() {
   
}