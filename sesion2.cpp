/*
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>

void initFunc();
void funReshape(int w, int h);
void funDisplay();
void drawTriangulo();
void drawPuntos();
void funKeyboard(unsigned char key, int x, int y);
void funIdle();
void drawCubo();
void funMouse(int button, int state, int x, int y);

using namespace std;

// Variables globales
int w = 500;
int h = 500;
GLfloat colorPuntos[] = { 1.0f, 1.0f, 1.0f };
bool dibujar = true;
GLfloat escalado=1.0f;
GLfloat fovy = 50.0f;

int main(int argc, char** argv) {

 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Sesion 2");
    
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
    glutKeyboardFunc(funKeyboard);
    glutMouseFunc(funMouse);
    glutIdleFunc(funIdle);
    glFlush();
 // Bucle principal
    glutMainLoop();
    
    return 0;
}

void initFunc() {

 // Estado inicial
    glPointSize(10);
    
 // Test de profundidad
    glEnable(GL_DEPTH_TEST);
    
 // Modelo de sombreado
    glShadeModel(GL_FLAT);
    //glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
    GLfloat aspectRatio = (GLfloat)w/(GLfloat)h;    
    GLfloat  nplane = 0.1f, fplane = 20.0f;
    gluPerspective(fovy,aspectRatio,nplane,fplane);
    
 // Dibujamos un triángulo
 
    drawTriangulo();
       
 // Dibujamos dos puntos
    drawPuntos();
//Dibujamos el cubo
    glScalef(escalado,escalado,1);
    drawCubo();
 // Intercambiamos los buffers
   
    glutSwapBuffers();
    
}

void drawTriangulo() {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glLineWidth(3.0);
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, -2.0f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f( 0.5, -0.5, -2.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f( 0.0f,  0.5f, -2.0f);
    glEnd();

}
void drawCubo(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    
     
    glBegin(GL_QUADS);
    
        glColor3f(1.0f, 1.0f, 1.0f);      
        glVertex3f(-1.0f, 1.0f, -6.0f);
        
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f( 1.0, 1.0, -6.0f);
        
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f( 1.0f,  1.0f, -4.0f);
       
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f( -1.0f,  1.0f, -4.0f);
       
        
         glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, 1.0f, -4.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f( 1.0, 1.0, -4.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f( 1.0f,  -1.0f, -4.0f);       
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f( -1.0f,  -1.0f, -4.0f);
        
         glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, 1.0f, -6.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f( 1.0f, 1.0f, -6.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f( 1.0f,  -1.0f, -6.0f);       
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f( -1.0f,  -1.0f, -6.0f);
        
         glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, -6.0f);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f( 1.0, -1.0, -6.0f);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f( 1.0f,  -1.0f, -4.0f);       
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f( -1.0f,  -1.0f, -4.0f);
        
         glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, -4.0f);
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f( 1.0, 1.0, -6.0f);
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f( 1.0f,  -1.0f, -6.0f);       
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f( 1.0f,  -1.0f, -4.0f);
        
     glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, 1.0f, -4.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f( -1.0, 1.0, -6.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f( -1.0f,  -1.0f, -6.0f);       
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f( -1.0f,  -1.0f, -4.0f);
        
    glEnd();
    
    
}
void drawPuntos() {
   
   
    glColor3fv(colorPuntos);
    glBegin(GL_POINTS);
        glVertex3f( 0.0f, 0.0f, -3.0f);
        glVertex3f( 0.5f, 0.5f, -3.0f);
    glEnd();
    
}

void funKeyboard(unsigned char key, int x, int y) {
   
    switch(key) {
        case 'r': colorPuntos[0] = 1.0f; colorPuntos[1] = 0.0f; colorPuntos[2] = 0.0f; break;
        case 'g': colorPuntos[0] = 0.0f; colorPuntos[1] = 1.0f; colorPuntos[2] = 0.0f; break;
        case 'b': colorPuntos[0] = 0.0f; colorPuntos[1] = 0.0f; colorPuntos[2] = 1.0f; break;
        case '+':escalado+=0.1f;break;
        case '-':escalado-=0.1f;break;
        default:  colorPuntos[0] = 1.0f; colorPuntos[1] = 1.0f; colorPuntos[2] = 1.0f; break;
    }
    
    glutPostRedisplay();
        
}
void funMouse(int button, int state, int x, int y){
    if (button==GLUT_RIGHT_BUTTON){
        escalado+=0.1f;
    }
        else if(button==GLUT_LEFT_BUTTON){
         escalado-=0.1f;   
        }   
    
}

void funIdle() {
    Sleep(50);
    if(fovy<100){
     fovy +=1.0f;
    }
    if(dibujar) {
        glPointSize(10);
        dibujar = false;
    }
    else {
        glPointSize(50);
        dibujar = true;  
    }
    
    Sleep(450);
    
    glutPostRedisplay();
    
}
 */

