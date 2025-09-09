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

    // Triangle 
    glBegin(GL_LINES);
    glVertex2f(0.2, 0.2);
    glVertex2f(0.5, 0.8);
    glVertex2f(0.5, 0.8);
    glVertex2f(0.8, 0.2);
    glVertex2f(0.8, 0.2);
    glVertex2f(0.2, 0.2);
    glEnd();

    // Polygon 
    glBegin(GL_LINES);
    glVertex2f(-0.8, -0.2);
    glVertex2f(-0.2, -0.2);
    glVertex2f(-0.2, -0.2);
    glVertex2f(-0.7, -0.7);
    glVertex2f(-0.7, -0.7);
    glVertex2f(-0.5, -0.1);
    glVertex2f(-0.5, -0.1);
    glVertex2f(-0.4, -0.8);
    glVertex2f(-0.4, -0.8);
    glVertex2f(-0.8, -0.2);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("057,063");
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}