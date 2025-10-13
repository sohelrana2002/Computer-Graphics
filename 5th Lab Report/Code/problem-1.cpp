// mid point circle drawing algorithm

#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

float x, y, r;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
}

void put_pixel(float x, float y)
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glVertex2f(y, x);
    glVertex2f(y, -x);
    glVertex2f(x, -y);
    glVertex2f(-x, y);
    glVertex2f(-y, x);
    glVertex2f(-y, -x);
    glVertex2f(-x, -y);

    glEnd();

    glFlush();
}

void circle(float x, float y, float r)
{
    float p = 1 - r;
    y = r;

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
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Draw axes
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(100, 0);
    glVertex2f(-100, 0);
    glVertex2f(0, 100);
    glVertex2f(0, -100);
    glEnd();

    circle(x, y, r);
}

int main(int argc, char *argv[])
{
    cout << "Enter Redius: ";
    cin >> r;

    cout << "Enter Center Point of X axis:";
    cin >> x;

    cout << "Enter Center Point of Y axis:";
    cin >> y;

    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Mid point cicle drawing algorithm");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
