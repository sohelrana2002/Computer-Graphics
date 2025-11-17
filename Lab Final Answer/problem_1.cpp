#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

float carBody[4][2] = {
    {-20, 0}, {20, 0}, {20, 10}, {-20, 10}
};
float wheel1[2] = {-10, -5};
float wheel2[2] = {10, -5};


void init() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(-100, 100, -100, 100);
}

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.1416 / 180;
        glVertex2f(cx + r * cos(theta), cy + r * sin(theta));
    }
    glEnd();
}

void drawCar() {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++)
        glVertex2f(carBody[i][0], carBody[i][1]);
    glEnd();

    drawCircle(wheel1[0], wheel1[1], 5);
    drawCircle(wheel2[0], wheel2[1], 5);
}

void scaleCar(float sx, float sy) {
    for (int i = 0; i < 4; i++) {
        carBody[i][0] *= sx;
        carBody[i][1] *= sy;
    }
    wheel1[0] *= sx; wheel1[1] *= sy;
    wheel2[0] *= sx; wheel2[1] *= sy;
}


void rotateCar() {
    float angle = 20 * 3.1416 / 180;
    for (int i = 0; i < 4; i++) {
        float x = carBody[i][0];
        float y = carBody[i][1];
        carBody[i][0] = x * cos(angle) - y * sin(angle);
        carBody[i][1] = x * sin(angle) + y * cos(angle);
    }
    float x, y;
    x = wheel1[0]; y = wheel1[1];
    wheel1[0] = x * cos(angle) - y * sin(angle);
    wheel1[1] = x * sin(angle) + y * cos(angle);

    x = wheel2[0]; y = wheel2[1];
    wheel2[0] = x * cos(angle) - y * sin(angle);
    wheel2[1] = x * sin(angle) + y * cos(angle);
}


void shearCar(float shx) {
    for (int i = 0; i < 4; i++) {
        float x = carBody[i][0];
        float y = carBody[i][1];
        carBody[i][0] = x + shx * y;
    }
    float x, y;
    x = wheel1[0]; y = wheel1[1];
    wheel1[0] = x + shx * y;

    x = wheel2[0]; y = wheel2[1];
    wheel2[0] = x + shx * y;
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(100, 0); glVertex2f(-100, 0);
    glVertex2f(0, 100); glVertex2f(0, -100);
    glEnd();

    glColor3f(0, 0, 1);
    drawCar();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            scaleCar(1.4, 1);
            printf("Car scaled up by 1.4 axis.\n");
            break;
        case '2':
            rotateCar();
            printf("Car rotated 20d \n");
            break;
        case '3':
            shearCar(0.3); // X-shear
            printf("Car sheared in X axis.\n");
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Car Tf");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    printf("1: Scaling\n");
    printf("2: Rotation\n");
    printf("3: Shearing\n");

    glutMainLoop();
    return 0;
}
