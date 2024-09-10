/*
#include <GL/glut.h>  // Include the GLUT library for OpenGL


void display() {
    // Clear the screen with a background color
    glClear(GL_COLOR_BUFFER_BIT);

    // Begin drawing the line
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);  // Set the color to red
    glVertex2f(-0.5f, 0.0f);   // First point of the line
    glVertex2f(0.5f, 0.0f);    // Second point of the line
    glEnd();

    // Force the drawing to be displayed
    glFlush();
}

// Initialize OpenGL settings
void init() {
    // Set the background color to white
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Set up the viewing area
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Set 2D orthographic projection
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Create a window
    glutCreateWindow("OpenGL Line");

    // Set the display callback function
    glutDisplayFunc(display);

    // Initialize OpenGL settings
    init();

    // Start the GLUT main loop
    glutMainLoop();

    return 0;
}
*/
