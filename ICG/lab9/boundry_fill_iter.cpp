#include <bits/stdc++.h>
using namespace std;
#include <GL/glut.h>
#include <stack>
#define HEIGHT 720
#define WIDTH 720
#define Point pair<int, int>
float fillColor[3] = { 1.0,0.0,1.0 };
float borderColor[3] = { 1.0,0.0,1.0 };

stack<Point> recur_stack;

void drawPixel(int pointx, int pointy, float f[3])
{
    glBegin(GL_POINTS);
    glColor3fv(f);
    glVertex2i(pointx, pointy);
    glEnd();
    glFlush();
}
void readPixel(int x, int y, float pixels[3])
{
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, pixels);
}

int randint(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void display()
{
    glClearColor(0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(5);
    // glRectd(150, 250, 300, 300);/
    glBegin(GL_POLYGON);
        for (int i = 0; i < 5; i++){
            glVertex2d(randint(0,720), randint(0,720));
        }
    glEnd();
    glLineWidth(1);
    glFlush();
}
void boundaryFill(int x, int y, float fillColor[3], float borderColor[3])
{
    recur_stack.push(Point(x, y));

    while (!recur_stack.empty()) {
        Point p = recur_stack.top();
        recur_stack.pop();
        int x = p.first;
        int y = p.second;
        float currColor[3];
        readPixel(x, y, currColor);
        if ((currColor[0] != borderColor[0] && (currColor[1]) != borderColor[1] && (currColor[2]) != borderColor[2]) && (currColor[0] != fillColor[0] && (currColor[1]) != fillColor[1] && (currColor[2]) != fillColor[2]))
        {
            drawPixel(x, y, fillColor);
            recur_stack.push(Point(x + 1, y + 1));
            recur_stack.push(Point(x + 1, y));
            recur_stack.push(Point(x + 1, y - 1));
            recur_stack.push(Point(x, y + 1));
            recur_stack.push(Point(x, y - 1));
            recur_stack.push(Point(x - 1, y + 1));
            recur_stack.push(Point(x - 1, y));
            recur_stack.push(Point(x - 1, y - 1));
        }
    }
}
void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int xi = x;
        int yi = (HEIGHT - y);
        boundaryFill(xi, yi, fillColor, borderColor);
    }
}

int main(int argc, char** argv)
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Bountry-Fill-Recursive");
    glutDisplayFunc(display);
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)WIDTH, 0.0, (GLdouble)HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
