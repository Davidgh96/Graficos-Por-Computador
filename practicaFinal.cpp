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
void funMouse(int button, int state, int x, int y);
void funTimer(int ignore);
void funMotion(int x, int y);
void drawLights();

void Patinete();
void Meta();
void PilaresMeta();
void CartelMeta();
void FocosMeta();
void RuedaTrasera();
void RuedaDelantera();
void Sillin();
void BaseHorizontal();
void BaseVertical();
void Foco();
void ManillarIzquierdo();
void ManillarDerecho();
void Carretera();

using namespace std;

// Variables globales
int w = 900;
int h = 700;

GLfloat desZ=0.0;
GLfloat rotZ=0.0;
GLfloat rotRueda=0.0;
GLfloat newX=1.0;
GLfloat newY=1.0;
GLfloat speed=30;
GLboolean leftbutton=false;
GLfloat zoom=1.0;

GLfloat DL0[] = { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat FL3[] = {0.0f,2.0f,0.0f, 1.0f };
GLfloat FD3[] = {0.0f,1.5f,30.0f};
GLfloat PL4[] = { 0.0f, 5.0f, -8.0f, 1.0f };
// Definimos el material del foco del patinete apagado
GLfloat  KaF[] = { 0.05f,0.05f,0.05f,1.0f};
GLfloat  KdF[] = {0.5f,0.5f,0.5f,1.0f};
GLfloat  KsF[] = {0.7f,0.7f,0.7f,1.0f};

// Definimos el material de los detalles de la meta
GLfloat  KaM[] = { 0.05f,0.05f,0.05f,1.0f};
GLfloat  KdM[] = {0.5f,0.5f,0.5f,1.0f};
GLfloat  KsM[] = {0.7f,0.7f,0.7f,1.0f};

int i=2;
int contadorM=0;
int contadorD=0;
int contadorP=0;
int contadorF=0;

#define NT 4
GLuint  objTexture[NT];


int main(int argc, char** argv) {

 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Practica final");
    
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
    GLfloat IA[]  = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, IA);

 // Parámetros de la luz direccional
    GLfloat Ia0[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Id0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat Is0[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT , Ia0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE , Id0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Is0);
    glEnable(GL_LIGHT0);


    //Parámetros de la luz del foco del patinete
    GLfloat Ia3[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Id3[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat Is3[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glLightfv(GL_LIGHT3, GL_AMBIENT , Ia3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE , Id3);
    glLightfv(GL_LIGHT3, GL_SPECULAR, Is3);
    glLightf (GL_LIGHT3, GL_SPOT_EXPONENT, 75.0f);
    glLightf (GL_LIGHT3, GL_SPOT_CUTOFF,   100.0f);
    glEnable(GL_LIGHT3);
    
    // Parámetros de la luz posicional , situada sobre la meta
    GLfloat Ia4[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat Id4[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat Is4[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glLightfv(GL_LIGHT4, GL_AMBIENT , Ia4);
    glLightfv(GL_LIGHT4, GL_DIFFUSE , Id4);
    glLightfv(GL_LIGHT4, GL_SPECULAR, Is4);
    glLightf (GL_LIGHT4, GL_CONSTANT_ATTENUATION , 0.90f);
    glLightf (GL_LIGHT4, GL_LINEAR_ATTENUATION   , 0.05f);
    glLightf (GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.01f);
    glEnable(GL_LIGHT4);


 // Modelo de Sombreado
    glShadeModel(GL_SMOOTH);
    
 // Normalizado de coordenadas normales
    glEnable(GL_NORMALIZE);
 
    glGenTextures(NT,objTexture);
    const char *fileName[NT] = {"carretera.bmp","ruedas.jpg","imgChess.bmp","winner.jpg"};
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
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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
    
 // Matriz de Proyeccion P (Camara)
    GLfloat fovy = 60.0f, aspectRatio = (GLfloat)w/(GLfloat)h, nplane = 0.1f, fplane = 20.0f;
    gluPerspective(fovy*zoom,aspectRatio,nplane,fplane);
    
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (Camara)
    GLfloat eye[3] = {3.0f*(GLfloat)cos(newY*M_PI/180.0f)*(GLfloat)sin(newX*M_PI/180.0f),3.0f*(GLfloat)sin(newY*M_PI/180.0f),3.0f*(GLfloat)cos(newY*M_PI/180.0f)*(GLfloat)cos(newX*M_PI/180.0f)};
    GLfloat center[3] = {0.0,  0.0, 0.0};
    GLfloat up[3]     = {0.0,  1.0,  0.0};
   
    gluLookAt(    eye[0],    eye[1],    eye[2],
               center[0], center[1], center[2],
                   up[0],     up[1],     up[2]); 
    
// Dibujamos los objetos (M)     
 drawLights();
 Meta();
 Patinete();

 Carretera();
 // Intercambiamos los buffers
    glutSwapBuffers();
    
}

void drawLights(){
    
     // Luz 0: Direccional
    glLightfv(GL_LIGHT0, GL_POSITION, DL0);
    
    // Luz 4: Posicional
    glLightfv(GL_LIGHT4, GL_POSITION, PL4);
    
    // Luz 3: Focal
    glPushMatrix();
        glTranslatef(0.0,0.0,desZ);
        glLightfv(GL_LIGHT3, GL_POSITION, FL3);
    glPopMatrix();
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, FD3);
 
}
void Meta(){
    
    PilaresMeta();
    
}
void Patinete(){
    
    glPushMatrix();
        glTranslatef(0.0,0.0,desZ);
        glRotated(rotZ,0.0,0.0,1.0);
        ManillarIzquierdo();
    glPopMatrix();
    
}
void PilaresMeta(){
    
    // Definimos el material de la esfera
    GLfloat Ka[] = { 0.19225f, 0.19225f, 0.19225f, 1.0f };
    GLfloat Kd[] = { 0.50754f, 0.50754f, 0.50754f, 1.0f  };
    GLfloat Ks[] = { 0.508273f, 0.508273f, 0.508273f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 10.2f);
      
    // Dibujamos ambos pilares y los desplazamos al lugar correcto
     glPushMatrix();
        glTranslatef(1.6,0.001,-10);
        glRotatef(-90,1.0,0.0,0.0);   
        glutSolidCylinder(0.4,5.0,50,50);
     glPopMatrix();
     glPushMatrix();
        glTranslatef(-1.6,0.001,-10);
        glRotatef(-90,1.0,0.0,0.0);   
        glutSolidCylinder(0.4,5.0,50,50);
     glPopMatrix();
 
     //Llamamos a los demas elementos de la meta
    FocosMeta();
    CartelMeta();
    
}
void FocosMeta(){
    
    glMaterialfv(GL_FRONT, GL_AMBIENT  , KaM);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , KdM);
    glMaterialfv(GL_FRONT, GL_SPECULAR , KsM);
    glMaterialf (GL_FRONT, GL_SHININESS, 32.0f);
    
    //Creamos los dos focos de la meta y los situamos en su lugar correspondiente, en cada uno de los pilares
    glPushMatrix();
        glTranslatef(1.5,4.0,-9.5);   
        glutSolidCylinder(0.3,0.3,50,50);
        glPopMatrix();
    glPushMatrix();
        glTranslatef(-1.5,4.0,-9.5);   
        glutSolidCylinder(0.3,0.3,50,50);
    glPopMatrix();
    
}
void CartelMeta(){
    
    GLfloat Ka[] = {0.05f,0.05f,0.05f,1.0f};
    GLfloat Kd[] = {0.5f,0.5f,0.5f,1.0f};
    GLfloat Ks[] = {0.7f,0.7f,0.7f,1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 10.0f);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, objTexture[i]);//con la variable i decidiremos la textura del cartel mas abajo
    glBegin(GL_QUADS);
    glNormal3f( 0.0f,  0.0f,  1.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.8f, 4.5f, -10.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.8f, 4.5f, -10.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.8f,  3.0f, -10.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.8f,  3.0f, -10.0f);

    glEnd();
    glDisable(GL_TEXTURE_2D);
       
}
void BaseHorizontal(){
    
    GLfloat Ka[] = { 0.2125f, 0.1275f, 0.054f, 1.0f };
    GLfloat Kd[] = {0.714f, 0.4284f, 0.18144f, 1.0f };
    GLfloat Ks[] = { 0.393548f, 0.271906f, 0.166721f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS,  25.6f);
    
    //Dibujamos la base vertical del patinete
    glutSolidCylinder(0.4,2.0,50,50);
    
    Sillin();
    
}

void BaseVertical(){
    
      
    GLfloat Ka[] = { 0.2125f, 0.1275f, 0.054f, 1.0f };
    GLfloat Kd[] = {0.714f, 0.4284f, 0.18144f, 1.0f };
    GLfloat Ks[] = { 0.393548f, 0.271906f, 0.166721f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS,  25.6f);
    
    glTranslatef(0.0,0.5,0.0);
    //Dibujamos la base vertical y la colocamos en sitio, perpendicular a la base horizontal
    glPushMatrix();
        glTranslatef(0.0,-0.2,0.3);
        glRotatef(-90,1.0,0.0,0.0);   
        glutSolidCylinder(0.25,2.0,50,50);
    glPopMatrix();
    
     BaseHorizontal();
     Foco();
     
}

void RuedaTrasera(){

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glBindTexture(GL_TEXTURE_2D, objTexture[1]);
    //Dibujamos la rueda trasera con su textura y la colocamos en su lugar
    glPushMatrix();
        glTranslatef(0.0,0.0,1.65);
        glRotatef(rotRueda,1.0,0.0,0.0);
        glRotatef(90,0.0,1.0,0.0);
        glutSolidTorus(0.1,0.25,50,50);
    glPopMatrix();
    
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_2D);
    
    BaseVertical();
   
}
void RuedaDelantera(){

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glBindTexture(GL_TEXTURE_2D, objTexture[1]);
    //Dibujamos la rueda delantera con su textura y la colocamos en su lugar
    glPushMatrix();
        glTranslatef(0.0,0.0,0.35);
        glRotatef(rotRueda,1.0,0.0,0.0);
        glRotatef(90,0.0,1.0,0.0);    
        glutSolidTorus(0.1,0.25,50,50);  
    glPopMatrix();
    
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_2D);
    
    RuedaTrasera();
    
}
void ManillarDerecho(){
    
    GLfloat Ka[] = {0.05f,0.05f,0.05f,1.0f};
    GLfloat Kd[] = {0.5f,0.5f,0.5f,1.0f};
    GLfloat Ks[] = {0.7f,0.7f,0.7f,1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 10.0f);
    //dibujamos el manillar derecho y lo situamos en su sitio, con su material correcto
    glPushMatrix();
        glTranslatef(0.0,2.0,0.3);
        glRotatef(90,0.0,1.0,0.0);
        glutSolidCylinder(0.1,0.6,50,50);
    glPopMatrix();
    
    RuedaDelantera();
    
}
void ManillarIzquierdo(){
  
    GLfloat Ka[] = {0.05f,0.05f,0.05f,1.0f};
    GLfloat Kd[] = {0.5f,0.5f,0.5f,1.0f};
    GLfloat Ks[] = {0.7f,0.7f,0.7f,1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 10.0f);
    
    glTranslatef(0.0,0.36,0);
    //dibujamos el manillar izquierdo y lo situamos en su sitio, con su material correcto
    glPushMatrix();
        glTranslatef(0.0,2.0,0.3);
        glRotatef(-90,0.0,1.0,0.0);
        glutSolidCylinder(0.1,0.6,50,50);
    glPopMatrix();
    
    ManillarDerecho();
    

}
void Sillin(){
  
    GLfloat Ka[] = { 0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat Kd[] = {0.01f, 0.01f, 0.01f, 1.0f};
    GLfloat Ks[] = {0.50f, 0.50f, 0.50f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 32.0f);
    //Dibujamos el sillin en su sitio
    glPushMatrix();
        glTranslatef(0.0,0.5,1.6);
        glRotatef(90,1.0,0.0,0.0);
        glutSolidCylinder(0.3,0.3,50,50);
    glPopMatrix();
    
}
void Foco(){
  
    glMaterialfv(GL_FRONT, GL_AMBIENT  , KaF);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , KdF);
    glMaterialfv(GL_FRONT, GL_SPECULAR , KsF);
    glMaterialf (GL_FRONT, GL_SHININESS, 32.0f);
    //Dibujamos el foco del patinete, con su material dependiendo si esta encendido o apagado
    glPushMatrix();   
        glTranslatef(0.0,1.2,0.0);   
        glutSolidCylinder(0.2,0.3,50,50);
    glPopMatrix();   

}
void Carretera(){
    
    //Le incluimos en el material una transparencia del 50% 
    GLfloat Ka[] = {0.25f, 0.25f, 0.25f, 0.5f  };
    GLfloat Kd[] = {0.4f, 0.4f, 0.4f, 0.5f};
    GLfloat Ks[] = { 0.774597f, 0.774597f, 0.774597f, 0.5f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS,76.8f);
    
    //Para dibujar la carretera correctamente, la dibujamos por sectores y unimos esos sectores
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, objTexture[0]);
    glPushMatrix();
        glBegin(GL_QUADS);
            glNormal3f( 0.0f,  0.0f,  1.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 0.0f, -16.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, 0.0f, -16.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f,  0.0f, -12.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  0.0f, -12.0f);
            
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 0.0f, -12.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, 0.0f, -12.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f,  0.0f, -8.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  0.0f, -8.0f);
            
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 0.0f, -8.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, 0.0f, -8.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f,  0.0f, -4.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  0.0f, -4.0f);
            
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 0.0f, -4.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, 0.0f, -4.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f,  0.0f, 0.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  0.0f, 0.0f);
            
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 0.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, 0.0f, 0.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f,  0.0f, 4.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  0.0f, 4.0f);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
}


void funKeyboard(unsigned char key, int x, int y) {
   
    switch(key) {
 
       case 'l':
           //Apagado y encendido de la luz posicional
            if(contadorD % 2==1){
                glEnable(GL_LIGHT0);
            }else{
                glDisable(GL_LIGHT0);
            }
            contadorD++;
            break;
        case 'm':
            //Cambio de material de los focos de los pilares
            if(contadorM % 2==1){             
                KaM[0]=0.05f;
                KaM[1]=0.05f;
                KaM[2]=0.05f;
                KdM[0]=0.5f;
                KdM[1]=0.5f;
                KdM[2]=0.5f;
                KsM[0]=0.7f;
                KsM[1]=0.7f;
                KsM[2]=0.7f ;       
                 
            }else{
                KaM[0]=0.0f;
                KaM[1]=0.0f;
                KaM[2]=0.0f;
                KdM[0]=0.01f;
                KdM[1]=0.01f;
                KdM[2]=0.01f;
                KsM[0]=0.5f;
                KsM[1]=0.5f;
                KsM[2]=0.5f ;  
               
            }
            contadorM++;
            
            break;
        case 'p':
            //Apagado y encendido de la luz posicional
            if(contadorP % 2==1){
                glEnable(GL_LIGHT4);
            }else{
                glDisable(GL_LIGHT4);
            }
            contadorP++;
            break;
         case 'f':
            //Apagado y encendido de los focos, ademas de su material
            if(contadorF % 2==1){
                glEnable(GL_LIGHT3);               
                KaF[0]=0.05f;
                KaF[1]=0.05f;
                KaF[2]=0.05f;
                KdF[0]=0.5f;
                KdF[1]=0.5f;
                KdF[2]=0.5f;
                KsF[0]=0.7f;
                KsF[1]=0.7f;
                KsF[2]=0.7f ;       
                 
            }else{
                glDisable(GL_LIGHT3);
                KaF[0]=0.0f;
                KaF[1]=0.0f;
                KaF[2]=0.0f;
                KdF[0]=0.01f;
                KdF[1]=0.01f;
                KdF[2]=0.01f;
                KsF[0]=0.5f;
                KsF[1]=0.5f;
                KsF[2]=0.5f ;  
               
            }
            contadorF++;  
        default:
            ;  
            
     }
    glutPostRedisplay();
        
}
void funKeyboardSpecial(int key, int x, int y){
    switch(key) {
        case GLUT_KEY_UP:
            //Limitamos el movimiento hacia delante
            if(desZ>-15){               
                desZ -= 0.1f;
                //Si cruza la linea de meta, cambiamos la textura del cartel
                if (desZ<=-10){
                    i=3;
                }
            }
            
            break;
        case GLUT_KEY_DOWN:
             //Limitamos el movimiento hacia atras
            if(desZ<4){
                desZ += 0.1f;
                //Si esta por detras de la linea de meta, cambiamos la textura del cartel
                if(desZ>-10){
                    i=2;
                }
            }
            break;
        case GLUT_KEY_LEFT:
            //Inclinacion del patinete hacia la izquierda
            if(rotZ<=10){
                rotZ+=5.0f;
            }
            break;
        case GLUT_KEY_RIGHT:
            //Inclinacion del patinete hacia la derecha
            if(rotZ>=-10){
                rotZ -= 5.0f;
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
       //zoom de la camara
       case 3: zoom -=zoom >1.5 ?0.05:0.0;break;
       case 4: zoom +=zoom<2.5 ? 0.05 :0.0;break;
   }
       
}
void funMotion(int x, int y){
    
    //calculo de la posicion de la camara
    if(leftbutton){
        newX=(GLfloat)(w/2- x);
        newY =(GLfloat)(y-h/2);
        newX/=5.0;
        newY/=5.0;
        glutPostRedisplay();
    }
    
}
void funTimer(int ignore){
    
    //Rotacion automatica de las ruedas
    rotRueda-=5.0;
    glutPostRedisplay();
    glutTimerFunc(speed,funTimer,0);
    
}

    
    




 







