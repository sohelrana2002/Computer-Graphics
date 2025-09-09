#include <windows.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    glVertex2f(0, 1);
    glVertex2f(0, -1);

    glVertex2f(-1, 0);
    glVertex2f(1, 0);
    glEnd();

    // Rhombus
    glBegin(GL_LINES);
    glVertex2f(-0.3, 0.5);
    glVertex2f(0.3, 0.5);
    glVertex2f(-0.3, 0.5);
    glVertex2f(0, -0.5);
    glVertex2f(0, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.3, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Set 2 Rhombus");
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(444, 555);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}