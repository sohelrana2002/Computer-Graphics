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
float tx = 2.0, ty = 3.0;   // Translation
float sx1 = 2.0, sy1 = 2.0; // Scaling 1
float sx2 = 0.5, sy2 = 0.5; // Scaling 2
float angle = 45.0;         // Rotation angle in degrees
float shr = 2.0;            // Shearing

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
    drawTriangle();

    glutSwapBuffers();
}

void applyTranslation()
{
    for (int i = 0; i < 3; i++)
    {
        transformedTriangle[i][0] = triangle[i][0] + tx;
        transformedTriangle[i][1] = triangle[i][1] + ty;
    }
}

void applyScaling(float sx, float sy)
{
    // Find center of triangle
    float centerX = (triangle[0][0] + triangle[1][0] + triangle[2][0]) / 3.0;
    float centerY = (triangle[0][1] + triangle[1][1] + triangle[2][1]) / 3.0;

    for (int i = 0; i < 3; i++)
    {
        // Translate to origin, scale, then translate back
        transformedTriangle[i][0] = centerX + (triangle[i][0] - centerX) * sx;
        transformedTriangle[i][1] = centerY + (triangle[i][1] - centerY) * sy;
    }
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

void applyReflectionX()
{
    for (int i = 0; i < 3; i++)
    {
        transformedTriangle[i][0] = triangle[i][0];
        transformedTriangle[i][1] = -triangle[i][1];
    }
}

void applyReflectionY()
{
    for (int i = 0; i < 3; i++)
    {
        transformedTriangle[i][0] = -triangle[i][0];
        transformedTriangle[i][1] = triangle[i][1];
    }
}

void applyShearingX()
{
    // Calculate center of triangle
    float centerX = (triangle[0][0] + triangle[1][0] + triangle[2][0]) / 3.0;
    float centerY = (triangle[0][1] + triangle[1][1] + triangle[2][1]) / 3.0;

    for (int i = 0; i < 3; i++)
    {
        // Translate point to origin, apply shear, then translate back
        float x = triangle[i][0] - centerX;
        float y = triangle[i][1] - centerY;

        // Apply shearing transformation
        float newX = x + shr * y;
        float newY = y;

        // Translate back to original position
        transformedTriangle[i][0] = newX + centerX;
        transformedTriangle[i][1] = newY + centerY;
    }
}

void applyShearingY()
{
    // Calculate center of triangle
    float centerX = (triangle[0][0] + triangle[1][0] + triangle[2][0]) / 3.0;
    float centerY = (triangle[0][1] + triangle[1][1] + triangle[2][1]) / 3.0;

    for (int i = 0; i < 3; i++)
    {
        // Translate point to origin, apply shear, then translate back
        float x = triangle[i][0] - centerX;
        float y = triangle[i][1] - centerY;

        // Apply shearing transformation
        float newX = x;
        float newY = y + shr * x;

        // Translate back to original position
        transformedTriangle[i][0] = newX + centerX;
        transformedTriangle[i][1] = newY + centerY;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        printf("Applying Translation\n");
        applyTranslation();
        break;
    case '2':
        printf("Applying Scaling\n");
        applyScaling(sx1, sy1);
        break;
    case '3':
        printf("Applying Scaling\n");
        applyScaling(sx2, sy2);
        break;
    case '4':
        printf("Applying Rotation\n");
        applyRotation();
        break;
    case '5':
        printf("Applying Reflection about X-axis\n");
        applyReflectionX();
        break;
    case '6':
        printf("Applying Reflection about Y-axis\n");
        applyReflectionY();
        break;
    case '7':
        printf("Applying Shearin in X axis\n");
        applyShearingX();
        break;
    case '8':
        printf("Applying Shearin in Y axis\n");
        applyShearingY();
        break;
    case 'R':
        printf("Resetting to original triangle\n");
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                transformedTriangle[i][j] = triangle[i][j];
            }
        }
        break;
    case 27: // ESC key
        exit(0);
        break;
    }

    glutPostRedisplay();
}

void printInstructions()
{
    printf("\n=== 2D Transformation of Triangle ===\n");
    printf("Press keys 1-7 to apply transformations:\n");
    printf("1 - Translation\n");
    printf("2 - Scaling\n");
    printf("3 - Scaling\n");
    printf("4 - Rotation\n");
    printf("5 - Reflection about X-axis\n");
    printf("6 - Reflection about Y-axis\n");
    printf("7 - Applying Shearin in X axis\n");
    printf("8 - Applying Shearin in Y axis\n");
    printf("R - Reset to original triangle\n");
    printf("ESC - Exit\n");
    printf("=====================================\n\n");
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformation of Triangle");

    initialize();
    printInstructions();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}