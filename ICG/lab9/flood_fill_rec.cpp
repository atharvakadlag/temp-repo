#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
#include <GL/glut.h>  
#define HEIGHT 720
#define WIDTH 720

float fillColor[3] = { 0.0,1.0,1.0 };
float oldColor[3] = { 1.0,0.0,1.0 };

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

    glColor3fv(oldColor);
    glBegin(GL_POLYGON);
        for (int i = 0; i < 5; i++){
            glVertex2d(randint(0,720), randint(0,720));
        }
    glEnd();
    // glRectd(150, 200, 300, 300);
    glFlush();
}
void flood_fill(int x, int y, float fillColor[3], float oldColor[3])
{
    float currColor[3];
    readPixel(x, y, currColor);
    if (currColor[0] == oldColor[0] && (currColor[1]) == oldColor[1] && (currColor[2]) == oldColor[2]) {
        cout << "drawing fill at " << x << ", " << y << "\n";
        drawPixel(x, y, fillColor);
        flood_fill(x + 1, y + 1, fillColor, oldColor);
        flood_fill(x + 1, y, fillColor, oldColor);
        flood_fill(x + 1, y - 1, fillColor, oldColor);
        flood_fill(x, y + 1, fillColor, oldColor);
        flood_fill(x, y - 1, fillColor, oldColor);
        flood_fill(x - 1, y + 1, fillColor, oldColor);
        flood_fill(x - 1, y, fillColor, oldColor);
        flood_fill(x - 1, y - 1, fillColor, oldColor);
    }
}
void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int xi = x;
        int yi = (HEIGHT - y);
        cout << "starting fill at " << xi << ", " << yi << "\n";
        flood_fill(xi, yi, fillColor, oldColor);
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
