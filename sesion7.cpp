/*
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <SOIL.h>
#include <vector>

void initFunc();
void destroyFunc();
void funReshape(int w, int h);
void funDisplay();
void drawLights();
void drawObject(GLfloat s, GLint c);
void myVbo();
void funKeyboard(int key, int x, int y);
void funIdle();

using namespace std;

typedef struct {
    vector<GLfloat>  vCoords;
    vector<GLfloat>  nCoords;
    vector<GLfloat>  tCoords;
    vector<GLushort> iCoords;
} Tmesh;
Tmesh loadMesh(const char* filename);

// Variables globales
   // Viewport
      int w = 500;
      int h = 500;
   // Animaciones
      GLfloat rotX = 0.0f;
      GLfloat rotY = 0.0f;
   // Luces
      GLfloat DL0[] = { 1.0f, 1.0f, 1.0f, 0.0f };
      GLfloat PL1[] = {-2.0f, 1.0f,-4.0f, 1.0f };
   // Texturas
      #define NT 1
      GLuint  objTexture[NT];
   // Mallas
      #define NB 4
      GLuint  VBO[NB];
      GLsizei meshSize;
        
int main(int argc, char** argv) {

 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Sesion 7");
    
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
    
 // Texturas
    glGenTextures(NT,objTexture);
    const char *fileName[NT] = {"common/img/imgEarthSOIL.bmp"};
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
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

 // Transparencia
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
 // VBO's para almacenar los objetos una vez creados y dejarlos en la GPU
    Tmesh mesh = loadMesh("monkeyTexture.obj");
    meshSize = mesh.iCoords.size();
    glGenBuffers(NB,VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mesh.vCoords.size(), &(mesh.vCoords.front()), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mesh.nCoords.size(), &(mesh.nCoords.front()), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mesh.tCoords.size(), &(mesh.tCoords.front()), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*mesh.iCoords.size(), &(mesh.iCoords.front()), GL_STATIC_DRAW);

}

void destroyFunc() {
    
    glDeleteTextures(NT,objTexture);
    glDeleteBuffers(NB,VBO);
    
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
    drawObject(2.0f,200);
    
 // Intercambiamos los buffers
    glutSwapBuffers();
    
}

void drawLights() {
    
 // Luz 0: Direccional
    glLightfv(GL_LIGHT0, GL_POSITION, DL0);
    
 // Luz 1: Posicional
    glLightfv(GL_LIGHT1, GL_POSITION, PL1);

}

void drawObject(GLfloat s, GLint c) {
    
 // Definimos el material del objeto
    GLfloat Ka[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat Kd[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat Ks[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT  , Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR , Ks);
    glMaterialf (GL_FRONT, GL_SHININESS, 50.0f);
    
 // Definimos el objeto
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, objTexture[0]);
    glPushMatrix();
        glTranslatef(0.0f, 2.0f, -5.0f);
        glRotatef(rotX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotY, 0.0f, 1.0f, 0.0f);
        glScalef(2.0f,2.0f,2.0f);
        myVbo();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void myVbo() {

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); glVertexPointer  (3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]); glNormalPointer  (   GL_FLOAT, 0, 0);  
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]); glTexCoordPointer(2, GL_FLOAT, 0, 0);
        
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[3]);
    glDrawElements (GL_TRIANGLES, meshSize, GL_UNSIGNED_SHORT, 0);
        
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
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

void funIdle() {
    
    rotY += 0.5f;
    Sleep(5);
    glutPostRedisplay();
    
}

Tmesh loadMesh(const char* filename) {
    
    Tmesh mesh;
    
    FILE *file = fopen(filename,"r");
    if(file == NULL) {
        printf("\n El fichero no se puede abrir (ENTER para continuar).\n");
        system("pause");
        exit(1);
    }
    
    std::vector<GLfloat>  nCoords, tCoords;
    std::vector<GLushort> *nLists;
    char  lineHeader[128], ignore;
    int   iv[3], it[3], in[3];
    float vCoord[3], tCoord[2], nCoord[3];
    bool  tflag = false;
    
    do { fscanf(file,"%s\n",&lineHeader); } while(strcmp(lineHeader,"v") != 0);
    
    fscanf(file, "%f %f %f\n", &vCoord[0], &vCoord[1], &vCoord[2]);
    for(int i=0; i<3; i++) mesh.vCoords.push_back((GLfloat)vCoord[i]);
    
    do {
        fscanf(file, "%s", lineHeader);
        if(strcmp(lineHeader,"v") == 0) {
            fscanf(file, "%f %f %f\n", &vCoord[0], &vCoord[1], &vCoord[2]);
            for(int i=0; i<3; i++) mesh.vCoords.push_back((GLfloat)vCoord[i]);
        }
        else if(strcmp(lineHeader,"vt") == 0) {
            tflag = true;
            fscanf(file,"%f %f\n", &tCoord[0], &tCoord[1]);
            for(int i=0; i<2; i++) {
                tCoords.push_back((GLfloat)tCoord[i]);
                mesh.tCoords.push_back(0.0f);
            }
        }
        else if(strcmp(lineHeader,"vn") == 0) {
            fscanf(file, "%f %f %f\n", &nCoord[0], &nCoord[1], &nCoord[2]);
            for(int i=0; i<3; i++) nCoords.push_back((GLfloat)nCoord[i]);
        }
    } while(strcmp(lineHeader,"s") != 0);
    
    fscanf(file,"%c off\n",&ignore);
    
    nLists = new std::vector<GLushort>[mesh.vCoords.size()];
    if(tflag) {
        while(fscanf(file, "%s", lineHeader) != EOF){
            fscanf(file,"%d/%d/%d %d/%d/%d %d/%d/%d\n", &iv[0], &it[0], &in[0], &iv[1], &it[1], &in[1], &iv[2], &it[2], &in[2]);
            for(int v=0; v<3; v++) {
                mesh.iCoords.push_back((GLushort)(iv[v]-1));
                nLists[iv[v]-1].push_back(in[v]-1);
                mesh.tCoords[(iv[v]-1)*2+0] = tCoords[(it[v]-1)*2+0];
                mesh.tCoords[(iv[v]-1)*2+1] = tCoords[(it[v]-1)*2+1];
            }
        }
    }
    else {
        while(fscanf(file, "%s", lineHeader) != EOF){
            fscanf(file,"%d//%d %d//%d %d//%d\n", &iv[0], &in[0], &iv[1], &in[1], &iv[2], &in[2]);
            for(int v=0; v<3; v++) {
                mesh.iCoords.push_back((GLushort)(iv[v]-1));
                nLists[iv[v]-1].push_back(in[v]-1);
            }
        }
    }
    
 // Calculo de normales
    for(int i=0; i<mesh.vCoords.size(); i++) {
        GLfloat x = 0.0f;
        GLfloat y = 0.0f;
        GLfloat z = 0.0f;
        int nNormals = nLists[i].size();
        for(int j=0; j<nNormals; j++) {
            x += nCoords[nLists[i][j]*3+0];
            y += nCoords[nLists[i][j]*3+1];
            z += nCoords[nLists[i][j]*3+2];
        }
        mesh.nCoords.push_back(x/(GLfloat)nNormals);
        mesh.nCoords.push_back(y/(GLfloat)nNormals);
        mesh.nCoords.push_back(z/(GLfloat)nNormals);
    }
    delete nLists;
    
    return mesh;
    
}
 */

