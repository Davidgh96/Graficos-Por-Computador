/*
 #include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>

void initFunc();
void funReshape(int w, int h);
void funDisplay();
void drawTriangulo(char color);
void drawMastil();
void funKeyboard(int key, int x, int y);
void funIdle();

using namespace std;

// Variables globales
int w = 500;
int h = 500;
GLfloat desZ = -4.0f;
GLfloat rotY =  0.0f;
GLfloat rotZ =120.0f;

int main(int argc, char** argv) {

 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Sesion 3");
    
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
    glutIdleFunc(funIdle);
    
 // Bucle principal
    glutMainLoop();
    
    return 0;
}

void initFunc() {
   
 // Test de profundidad
    glEnable(GL_DEPTH_TEST);
    
 // Modelo de sombreado
    glShadeModel(GL_FLAT);
    
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
    GLfloat fovy = 50.0f, nplane = 0.1f, fplane = 20.0f;
    gluPerspective(fovy,aspectRatio,nplane,fplane);
    
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (Cámara)
    // Aquí cargaremos la matriz V
    
 // Dibujamos un triángulo
   
       

    glTranslatef( 0.0f, 0.0f, desZ);
  
    
    glRotatef(rotY,0.0f,1.0f,0.0f);
   
    drawMastil();
   
   
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
    drawTriangulo('g');
    
     
  
   
   
    glRotatef(120.0, 0.0f, 0.0f, 1.0f);
    drawTriangulo('b');
   
     
   
    
 // Dibujamos otro triángulo
   
    glRotatef(120.0, 0.0f, 0.0f, 1.0f);
    drawTriangulo('r');
    
    
     
 // Intercambiamos los buffers
    glutSwapBuffers();
    
}

void drawTriangulo(char color) {
    
    switch(color) {
        case 'r':
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        case 'g':
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        case 'b':
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        default:
            glColor3f(1.0f, 1.0f, 1.0f);            
    }
    
    glBegin(GL_TRIANGLES);
        glVertex3f(0.0f, 0.0f, -4.0f);
        glVertex3f( 0.1f, -0.5f,-4.0f);
        glVertex3f(-0.1f,-0.5f,-4.0f);
    glEnd();
    
}
void drawMastil(){
    glColor3f(1.0f,1.0f,1.0f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,-3.99);
    glVertex3f(0.0,-1.5,-3.99);
    
    glEnd();
    
}

void funKeyboard(int key, int x, int y) {
    
    switch(key) {
        case GLUT_KEY_UP:
            desZ -= 0.1f;
            break;
        case GLUT_KEY_DOWN:
            desZ += 0.1f;
            break;
        case GLUT_KEY_RIGHT:
            rotY -= 5.0f;
            break;
        case GLUT_KEY_LEFT:
            rotY += 5.0f;
            break;
        default:
            desZ = -5.0f;  
            rotY =  0.0f;
    }
    
    glutPostRedisplay();
      
}
void funIdle() {
   
    rotZ+=2.0;
    
    Sleep(10);
    
    glutPostRedisplay();
}
 */

