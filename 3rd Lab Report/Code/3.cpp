#include <GL/glut.h>
#include <math.h>

void init(void) {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
}

// DDA Algorithm
void DDA(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    float steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
    float x_inc = dx / steps;
    float y_inc = dy / steps;

    float x = x1, y = y1;

    glPointSize(3.0);
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2f(x, y);
        x += x_inc;
        y += y_inc;
    }
    glEnd();
}

// DLD Algorithm
void DLD(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    float m = dy / dx;
    float b = y1 - m * x1;

    glPointSize(3.0);
    glBegin(GL_POINTS);

    if (fabs(m) <= 1) {
        float start = (x1 < x2) ? x1 : x2;
        float end = (x1 < x2) ? x2 : x1;

        for (float x = start; x <= end; x += 1.0) {
            float y = m * x + b;
            glVertex2f(x, round(y));
        }
    }
    else {
        float start = (y1 < y2) ? y1 : y2;
        float end = (y1 < y2) ? y2 : y1;

        for (float y = start; y <= end; y += 1.0) {
            float x = (y - b) / m;
            glVertex2f(round(x), y);
        }
    }
    glEnd();
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw axes
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(100, 0);  glVertex2f(-100, 0);
    glVertex2f(0, 100);  glVertex2f(0, -100);
    glEnd();

    // Red rectangle with DDA
    glColor3f(1, 0, 0);
    DDA(10, 80, 50, 80);
    DDA(10, 80, 10, 50);
    DDA(10, 50, 50, 50);
    DDA(50, 50, 50, 20);
    DDA(50, 20, 10, 20);

    // Blue triangle with DLD
    glColor3f(0, 0, 1);
    DLD(-60, 20, -40, 80);
    DLD(-20, 20, -40, 80);
    DLD(-50, 50, -30, 50);

    glFlush();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA & DLD");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
