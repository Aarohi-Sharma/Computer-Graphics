#include <GL/glut.h>
#include <iostream>

double xmin = 50, ymin = 50, xmax = 150, ymax = 150;

void LiangBarskyClip(double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double p[4], q[4];
    p[0] = -dx; q[0] = x1 - xmin;
    p[1] = dx;  q[1] = xmax - x1;
    p[2] = -dy; q[2] = y1 - ymin;
    p[3] = dy;  q[3] = ymax - y1;

    double t0 = 0.0, t1 = 1.0;
    for (int i = 0; i < 4; i++)
    {
        if (p[i] == 0 && q[i] < 0)
            return; // Line is outside

        double t = q[i] / p[i];
        if (p[i] < 0)
        {
            if (t > t1)
                return; // Line is outside
            if (t > t0)
                t0 = t; // Line is clipped
        }
        else if (p[i] > 0)
        {
            if (t < t0)
                return; // Line is outside
            if (t < t1)
                t1 = t; // Line is clipped
        }
    }

    double new_x1 = x1 + t0 * dx;
    double new_y1 = y1 + t0 * dy;
    double new_x2 = x1 + t1 * dx;
    double new_y2 = y1 + t1 * dy;

    glColor3f(1.0, 0.0, 0.0); // Clipped line in red
    glBegin(GL_LINES);
    glVertex2d(new_x1, new_y1);
    glVertex2d(new_x2, new_y2);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the clipping rectangle
    glColor3f(0.0, 0.0, 1.0); // Rectangle in blue
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // Example lines to demonstrate clipping
    LiangBarskyClip(60, 20, 80, 120);
    LiangBarskyClip(70, 80, 200, 300);
    LiangBarskyClip(30, 50, 60, 100);
    LiangBarskyClip(200, 10, 140, 150);

    glFlush();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(0.0, 0.0, 0.0);         // Black drawing color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Liang Barsky Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
