#include <GL/glut.h>
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

void init(void)
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
}

// Bresenham Algorithm
void bresenham(int x0, int y0, int x1, int y1)
{
    // Ensure left to right drawing for consistency
    if (x0 > x1 || y0 > y1)
    {
        swap(x0, x1);
        swap(y0, y1);
    }

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    float m = dy / (float)dx;

    int x = x0;
    int y = y0;

    int x_inc = (x1 >= x0) ? 1 : -1;
    int y_inc = (y1 >= y0) ? 1 : -1;

    glBegin(GL_POINTS);

    if (m < 1)
    {
        int p = 2 * dy - dx;

        while (x <= x1)
        {
            glVertex2i(x, y);

            x += x_inc;

            if (p < 0)
            {
                p += 2 * dy;
            }
            else
            {
                y += y_inc;
                p += 2 * dy - 2 * dx;
            }
        }
    }
    else
    {
        int p = 2 * dx - dy;

        while (x <= x1)
        {
            glVertex2i(x, y);

            y += y_inc;

            if (p < 0)
            {
                p += 2 * dx;
            }
            else
            {
                x += x_inc;
                p += 2 * dx - 2 * dy;
            }
        }
    }

    glEnd();
}

// Display callback
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw axes
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(100, 0);
    glVertex2f(-100, 0);
    glVertex2f(0, 100);
    glVertex2f(0, -100);
    glEnd();

    glColor3f(1, 0, 0);
    glPointSize(3);
    bresenham(15, 15, 45, 60);
    bresenham(45, 15, 15, 60);

    glFlush();
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
