// Direct circle drawing algorithm

#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
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
    glVertex2f(x, -y);
    glVertex2f(-x, y);
    glVertex2f(-x, -y);

    glEnd();

    glFlush();
}

void direct_circle(float x, float y, float z)
{
    y = r;

    put_pixel(x, y);

    while (x <= y)
    {
        int y_update = round(sqrt(r * r - x * x));
        x = x + 1;
        put_pixel(x, y_update);
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

    direct_circle(x, y, r);
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
    glutCreateWindow("GLUT Shapes");

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
