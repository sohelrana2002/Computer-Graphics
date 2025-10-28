#include <GL/glut.h>

// Window size
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Object properties
float objSize = 50.0f;
float objX = WINDOW_WIDTH / 2 - objSize / 2;
float objY = WINDOW_HEIGHT / 2 - objSize / 2;
float speed = 3.0f;

// Direction control
int moveRight = 0;
int moveLeft = 0;
int moveUp = 0;
int moveDown = 0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw boundary box
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0, 0);
    glVertex2f(WINDOW_WIDTH, 0);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
    glVertex2f(0, WINDOW_HEIGHT);
    glEnd();

    // Draw square
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
    // Move continuously based on direction
    if (moveRight && objX + objSize + speed <= WINDOW_WIDTH)
        objX += speed;
    if (moveLeft && objX - speed >= 0)
        objX -= speed;
    if (moveUp && objY + objSize + speed <= WINDOW_HEIGHT)
        objY += speed;
    if (moveDown && objY - speed >= 0)
        objY -= speed;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // call again after 16ms (~60fps)
}

// Keyboard arrow key control
void specialKeys(int key, int x, int y)
{
    // Reset all directions
    moveRight = moveLeft = moveUp = moveDown = 0;

    switch (key)
    {
    case GLUT_KEY_RIGHT:
        moveRight = 1;
        break;
    case GLUT_KEY_LEFT:
        moveLeft = 1;
        break;
    case GLUT_KEY_UP:
        moveUp = 1;
        break;
    case GLUT_KEY_DOWN:
        moveDown = 1;
        break;
    }

    glutPostRedisplay();
}

// Optional: stop motion when pressing 's' or exit with ESC
void keyboard(unsigned char key, int x, int y)
{
    if (key == 's' || key == 'S')
    {
        moveRight = moveLeft = moveUp = moveDown = 0; // stop motion
    }
    else if (key == 27)
    { // ESC
        exit(0);
    }
}

void init()
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
    glutCreateWindow("Continuous Object Movement with Arrow Keys");

    init();

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
