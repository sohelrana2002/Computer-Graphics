// snake.cpp
// Simple Snake game using OpenGL + GLUT (immediate mode).
// Compile (Linux): g++ snake.cpp -o snake -lGL -lGLU -lglut
// Compile (Windows with MinGW + freeglut): g++ snake.cpp -o snake -lfreeglut -lopengl32 -lglu32

#include <GL/glut.h>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

int windowWidth = 600;
int windowHeight = 600;

// Grid settings
const int cols = 30;
const int rows = 30;
int cellSize = 20; // will be recalculated if window resizes

// Game state
enum Direction { UP, DOWN, LEFT, RIGHT };
Direction dir = RIGHT;
bool gameOver = false;
int score = 0;
int speedMs = 250; // move every X milliseconds

struct Point { int x, y; };
std::deque<Point> snake; // front = head
Point food;

// Helpers
void placeFood() {
    bool ok = false;
    while (!ok) {
        food.x = rand() % cols;
        food.y = rand() % rows;
        ok = true;
        for (auto& p : snake) if (p.x == food.x && p.y == food.y) { ok = false; break; }
    }
}

void resetGame() {
    snake.clear();
    // start snake in center with length 3
    int sx = cols / 2;
    int sy = rows / 2;
    snake.push_back({ sx, sy });
    snake.push_back({ sx - 1, sy });
    snake.push_back({ sx - 2, sy });
    dir = RIGHT;
    score = 0;
    gameOver = false;
    speedMs = 250;
    placeFood();
}

// Convert grid coord to pixel rectangle
void drawCell(int gx, int gy) {
    int px = gx * cellSize;
    int py = gy * cellSize;
    glBegin(GL_QUADS);
    glVertex2i(px, py);
    glVertex2i(px + cellSize, py);
    glVertex2i(px + cellSize, py + cellSize);
    glVertex2i(px, py + cellSize);
    glEnd();
}

void drawGridLines() {
    glColor3f(0.85f, 0.85f, 0.85f);
    glBegin(GL_LINES);
    for (int i = 0; i <= cols; ++i) {
        int x = i * cellSize;
        glVertex2i(x, 0); glVertex2i(x, rows * cellSize);
    }
    for (int j = 0; j <= rows; ++j) {
        int y = j * cellSize;
        glVertex2i(0, y); glVertex2i(cols * cellSize, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw grid background
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCell(0, 0); // not used but keep white background via clear

    // Draw grid lines
    drawGridLines();

    // Draw food
    glColor3f(1.0f, 0.0f, 0.0f); // red
    drawCell(food.x, food.y);

    // Draw snake: head a different color
    if (!snake.empty()) {
        // head
        glColor3f(0.0f, 0.6f, 0.0f);
        drawCell(snake.front().x, snake.front().y);

        // body
        glColor3f(0.0f, 0.9f, 0.0f);
        for (size_t i = 1; i < snake.size(); ++i) {
            drawCell(snake[i].x, snake[i].y);
        }
    }

    glutSwapBuffers();
}

void updateTitle() {
    std::ostringstream ss;
    ss << "Simple Snake - Score: " << score << (gameOver ? " (Game Over - press R to restart)" : "");
    glutSetWindowTitle(ss.str().c_str());
}

void timer(int value) {
    if (!gameOver) {
        // compute new head position
        Point head = snake.front();
        Point newHead = head;

        if (dir == UP)    newHead.y += 1;
        if (dir == DOWN)  newHead.y -= 1;
        if (dir == LEFT)  newHead.x -= 1;
        if (dir == RIGHT) newHead.x += 1;

        // check wall collision
        if (newHead.x < 0 || newHead.x >= cols || newHead.y < 0 || newHead.y >= rows) {
            gameOver = true;
            updateTitle();
            glutPostRedisplay();
            return;
        }

        // check self collision
        for (auto& p : snake) {
            if (p.x == newHead.x && p.y == newHead.y) {
                gameOver = true;
                updateTitle();
                glutPostRedisplay();
                return;
            }
        }

        // push new head
        snake.push_front(newHead);

        // eat food?
        if (newHead.x == food.x && newHead.y == food.y) {
            score += 10;
            placeFood();
            // optional: speed up
            if (speedMs > 40 && score % 50 == 0) speedMs -= 5;
        }
        else {
            // remove tail
            snake.pop_back();
        }

        updateTitle();
    }

    glutPostRedisplay();
    glutTimerFunc(speedMs, timer, 0);
}

void reshape(int w, int h) {
    // maintain square grid area
    windowWidth = w;
    windowHeight = h;
    int gridPixel = std::min(windowWidth, windowHeight);
    cellSize = gridPixel / std::max(cols, rows);

    glViewport(0, 0, cols * cellSize, rows * cellSize);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, cols * cellSize, 0, rows * cellSize);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(int key, int x, int y) {
    // arrow keys
    if (key == GLUT_KEY_UP && dir != DOWN) dir = UP;
    else if (key == GLUT_KEY_DOWN && dir != UP) dir = DOWN;
    else if (key == GLUT_KEY_LEFT && dir != RIGHT) dir = LEFT;
    else if (key == GLUT_KEY_RIGHT && dir != LEFT) dir = RIGHT;
}

void normalKey(unsigned char k, int x, int y) {
    if (k == 27) exit(0); // ESC
    if ((k == 'r' || k == 'R') && gameOver) {
        resetGame();
        updateTitle();
        // Restart the timer loop
        glutTimerFunc(speedMs, timer, 0);
        glutPostRedisplay(); // Force redraw to show new game state
    }
    if (k == 'p' || k == 'P') {
        // simple pause toggle using gameOver flag as pause
        gameOver = !gameOver;
        updateTitle();
    }
}

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(nullptr)));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Simple Snake");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // white background

    resetGame();
    updateTitle();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(normalKey);
    glutTimerFunc(speedMs, timer, 0);

    glutMainLoop();
    return 0;
}
