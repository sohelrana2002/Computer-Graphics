#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

// Circle parameters
int xc = 6, yc = 5, r = 12;

void plotPoints(int x, int y)
{
    // Plot the 8 symmetrical points
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc - y, yc - x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc - x, yc + y);

    // Print points to console for verification
    cout << "(" << xc + x << "," << yc + y << ")  ";
    cout << "(" << xc + y << "," << yc + x << ")  ";
    cout << "(" << xc + y << "," << yc - x << ")  ";
    cout << "(" << xc + x << "," << yc - y << ")  ";
    cout << "(" << xc - x << "," << yc - y << ")  ";
    cout << "(" << xc - y << "," << yc - x << ")  ";
    cout << "(" << xc - y << "," << yc + x << ")  ";
    cout << "(" << xc - x << "," << yc + y << ")" << endl;
}

void mcd()
{
    int x = 0;
    int y = r;
    int d = 1 - r;

    cout << "Midpoint Circle Drawing Algorithm Points:" << endl;
    glBegin(GL_POINTS);

    while (x <= y)
    {
        plotPoints(x, y);

        if (d < 0)
            d += 2 * x + 3;
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }

    glEnd();
    glFlush();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    mcd();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White background
    glColor3f(0.0, 0.0, 1.0);          // Blue points
    glPointSize(5.0);
    gluOrtho2D(-50, 50, -50, 50);      // Adjust coordinate system
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Midpoint Circle Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}