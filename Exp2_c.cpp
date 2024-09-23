#include <GL/glut.h>
#include <iostream>

// Function to set a pixel in the window
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Bresenham's Line Drawing Algorithm for slope |m| < 1 (dx > dy)
void bresenhamLineLow(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int yi = 1;

    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }

    int D = 2 * dy - dx;
    int y = y1;

    for (int x = x1; x <= x2; x++) {
        setPixel(x, y);
        if (D > 0) {
            y += yi;
            D -= 2 * dx;
        }
        D += 2 * dy;
    }
}

// Bresenham's Line Drawing Algorithm for slope |m| > 1 (dy > dx)
void bresenhamLineHigh(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int xi = 1;

    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }

    int D = 2 * dx - dy;
    int x = x1;

    for (int y = y1; y <= y2; y++) {
        setPixel(x, y);
        if (D > 0) {
            x += xi;
            D -= 2 * dy;
        }
        D += 2 * dx;
    }
}

// General Bresenham's Line Drawing Algorithm that handles both slopes m < 1 and m > 1
void bresenhamLine(int x1, int y1, int x2, int y2) {
    if (abs(y2 - y1) < abs(x2 - x1)) {
        if (x1 > x2) {
            bresenhamLineLow(x2, y2, x1, y1);
        }
        else {
            bresenhamLineLow(x1, y1, x2, y2);
        }
    }
    else {
        if (y1 > y2) {
            bresenhamLineHigh(x2, y2, x1, y1);
        }
        else {
            bresenhamLineHigh(x1, y1, x2, y2);
        }
    }
}

// Display callback function for OpenGL
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the window

    // Draw two lines using Bresenham's Algorithm
    // For example: line from (100, 100) to (700, 300) (m < 1) and (300, 100) to (500, 500) (m > 1)
    bresenhamLine(100, 100, 700, 300);  // Line with slope m < 1
    bresenhamLine(300, 100, 500, 500);  // Line with slope m > 1

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
    glutCreateWindow("Bresenham's Line Drawing Algorithm");

    init();  // Initialize OpenGL
    glutDisplayFunc(display);  // Set display callback
    glutMainLoop();  // Start the main loop

    return 0;
}
