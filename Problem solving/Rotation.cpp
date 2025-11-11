#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// Original triangle vertices
float triangle[3][2] = {
    {100.0, 100.0},
    {200.0, 100.0},
    {150.0, 200.0}};

// Transformed triangle vertices
float transformedTriangle[3][2];

// Transformation parameters
float angle = 45.0;         // Rotation angle in degrees

void initialize()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300, 300, -300, 300);

    // Initialize transformed triangle with original values
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            transformedTriangle[i][j] = triangle[i][j];
        }
    }
}

void drawTriangle()
{
    glBegin(GL_LINES);
    // Draw triangle edges
    glVertex2f(transformedTriangle[0][0], transformedTriangle[0][1]);
    glVertex2f(transformedTriangle[1][0], transformedTriangle[1][1]);

    glVertex2f(transformedTriangle[1][0], transformedTriangle[1][1]);
    glVertex2f(transformedTriangle[2][0], transformedTriangle[2][1]);

    glVertex2f(transformedTriangle[2][0], transformedTriangle[2][1]);
    glVertex2f(transformedTriangle[0][0], transformedTriangle[0][1]);
    glEnd();
}


void applyRotation()
{
    float radians = angle * M_PI / 180.0; // Convert to radians

    // Find center of triangle
    float centerX = (triangle[0][0] + triangle[1][0] + triangle[2][0]) / 3.0;
    float centerY = (triangle[0][1] + triangle[1][1] + triangle[2][1]) / 3.0;

    for (int i = 0; i < 3; i++)
    {
        // Translate to origin
        float x = triangle[i][0] - centerX;
        float y = triangle[i][1] - centerY;

        // Rotate
        transformedTriangle[i][0] = centerX + (x * cos(radians) - y * sin(radians));
        transformedTriangle[i][1] = centerY + (x * sin(radians) + y * cos(radians));
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw axes
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(300, 0);
    glVertex2f(-300, 0);
    glVertex2f(0, 300);
    glVertex2f(0, -300);
    glEnd();

    // Draw original triangle in green
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(triangle[0][0], triangle[0][1]);
    glVertex2f(triangle[1][0], triangle[1][1]);

    glVertex2f(triangle[1][0], triangle[1][1]);
    glVertex2f(triangle[2][0], triangle[2][1]);

    glVertex2f(triangle[2][0], triangle[2][1]);
    glVertex2f(triangle[0][0], triangle[0][1]);
    glEnd();

    // Draw transformed triangle in red
    glColor3f(1.0, 0.0, 0.0);
    applyRotation();

    drawTriangle();

    glutSwapBuffers();
}



int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformation of Triangle");

    initialize();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}