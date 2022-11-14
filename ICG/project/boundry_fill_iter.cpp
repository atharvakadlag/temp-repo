#include <bits/stdc++.h>
using namespace std;
#include <GL/glut.h>
#include <stack>
#define HEIGHT 1440
#define WIDTH 1440

int start = 1440;
int pothole_side = rand() % 2;
int pothole_center_x = pothole_side ? 540 : 900;

void draw_ellipse(float cx, float cy, float rx, float ry, int num_segments=100) 
{ 
    float theta = 2 * 3.1415926 / float(num_segments); 
    float c = cosf(theta);
    float s = sinf(theta);
    float t;

    float x = 1;
    float y = 0; 

    glBegin(GL_POLYGON); 
    for(int ii = 0; ii < num_segments; ii++) 
    { 
        glVertex2f(x * rx + cx, y * ry + cy);//output vertex 
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    } 
    glEnd(); 
}


void display()
{
    glClearColor(0.0, 0.8, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.2, 0.2, 0.2);
    glRectd(340, 0, 380+720, 1440);

    glColor3f(0.8, 0.8, 0.8);
    glRectd(360, 0, 360+720, 1440);

    glColor3f(0.2, 0.2, 0.2);
    int height = 300;
    int gap = 100;
    int curr = start;
    for (int i = 0; i < 4; i++) {
        glRectd(720-20, curr, 720+20, curr - height);
        curr = curr - gap - height;
    }
    if (start < 720) {
        pothole_side = rand() % 2;
        pothole_center_x = pothole_side ? 540 : 900;
    }
    glColor3f(0.6, 0.6, 0.6);
    draw_ellipse(pothole_center_x, start - 720, 100, 50);

    glFlush();
}

void keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            start -= 10;
            if (start <= 1140) {
                start = 1440;
            }
            display();
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
    // glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboard);
    glutMainLoop();
    return 0;
}
