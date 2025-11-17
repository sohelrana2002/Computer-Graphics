#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

float xc, yc, r = 8;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(5.0);
    gluOrtho2D(-50, 50, -50, 50);
}

void put_pixel(float x, float y)
{
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc - y, yc - x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc - x, yc + y);

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
    float x = 0;
    float y = r;
    float p = 1 - r;

    cout << "Midpoint Circle Drawing Algorithm Points:" << endl;
    glBegin(GL_POINTS);

     while (x <= y)
    {
        put_pixel(x, y);

        if (p < 0)
        {
            x = x + 1;
            y = y;
            p += 2 * x + 3;
        }
        else
        {
            x = x + 1;
            y = y - 1;
            p += 2 * (x - y) + 5;
        }
    }

    glEnd();
    glFlush();
}

void display()
{
     glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Draw axes
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(50, 0);
    glVertex2f(-50, 0);
    glVertex2f(0, 50);
    glVertex2f(0, -50);
    glEnd();

    mcd();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Midpoint Circle Drawing Algorithm");

    cout << "Center point of x axis: ";
    cin >> xc;

    cout << "Center point of y -axis: ";
    cin >> yc;

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
