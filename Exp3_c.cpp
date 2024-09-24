#include <GL/glut.h>
#include <iostream>
#include <cmath>

// Function to set a pixel in the window
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Function to draw symmetrical points of the ellipse
void plotEllipsePoints(int xc, int yc, int x, int y) {
    setPixel(xc + x, yc + y);
    setPixel(xc - x, yc + y);
    setPixel(xc + x, yc - y);
    setPixel(xc - x, yc - y);
}

// Mid-point Ellipse Drawing Algorithm
void midPointEllipse(int xc, int yc, int rx, int ry) {
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;

    // Initial decision parameter for region 1
    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    // Region 1
    while (dx < dy) {
        plotEllipsePoints(xc, yc, x, y);

        if (d1 < 0) {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    // Initial decision parameter for region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);

    // Region 2
    while (y >= 0) {
        plotEllipsePoints(xc, yc, x, y);

        if (d2 > 0) {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
}

// Display function for OpenGL
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen

    // Draw the ellipse with center at (400, 300) and radii rx = 200, ry = 100
    midPointEllipse(400, 300, 200, 100);

    glFlush();  // Ensure all OpenGL commands are executed
}

// OpenGL initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set background to white
    glColor3f(0.0, 0.0, 0.0);          // Set drawing color to black
    glPointSize(2.0);                  // Set point size for clearer pixels
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);  // Set coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mid-point Ellipse Drawing Algorithm");

    init();  // Initialize OpenGL
    glutDisplayFunc(display);  // Set display callback
    glutMainLoop();  // Start the main loop

    return 0;
}
