#include <GL/glut.h>
#include <iostream>

// Line equation parameters
float m = 1.0f; // Slope
float c = 0.0f; // Y-intercept

// Window dimensions
const int windowWidth = 800;
const int windowHeight = 600;

// Function to initialize OpenGL settings
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white
    glColor3f(0.0, 0.0, 0.0);         // Set drawing color to black
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight); // Set the orthographic view
}

// Function to draw a line using Y = mX + C
void drawLineEquation() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Draw the line using the equation Y = mX + C
    glBegin(GL_LINES);
    for (int x = 0; x < windowWidth; x++) {
        float y = m * x + c;  // Calculate Y for each X
        if (y >= 0 && y < windowHeight) {
            glVertex2i(x, y);  // Set a point at (x, y)
        }
    }
    glEnd();

    glFlush();  // Render now
}

// Callback function called by GLUT
void display() {
    drawLineEquation();
}

// Main function
int main(int argc, char** argv) {
    std::cout << "Enter the slope (m): ";
    std::cin >> m;
    std::cout << "Enter the y-intercept (c): ";
    std::cin >> c;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Line Drawing using Y=mX+C");

    init();                 // Initialize the window
    glutDisplayFunc(display);// Register the display callback function
    glutMainLoop();          // Enter the main loop

    return 0;
}
