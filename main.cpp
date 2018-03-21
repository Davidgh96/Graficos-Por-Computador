#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>

void initFunc();
void funReshape(int w, int h);
void funDisplay();
void drawCube();
void funKeyboard(int key, int x, int y);

using namespace std;

// Variables globales
int w = 500;
int h = 500;
GLfloat desZ = -5.0f;
GLfloat rotY =  0.0f;

int main(int argc, char** argv) {

 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Sesion 5");
    
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
    
    return 0;
}

void initFunc() {
   
 // Test de profundidad
    glEnable(GL_DEPTH_TEST);

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
    GLfloat fovy = 50.0f, aspectRatio = (GLfloat)w/(GLfloat)h, nplane = 1.0f, fplane = 20.0f;
    gluPerspective(fovy,aspectRatio,nplane,fplane);
    
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (Cámara)
    GLfloat eye[3]    = {0.0,  2.0,  0.0};
    GLfloat center[3] = {0.0,  0.0, -5.0};
    GLfloat up[3]     = {0.0,  1.0,  0.0};
    gluLookAt(    eye[0],    eye[1],    eye[2],
               center[0], center[1], center[2],
                   up[0],     up[1],     up[2]);

 // Dibujamos los objetos (M)
    glTranslatef(0.0f, 0.0f, desZ);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    drawCube();
    
 // Intercambiamos los buffers
    glutSwapBuffers();
    
}

void drawCube() {
    
 // Definimos el material del cubo
    GLfloat Ka[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat Kd[] = { 0.8f, 0.8f, 0.0f, 1.0f };
    GLfloat Ks[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
        
 // Definimos el cubo
    glBegin(GL_QUADS);
     // CARA DERECHA (x = 1)
        glVertex3f( 1.0f, -1.0f,  1.0f); 
        glVertex3f( 1.0f, -1.0f, -1.0f);   
        glVertex3f( 1.0f,  1.0f, -1.0f);    
        glVertex3f( 1.0f,  1.0f,  1.0f);   
     // CARA IZQUIERDA (x = -1)
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
     // CARA SUPERIOR (y = 1)
        glVertex3f( 1.0f,  1.0f,  1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f); 
        glVertex3f(-1.0f,  1.0f,  1.0f);
     // CARA INFERIOR (y = -1)
        glVertex3f( 1.0f, -1.0f,  1.0f);    
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);    
        glVertex3f( 1.0f, -1.0f, -1.0f);
     // CARA DELANTERA (z = 1)
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);
     // CARA TRASERA (z = -1)
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);  
        glVertex3f( 1.0f, -1.0f, -1.0f);
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