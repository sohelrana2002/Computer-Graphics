
#include <windows.h>
#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    glVertex2f(1, 0);
    glVertex2f(-1, 0);

    glVertex2f(0, 1);
    glVertex2f(0, -1);
    glEnd();

    // A 
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1, 0.3, 0.3);
    for (float i = 0.3; i <= 0.9; i = i + (0.001)) {
        glVertex2f(i, 0.3);
    }
    glEnd();

    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1, 0.3, 0.3);
    for (float i = 0.2; i <= 0.6; i = i + (0.001)) {
        glVertex2f(i, i);
    }
    glEnd();

    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1, 0.3, 0.3);
    for (float i = 0.0; i <= 0.37; i = i + (0.001)) {
        glVertex2f(0.6 + i, 0.6 - i);
    }
    glEnd();

    // E 
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1, 0.3, 0.3);
    for (float i = 0.1; i <= 0.6; i = i + (0.001)) {
        glVertex2f(-0.6, -i);
    }
    glEnd();

    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1, 0.3, 0.3);
    for (float i = 0.6; i >= 0.1; i = i - (0.001)) {
        glVertex2f(-i, -0.6);
    }
    glEnd();

    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1, 0.3, 0.3);
    for (float i = 0.6; i >= 0.1; i = i - (0.001)) {
        glVertex2f(-i, -0.35);
    }
    glEnd();

    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1, 0.3, 0.3);
    for (float i = 0.6; i >= 0.1; i = i - (0.001)) {
        glVertex2f(-i, -0.1);
    }
    glEnd();


    glFlush();

}
int main(int argc, char* argv[]) {

    glutInit(&argc, argv);
    glutInitWindowSize(440, 480);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow(" Gult_Graphics");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
