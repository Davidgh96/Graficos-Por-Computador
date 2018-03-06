/*
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <valarray>

void initFunc();
void funReshape(int w, int h);
void funDisplay();
void funKeyboard(int key, int x, int y);
void funIdle();
void funMouse(int button, int state, int x, int y);


void BrazoRojo();
void BrazoAzul();
void BrazoVerde();
void ArticuacionVerde();
void ArticulacionAzul();
void ejes();
void base();
using namespace std;

// Variables globales
int w = 600;
int h = 600;
GLfloat desZ=1.0;
GLfloat rotY=0.0;


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
    //glutKeyboardFunc(funKeyboard);
    glutMouseFunc(funMouse);
    glutIdleFunc(funIdle);
    glutSpecialFunc(funKeyboard);
   
    
 // Bucle principal
    glutMainLoop();
    
    return 0;
}

void initFunc() {
   
 // Test de profundidad
    glEnable(GL_DEPTH_TEST);
    glPolygonOffset(1.0,1.0);
    glEnable(GL_POLYGON_OFFSET_FILL);
 // Modelo de sombreado
    glShadeModel(GL_FLAT);
       
 // Modo de rasterizado de las caras
//    glPolygonMode(GL_FRONT,GL_FILL);
//    glPolygonMode(GL_BACK,GL_LINE); 
//     glEnable(GL_FOG);    
//    glFogi(GL_FOG_MODE,GL_LINEAR);
//    glFogf(GL_FOG_START, 10.0);
//   glFogf(GL_FOG_END  , 20.0);
//   GLfloat colorNiebla[4] = {0.0, 0.0, 0.0, 1.0};
//    glFogfv(GL_FOG_COLOR, colorNiebla);
 

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
    gluPerspective(fovy,aspectRatio,nplane,fplane);
    
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (CÃ¡mara)
    GLfloat eye[3]    = {-3.0,  2.0,  3.0};
    GLfloat center[3] = {0.0,  0.0, 0.0};
    GLfloat up[3]     = {0.0,  1.0,  0.0};
    gluLookAt(    eye[0],    eye[1],    eye[2],
               center[0], center[1], center[2],
                   up[0],     up[1],     up[2]); 

 // Dibujamos los objetos (M)
    ejes();
    
    glTranslatef(0.0f, 0.0f, desZ);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);  
    
    base();


   
 
  
    
    
   
    
 // Intercambiamos los buffers
    glutSwapBuffers();
    
}
void BrazoAzul(){

    glColor3f(1.0, 1.0, 1.0);
    glutWireCylinder(0.1,1.0,20,10);
    glColor3f(0.0, 0.0, 1.0);
    glutSolidCylinder(0.1,1.0,20,10);
    glTranslatef(0.0,0.0,1.0);
    ArticuacionVerde();


}
void BrazoVerde(){

    

    glColor3f(1.0, 1.0, 1.0);
    glutWireCylinder(0.075,0.7,20,10);
    glColor3f(0.0, 1.0, 0.0);
    glutSolidCylinder(0.075,0.7,20,10);
    
    glTranslatef(0.0,0.0,0.7);
    BrazoRojo();
    

    
}
void BrazoRojo(){
 
   glColor3f(1.0, 1.0, 1.0);
   glutWireCylinder(0.05,0.5,20,10);
   glColor3f(1.0, 0.0, 0.0);
   glutSolidCylinder(0.05,0.5,20,10);

    
 
    
}
void ArticuacionVerde(){

     glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(0.15,20,20);
    glColor3f(0.0, 1.0, 0.0);
    glutSolidSphere(0.15,20,20);
    BrazoVerde();


}
void ArticulacionAzul(){
    

    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(0.2,20,20);
    glColor3f(0.0, 0.0, 1.0);
    glutSolidSphere(0.2,20,20);
    BrazoAzul();


}
void base(){
   glPushMatrix(); 
    glTranslatef(0.0,0.2,0.0);
    glRotated(90,1.0,0.0,0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutWireCylinder(0.5,0.2,100,5);   
    glColor3f(0.5, 0.5, 0.5);
    glutSolidCylinder(0.5,0.2,100,5);   
   glPopMatrix();
    
    glTranslatef(0.0,0.4,0.0);
    ArticulacionAzul();
    
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
void funKeyboard(int key, int x, int y) {
   
    switch(key) {
//        case 'r': colorPuntos[0] = 1.0f; colorPuntos[1] = 0.0f; colorPuntos[2] = 0.0f; break;
//        case 'g': colorPuntos[0] = 0.0f; colorPuntos[1] = 1.0f; colorPuntos[2] = 0.0f; break;
//        case 'b': colorPuntos[0] = 0.0f; colorPuntos[1] = 0.0f; colorPuntos[2] = 1.0f; break;
//        case '+':escalado+=0.1f;break;
//        case '-':escalado-=0.1f;break;
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
            ;  
//            rotY =  0.0f;
     }
    
    
    
    glutPostRedisplay();
        
}
void funMouse(int button, int state, int x, int y){
//    if (button==GLUT_RIGHT_BUTTON){
//        escalado+=0.1f;
//    }
//        else if(button==GLUT_LEFT_BUTTON){
//         escalado-=0.1f;   
//        }   
    
}

void funIdle() {
//    Sleep(50);
//    if(fovy<100){
//     fovy +=1.0f;
//    }
//    if(dibujar) {
//        glPointSize(10);
//        dibujar = false;
//    }
//    else {
//        glPointSize(50);
//        dibujar = true;  
//    }
//    
//    Sleep(450);
//    
//    glutPostRedisplay();
    
}

 */

