#include <GL/glut.h>
#include <cmath>
#include <string>
#include <iostream>

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 600;

// Current selected shape
int currentShape = 0; // No shape initially

// Material colors for different shapes
void setMaterialColor(int shape) {
    GLfloat material_diffuse[4];
    switch (shape) {
    case 1: // Cube - Royal Blue
        material_diffuse[0] = 0.0f;
        material_diffuse[1] = 0.2f;
        material_diffuse[2] = 0.8f;
        break;
    case 2: // Sphere - Emerald Green
        material_diffuse[0] = 0.0f;
        material_diffuse[1] = 0.8f;
        material_diffuse[2] = 0.3f;
        break;
    case 3: // Cone - Ruby Red
        material_diffuse[0] = 0.8f;
        material_diffuse[1] = 0.0f;
        material_diffuse[2] = 0.2f;
        break;
    case 4: // Cylinder - Purple
        material_diffuse[0] = 0.6f;
        material_diffuse[1] = 0.0f;
        material_diffuse[2] = 0.8f;
        break;
    case 5: // Cuboid - Golden
        material_diffuse[0] = 1.0f;
        material_diffuse[1] = 0.84f;
        material_diffuse[2] = 0.0f;
        break;
    case 6: // Prism - Turquoise
        material_diffuse[0] = 0.0f;
        material_diffuse[1] = 0.8f;
        material_diffuse[2] = 0.8f;
        break;
    case 7: // Torus - Orange
        material_diffuse[0] = 1.0f;
        material_diffuse[1] = 0.5f;
        material_diffuse[2] = 0.0f;
        break;
    }
    material_diffuse[3] = 1.0f; // Alpha value
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
}

// Drawing functions for each shape
void drawCube() {
    setMaterialColor(1);
    glutSolidCube(1.0f);
}

void drawSphere() {
    setMaterialColor(2);
    glutSolidSphere(0.7f, 30, 30);
}

void drawCone() {
    setMaterialColor(3);
    glutSolidCone(0.7f, 1.2f, 30, 30);
}

void drawCylinder() {
    GLUquadricObj* quadric = gluNewQuadric();


    setMaterialColor(4);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadric, 0.5f, 0.5f, 1.0f, 30, 30);
    gluDeleteQuadric(quadric);
}

void drawCuboid() {
    setMaterialColor(5);
    glScalef(1.5f, 1.0f, 0.7f);
    glutSolidCube(1.0f);
}

void drawPrism() {
    setMaterialColor(6);
    // Draw a triangular prism
    glBegin(GL_TRIANGLES);
    // Front face
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.0f, 0.5f, 0.5f);
    // Back face
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.0f, 0.5f, -0.5f);
    glEnd();

    glBegin(GL_QUADS);
    // Bottom face
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // Left face
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.0f, 0.5f, 0.5f);
    glVertex3f(0.0f, 0.5f, -0.5f);


    glVertex3f(-0.5f, -0.5f, -0.5f);
    // Right face
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.0f, 0.5f, 0.5f);
    glVertex3f(0.0f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();
}

void drawTorus() {
    setMaterialColor(7);
    glutSolidTorus(0.2f, 0.5f, 20, 30);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Position the camera
    gluLookAt(0.0f, 0.0f, 5.0f,  // Eye position
        0.0f, 0.0f, 0.0f,   // Look at position
        0.0f, 1.0f, 0.0f);  // Up vector

    // Add slight rotation for better 3D perspective
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);

    // Draw the selected shape
    switch (currentShape) {
    case 1: drawCube(); break;
    case 2: drawSphere(); break;
    case 3: drawCone(); break;
    case 4: drawCylinder(); break;
    case 5: drawCuboid(); break;
    case 6: drawPrism(); break;
    case 7: drawTorus(); break;
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
        currentShape = key - '0';
        break;
    case 'q':
    case 'Q':
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    // Set background color to dark gray
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Enable lighting and material properties
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);

    // Set up light position and properties
    GLfloat lightPos[] = { 5.0f, 5.0f, 5.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Set material properties for shininess
    GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat material_shininess[] = { 50.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

    // Print instructions
    std::cout << "\n3D Shapes Viewer Instructions:" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Press number keys to show shapes:" << std::endl;
    std::cout << "1: Cube (Royal Blue)" << std::endl;
    std::cout << "2: Sphere (Emerald Green)" << std::endl;
    std::cout << "3: Cone (Ruby Red)" << std::endl;
    std::cout << "4: Cylinder (Purple)" << std::endl;
    std::cout << "5: Cuboid (Golden)" << std::endl;
    std::cout << "6: Triangular Prism (Turquoise)" << std::endl;
    std::cout << "7: Torus (Orange)" << std::endl;
    std::cout << "Press Q to quit" << std::endl;
    std::cout << "-----------------------------\n" << std::endl;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Colorful 3D Shapes Viewer");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
