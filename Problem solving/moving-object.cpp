#include <GL/glut.h>

// Window size
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Object properties
float objSize = 50.0f;
float objX = 0.0f;                            // Object's current X position
float objY = WINDOW_HEIGHT / 2 - objSize / 2; // Center vertically
float speed = 2.0f;                           // Speed of translation

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a rectangle as the boundary box (the window edges)
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0, 0);
    glVertex2f(WINDOW_WIDTH, 0);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
    glVertex2f(0, WINDOW_HEIGHT);
    glEnd();

    // Draw the moving square
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(objX, objY);
    glVertex2f(objX + objSize, objY);
    glVertex2f(objX + objSize, objY + objSize);
    glVertex2f(objX, objY + objSize);
    glEnd();

    glutSwapBuffers();
}

void update(int value)
{
    // Move object to the right until hitting the right boundary
    if (objX + objSize + speed <= WINDOW_WIDTH)
    {
        objX += speed;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // roughly 60 FPS
}

void setup()
{
    // Set clear color to black
    glClearColor(0, 0, 0, 1);

    // Set up orthographic projection for 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("2D Object Translation with Boundary");

    setup();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
