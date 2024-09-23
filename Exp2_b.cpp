#include <iostream>
#include <cmath>  // For round() function

using namespace std;

// DDA Algorithm to draw a line (output points to the console)
void drawLineDDA(int x0, int y0, int x1, int y1) {
    // Calculate the differences
    int dx = x1 - x0;
    int dy = y1 - y0;

    // Determine the number of steps based on the largest difference
    int steps = max(abs(dx), abs(dy));

    // Calculate the increment for each step
    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;

    // Initialize starting point
    float x = x0;
    float y = y0;

    // Output the starting point
    cout << "(" << round(x) << ", " << round(y) << ")" << endl;

    // Loop to compute and print each point
    for (int i = 0; i < steps; i++) {
        x += xIncrement;
        y += yIncrement;
        cout << "(" << round(x) << ", " << round(y) << ")" << endl;
    }
}

int main() {
    // Define the start and end points for slope m < 1
    int x0 = 2, y0 = 2, x1 = 8, y1 = 5;
    cout << "Line for slope m < 1:" << endl;
    drawLineDDA(x0, y0, x1, y1);

    cout << endl;

    // Define the start and end points for slope m > 1
    x0 = 4, y0 = 4, x1 = 6, y1 = 10;
    cout << "Line for slope m > 1:" << endl;
    drawLineDDA(x0, y0, x1, y1);

    return 0;
}
