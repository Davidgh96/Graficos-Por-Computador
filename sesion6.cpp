/*
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <SOIL.h>

void initFunc();
void destroyFunc();
void funReshape(int w, int h);
void funDisplay();
void drawLights();
void drawRoom();
void drawObject(GLfloat s, GLint c);
void drawEsfera();
void funKeyboard(int key, int x, int y);

using namespace std;

// Variables globales
int w = 500;
int h = 500;
GLfloat rotX = 0.0f;
GLfloat rotY = 0.0f;
GLfloat DL0[] = { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat PL1[] = {-2.0f, 1.0f,-4.0f, 1.0f };
#define NT 4
GLuint  objTexture[NT];

int main(int argc, char** argv) {

 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Sesion 6");
    
 // Inicializamos GLEW
    GLenum err = glewInit();
    if(GLEW_OK != err) printf("Error: %s\n", glewGetErrorString(err));
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    printf("This system supports OpenGL Version: %s\n", oglVersion);
    
 // Inicializaciones específicas
    initFunc();
    
 // Configuración CallBacks
    glutReshapeFunc(funReshape);
    glutDisplayFunc(funDisplay);
    glutSpecialFunc(funKeyboard);
    
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
    GLfloat IA[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, IA);

 // Parámetros de la Luz 0 (direccional=sol)
    GLfloat Ia0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat Id0[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat Is0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT , Ia0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE , Id0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Is0);
    glEnable(GL_LIGHT0);

 // Parámetros de la Luz 1 (posicional=bombilla)
    GLfloat Ia1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat Id1[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat Is1[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT , Ia1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE , Id1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, Is1);
    glLightf (GL_LIGHT1, GL_CONSTANT_ATTENUATION , 0.90f);
    glLightf (GL_LIGHT1, GL_LINEAR_ATTENUATION   , 0.05f);
    glLightf (GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01f);
    glEnable(GL_LIGHT1);

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
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
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
    
 // Matriz de Proyección P (Cámara)
    GLfloat fovy = 75.0f, aspectRatio = (GLfloat)w/(GLfloat)h, nplane = 1.0f, fplane = 25.0f;
    gluPerspective(fovy,aspectRatio,nplane,fplane);
    
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (Cámara)
    GLfloat eye[3]    = {0.0,  2.0,  0.0};
    GLfloat center[3] = {0.0,  2.0, -5.0};
    GLfloat up[3]     = {0.0,  1.0,  0.0};
    gluLookAt(    eye[0],    eye[1],    eye[2],
               center[0], center[1], center[2],
                   up[0],     up[1],     up[2]);

 // Colocamos las luces
    drawLights();
    
 // Dibujamos los objetos (M)
    drawRoom();
    drawObject(1.0f,200);
     drawEsfera();
 // Intercambiamos los buffers
    glutSwapBuffers();
    
}

void drawLights() {
    
 // Luz 0: Direccional
    glLightfv(GL_LIGHT0, GL_POSITION, DL0);
    
 // Luz 1: Posicional
    glLightfv(GL_LIGHT1, GL_POSITION, PL1);

}

void drawRoom() {
    
 // Definimos el material de la habitación
    GLfloat Ka[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat Kd[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat Ks[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 50.0f);
    
 // Definimos la habitación
    glPushMatrix();
    
        glTranslatef(0.0f,2.5f,-10.f);
        glScalef(5.0f,2.5f,10.0f);
        
        glEnable(GL_TEXTURE_2D);
        
        glBindTexture(GL_TEXTURE_2D, objTexture[0]);
     // SUELO (y = -1)
        glBegin(GL_QUADS);
            glNormal3f( 0.0f,  1.0f,  0.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
            glTexCoord2f(2.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
            glTexCoord2f(2.0f, 4.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
            glTexCoord2f(0.0f, 4.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glEnd();
             // PARED IZQUIERDA (x = -1)
        glBindTexture(GL_TEXTURE_2D, objTexture[1]);
        glBegin(GL_QUADS);
            glNormal3f( 1.0f,  0.0f,  0.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); 
            glTexCoord2f(8.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);   
            glTexCoord2f(8.0f, 2.0f); glVertex3f(-1.0f,  1.0f, -1.0f);    
            glTexCoord2f(0.0f, 2.0f); glVertex3f(-1.0f,  1.0f,  1.0f); 
        glEnd();

     // PARED DEL FONDO (z = -1)
        glBindTexture(GL_TEXTURE_2D, objTexture[1]);
        glBegin(GL_QUADS);
            glNormal3f( 0.0f,  0.0f,  1.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
            glTexCoord2f(4.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
            glTexCoord2f(4.0f, 2.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
            glTexCoord2f(0.0f, 2.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
        glEnd();

     // PARED DERECHA (x = 1)
        glBindTexture(GL_TEXTURE_2D, objTexture[3]);
        glBegin(GL_QUADS);
            glNormal3f(-1.0f,  0.0f,  0.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
            glTexCoord2f(8.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
            glTexCoord2f(8.0f, 2.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
            glTexCoord2f(0.0f, 2.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
        glEnd();

     // TECHO (y = 1)
        glBindTexture(GL_TEXTURE_2D, objTexture[2]);
        glBegin(GL_QUADS);
            glNormal3f( 0.0f, -1.0f,  0.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  
            glTexCoord2f(4.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
            glTexCoord2f(4.0f, 8.0f); glVertex3f( 1.0f,  1.0f,  1.0f);    
            glTexCoord2f(0.0f, 8.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
        glEnd();
    
        glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
    
}
void drawEsfera(){
     // Definimos el material del objeto
    GLfloat Ka[] = { 0.8f, 0.2f, 0.2f, 0.5f };
    GLfloat Kd[] = { 0.7f, 0.2f, 0.2f, 0.5f };
    GLfloat Ks[] = { 0.8f, 0.2f, 0.2f, 0.5f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 50.0f);
    
 // Definimos el objeto
    
  
    glPushMatrix();
        glTranslatef(0.0f, 3.0f, -10.0f);
        glutSolidSphere(1,10,20);
    glPopMatrix();
   

}
void drawObject(GLfloat s, GLint c) {
    
 // Definimos el material del objeto
    GLfloat Ka[] = { 0.2f, 0.2f, 0.2f, 0.5f };
    GLfloat Kd[] = { 0.7f, 0.7f, 0.3f, 0.5f };
    GLfloat Ks[] = { 0.5f, 0.5f, 0.5f, 0.5f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 50.0f);
    
 // Definimos el objeto
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glBindTexture(GL_TEXTURE_2D, objTexture[2]);
//    glDepthMask(GL_FALSE);
    glPushMatrix();
        glTranslatef(0.0f, 2.0f, -5.0f);
        glRotatef(rotX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotY, 0.0f, 1.0f, 0.0f);
        glutSolidTeapot(s);
    glPopMatrix();
//    glDepthMask(GL_TRUE);
        glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_2D);

}

void funKeyboard(int key, int x, int y) {

    switch(key) {
        case GLUT_KEY_UP:
            rotX -= 5.0f;
            break;
        case GLUT_KEY_DOWN:
            rotX += 5.0f;
            break;
        case GLUT_KEY_LEFT:
            rotY -= 5.0f;
            break;
        case GLUT_KEY_RIGHT:
            rotY += 5.0f;
            break;
        default:
            rotX = 0.0f;  
            rotY = 0.0f;
    }    
    glutPostRedisplay();
    
}

 */

