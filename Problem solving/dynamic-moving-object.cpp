#include <GL/glut.h>

// Window size
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Object properties
float objSize = 50.0f;
float objX = WINDOW_WIDTH / 2 - objSize / 2;  // start center horizontally
float objY = WINDOW_HEIGHT / 2 - objSize / 2; // start center vertically
float speed = 10.0f;                          // movement step when key pressed

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a rectangle as the boundary box
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

// handle special keys like arrow keys
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        if (objX + objSize + speed <= WINDOW_WIDTH)
            objX += speed;
        break;
    case GLUT_KEY_LEFT:
        if (objX - speed >= 0)
            objX -= speed;
        break;
    case GLUT_KEY_UP:
        if (objY + objSize + speed <= WINDOW_HEIGHT)
            objY += speed;
        break;
    case GLUT_KEY_DOWN:
        if (objY - speed >= 0)
            objY -= speed;
        break;
    }

    glutPostRedisplay(); // redraw the scene
}

void setup()
{
    glClearColor(0, 0, 0, 1);

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
    glutCreateWindow("Move Object with Arrow Keys");

    setup();

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys); // register arrow key handler

    glutMainLoop();
    return 0;
}
