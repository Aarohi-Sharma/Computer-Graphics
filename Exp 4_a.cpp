#include <GL/glut.h>
#include <iostream>

using namespace std;

float xmin = -50, ymin = -50, xmax = 50, ymax = 50; // Predefined clipping window

// Function to compute the region code for a point (x, y)
int ComputeCode(float x, float y) {
    int code = 0;
    if (x < xmin) code |= 1; // left
    if (x > xmax) code |= 2; // right
    if (y < ymin) code |= 4; // bottom
    if (y > ymax) code |= 8; // top
    return code;
}

// Cohen-Sutherland clipping algorithm
void CohenSutherlandClip(float x1, float y1, float x2, float y2) {
    int code1 = ComputeCode(x1, y1);
    int code2 = ComputeCode(x2, y2);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            accept = true; // Both points are inside the clipping area
            break;
        }
        else if (code1 & code2) {
            break; // Both points are outside the clipping area
        }
        else {
            int code_out;
            float x, y;

            // Select one of the points outside the clipping area
            if (code1 != 0) code_out = code1;
            else code_out = code2;

            // Find the intersection point
            if (code_out & 8) { // Top
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            }
            else if (code_out & 4) { // Bottom
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            }
            else if (code_out & 2) { // Right
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            }
            else if (code_out & 1) { // Left
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            // Replace point outside clipping area
            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = ComputeCode(x1, y1);
            }
            else {
                x2 = x;
                y2 = y;
                code2 = ComputeCode(x2, y2);
            }
        }
    }

    if (accept) {
        glColor3f(0.0, 0.0, 1.0); // Blue for clipped line
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window (rectangle)
    glColor3f(0.0, 1.0, 0.0); // Green for clipping window
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // Draw original line in red
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-100, -100);
    glVertex2f(100, 100);
    glEnd();

    // Perform clipping
    CohenSutherlandClip(-100, -100, 100, 100);
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200, 200, -200, 200);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
