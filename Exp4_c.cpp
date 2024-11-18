#include <GL/glut.h>
#include <iostream>
using namespace std;

const int MAX_POINTS = 20;

// Function to return x-value of point of intersection of two lines
int x_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    int num = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
    int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    return num / den;
}

// Function to return y-value of point of intersection of two lines
int y_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    int num = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);
    int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    return num / den;
}

// Function to clip all the edges w.r.t one clip edge of the clipping area
void clip(int poly_points[][2], int& poly_size, int x1, int y1, int x2, int y2) {
    int new_points[MAX_POINTS][2], new_poly_size = 0;

    for (int i = 0; i < poly_size; i++) {
        int k = (i + 1) % poly_size;
        int ix = poly_points[i][0], iy = poly_points[i][1];
        int kx = poly_points[k][0], ky = poly_points[k][1];

        int i_pos = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);
        int k_pos = (x2 - x1) * (ky - y1) - (y2 - y1) * (kx - x1);

        if (i_pos < 0 && k_pos < 0) {
            new_points[new_poly_size][0] = kx;
            new_points[new_poly_size][1] = ky;
            new_poly_size++;
        }
        else if (i_pos >= 0 && k_pos < 0) {
            new_points[new_poly_size][0] = x_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
            new_points[new_poly_size][1] = y_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;
            new_points[new_poly_size][0] = kx;
            new_points[new_poly_size][1] = ky;
            new_poly_size++;
        }
        else if (i_pos < 0 && k_pos >= 0) {
            new_points[new_poly_size][0] = x_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
            new_points[new_poly_size][1] = y_intersect(x1, y1, x2, y2, ix, iy, kx, ky);
            new_poly_size++;
        }
    }

    poly_size = new_poly_size;
    for (int i = 0; i < poly_size; i++) {
        poly_points[i][0] = new_points[i][0];
        poly_points[i][1] = new_points[i][1];
    }
}

// Implements Sutherland–Hodgman algorithm
void suthHodgClip(int poly_points[][2], int& poly_size, int clipper_points[][2], int clipper_size) {
    for (int i = 0; i < clipper_size; i++) {
        int k = (i + 1) % clipper_size;
        clip(poly_points, poly_size, clipper_points[i][0], clipper_points[i][1], clipper_points[k][0], clipper_points[k][1]);
    }
}

// Global variables for polygon and clipper
int poly_points[20][2] = { {100, 150}, {200, 250}, {300, 200} };
int poly_size = 3;
int clipper_points[4][2] = { {150, 150}, {150, 200}, {200, 200}, {200, 150} };
int clipper_size = 4;

// Function to display the polygons
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw and fill the clipping polygon
    glColor3f(0.0, 1.0, 0.0); // Green for clipping window
    glBegin(GL_POLYGON);
    for (int i = 0; i < clipper_size; i++) {
        glVertex2i(clipper_points[i][0], clipper_points[i][1]);
    }
    glEnd();

    // Draw and fill the original polygon
    glColor3f(1.0, 0.0, 0.0); // Red for original polygon
    glBegin(GL_POLYGON);
    for (int i = 0; i < poly_size; i++) {
        glVertex2i(poly_points[i][0], poly_points[i][1]);
    }
    glEnd();

    // Perform clipping
    suthHodgClip(poly_points, poly_size, clipper_points, clipper_size);

    // Draw and fill the clipped polygon
    glColor3f(0.0, 0.0, 1.0); // Blue for clipped polygon
    glBegin(GL_POLYGON);
    for (int i = 0; i < poly_size; i++) {
        glVertex2i(poly_points[i][0], poly_points[i][1]);
    }
    glEnd();

    glFlush();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sutherland-Hodgman Polygon Clipping");
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white
    glColor3f(0.0, 0.0, 0.0); // Set drawing color to black
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 400, 0, 400); // Set up the coordinate system
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
