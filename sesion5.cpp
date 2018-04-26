//
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <stdio.h>
//
//void initFunc();
//void funReshape(int w, int h);
//void funDisplay();
//void drawLights();
//void drawEsfera(GLfloat s, GLint c);
//void funKeyboardSpecial(int key, int x, int y);
//void funKeyboard(unsigned char key, int x, int y);
//
//using namespace std;
//
//// Variables globales
//int w = 500;
//int h = 500;
//GLfloat desZ = 0.0f;
//GLfloat rotY =  0.0f;
//GLfloat DL0[] = { 1.0f, 1.0f, 1.0f, 0.0f };
//GLfloat PL1[] = {-2.0f,0.0f,0.0f, 1.0f };
//GLfloat PL2[] = { 2.0f, 0.0f,2.0f, 1.0f };
//GLfloat DL2[] = {-2.0f, 0.0f,-2.0f };
//int contadorD,contadorP,contadorF=0;
//int main(int argc, char** argv) {
//
// // Inicializamos GLUT
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(w,h);
//    glutInitWindowPosition(50,50);
//    glutCreateWindow("Sesion 5");
//    
//  //Inicializamos GLEW
//    GLenum err = glewInit();
//    if(GLEW_OK != err) printf("Error: %s\n", glewGetErrorString(err));
//    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
//    const GLubyte *oglVersion = glGetString(GL_VERSION);
//    printf("This system supports OpenGL Version: %s\n", oglVersion);
//    
// // Inicializaciones específicas
//    initFunc();
//    
// // Configuración CallBacks
//    glutReshapeFunc(funReshape);
//    glutDisplayFunc(funDisplay);
//    glutSpecialFunc(funKeyboardSpecial);
//    glutKeyboardFunc(funKeyboard);
//    
// // Bucle principal
//    glutMainLoop();
//    
//    return 0;
//}
//
//void initFunc() {
//   
//  //Test de profundidad
//    glEnable(GL_DEPTH_TEST);
//
//  //Modelo de Iluminación
//    glEnable(GL_LIGHTING);
//    
//  //Parámetros de la Luz ambiental global
//    GLfloat IA[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, IA);
//
//  //Parámetros de la Luz 0 (direccional=sol)
//    GLfloat Ia0[] = { 0.1f, 0.1f, 0.1f, 1.0f };
//    GLfloat Id0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
//    GLfloat Is0[] = { 0.3f, 0.3f, 0.3f, 1.0f };
//    glLightfv(GL_LIGHT0, GL_AMBIENT , Ia0);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE , Id0);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, Is0);
//    glEnable(GL_LIGHT0);
//
// // Parámetros de la Luz 1 (posicional=bombilla)
//    GLfloat Ia1[] = { 0.1f, 0.1f, 0.1f, 1.0f };
//    GLfloat Id1[] = { 0.9f, 0.9f, 0.9f, 1.0f };
//    GLfloat Is1[] = { 0.8f, 0.8f, 0.8f, 1.0f };
//    glLightfv(GL_LIGHT1, GL_AMBIENT , Ia1);
//    glLightfv(GL_LIGHT1, GL_DIFFUSE , Id1);
//    glLightfv(GL_LIGHT1, GL_SPECULAR, Is1);
//    glLightf (GL_LIGHT1, GL_CONSTANT_ATTENUATION , 0.90f);
//    glLightf (GL_LIGHT1, GL_LINEAR_ATTENUATION   , 0.05f);
//    glLightf (GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01f);
//    glEnable(GL_LIGHT1);
//
//  //Parámetros de la Luz 2 (Spotligth=foco)
//    GLfloat Ia2[] = { 0.1f, 0.1f, 0.1f, 1.0f };
//    GLfloat Id2[] = { 0.7f, 0.7f, 0.7f, 1.0f };
//    GLfloat Is2[] = { 0.9f, 0.9f, 0.9f, 1.0f };
//    glLightfv(GL_LIGHT2, GL_AMBIENT , Ia2);
//    glLightfv(GL_LIGHT2, GL_DIFFUSE , Id2);
//    glLightfv(GL_LIGHT2, GL_SPECULAR, Is2);
//    glLightf (GL_LIGHT2, GL_SPOT_EXPONENT, 75.0f);
//    glLightf (GL_LIGHT2, GL_SPOT_CUTOFF,   15.0f);
//    glEnable(GL_LIGHT2);
//
// // Modelo de Sombreado
//    glShadeModel(GL_SMOOTH);
//    
// // Normalizado de coordenadas normales
//    glEnable(GL_NORMALIZE);
//    
//}
//
//void funReshape(int wnew, int hnew) {
//    
//  //Configuración del Viewport
//    glViewport(0, 0, wnew, hnew);
//
// // Captura de w y h
//    w = wnew;
//    h = hnew;
//    
//}
//
//void funDisplay() {
//    
// // Borramos el buffer de color
//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
// // Para configurar la matriz matriz P
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    
// // Matriz de Proyección P (Cámara)
//    GLfloat fovy = 50.0f, aspectRatio = (GLfloat)w/(GLfloat)h, nplane = 1.0f, fplane = 20.0f;
//    gluPerspective(fovy,aspectRatio,nplane,fplane);
//    
// // Para configurar las matrices M y V
//    glMatrixMode(GL_MODELVIEW);  
//    glLoadIdentity();
//    
// // Matriz de Vista V (Cámara)
//    GLfloat eye[3]    = {0.0,  2.0,  5.0};
//    GLfloat center[3] = {0.0,  0.0, 0.0};
//    GLfloat up[3]     = {0.0,  1.0,  0.0};
//    gluLookAt(    eye[0],    eye[1],    eye[2],
//               center[0], center[1], center[2],
//                   up[0],     up[1],     up[2]);
//
// // Colocamos las luces
//    drawLights();
//    
//  //Dibujamos los objetos (M)
//   // glTranslatef(0.0f, 0.0f, desZ);
//    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
//    glScalef(1.0f,0.5f,1.0f);
//    drawEsfera(1.0f,100);
//    
//  //Intercambiamos los buffers
//    glutSwapBuffers();
//    
//}
//
//void drawLights() {
//    
//  //Luz 0: Direccional
//    glLightfv(GL_LIGHT0, GL_POSITION, DL0);
//    
// // Luz 1: Posicional
//    glLightfv(GL_LIGHT1, GL_POSITION, PL1);
//
//  //Luz 2: Foco
//    glLightfv(GL_LIGHT2, GL_POSITION, PL2);
//    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, DL2);
//
//}
//
//void drawEsfera(GLfloat s, GLint c) {
//    
// // Definimos el material de la esfera
//    GLfloat Ka[] = { 0.1f, 0.1f, 0.1f, 1.0f };
//    GLfloat Kd[] = { 0.0f, 0.8f, 0.0f, 1.0f };
//    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 1.0f };
//    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
//    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
//    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
//    
// // Definimos la esfera
//    glPushMatrix();
//        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
//        glutSolidSphere(s,c,c);   
//    glPopMatrix();
//    
//   //   Definimos el material de la esfera
//    GLfloat KA[] = { 0.1f, 0.1f, 0.1f, 1.0f };
//    GLfloat KD[] = { 0.5f, 0.5f, 0.5f, 1.0f };
//    GLfloat KS[] = { 0.9f, 0.9f, 0.9f, 1.0f };
//    glMaterialfv(GL_FRONT, GL_AMBIENT  , KA);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE  , KD);
//    glMaterialfv(GL_FRONT, GL_SPECULAR , KS);
//    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
//    
// // Definimos la esfera
//    glPushMatrix();
//        glRotatef(rotY,0.0f,1.0f,0.0f);
//        glTranslatef(-2.0f,0.0f,0.0f) ;              
//        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
//        glutSolidSphere(0.25,100,100);   
//    glPopMatrix();
//    
//    
//
//}
//void funKeyboard(unsigned char key, int x, int y){
//    switch(key){
//        case 'd':
//            if(contadorD % 2==1){
//                glEnable(GL_LIGHT0);
//            }else{
//                glDisable(GL_LIGHT0);
//            }
//            contadorD++;
//            break;
//        case 'p':
//            if(contadorP % 2==1){
//                glEnable(GL_LIGHT1);
//            }else{
//                glDisable(GL_LIGHT1);
//            }
//            contadorP++;
//            break;
//        case 'f':
//            if(contadorF % 2==1){
//                glEnable(GL_LIGHT2);
//            }else{
//                glDisable(GL_LIGHT2);
//            }
//            contadorF++;
//            break;
//            
//    }
//    glutPostRedisplay();
//}
//
//void funKeyboardSpecial(int key, int x, int y) {
//    
//    switch(key) {
//        case GLUT_KEY_UP:
//            desZ -= 0.1f;
//            break;
//        case GLUT_KEY_DOWN:
//            desZ += 0.1f;
//            break;
//        case GLUT_KEY_RIGHT:
//            rotY -= 5.0f;
//            break;
//        case GLUT_KEY_LEFT:
//            rotY += 5.0f;
//            break;
//        default:
//            desZ = -5.0f;  
//            rotY =  0.0f;
//    }
//    
//    glutPostRedisplay();
//      
//}
// 
//
