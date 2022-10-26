#include <GL/freeglut.h>
#include <bits/stdlib.h>
#include <math.h>
#include <unistd.h>

#include <iostream>

#include "clipping.hpp"

using namespace std;
#define HEIGHT 720
#define WIDTH 720
#define PADDING 10

int randint(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void draw_car(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int x_min = 360;
    int x_max = 1080;
    int y_min = 360;
    int y_max = 1080;

    Point p1 = Point(x_min, y_min);
    Point p2 = Point(x_max, y_min);
    Point p3 = Point(x_max, y_max);
    Point p4 = Point(x_min, y_max);
    vector<Point> rect_window = {p1, p2, p3, p4};
    ClippingWindow clip = ClippingWindow(rect_window);

    glColor3f(0.5, 0.5, 0.5);
    glRectd(x_min, y_min, x_max, y_max);
    glPointSize(2);
    glBegin(GL_POINTS);
        for (int i = 0; i < 200; i++) {
    	int x = randint(0, 1440);
    	int y = randint(0, 1440);
    	Point test = Point(x, y);
    	if (clip.contains(test)) {
    		glColor3f(0, 1, 0);
    		glVertex2d(x, y);
    	} else {
    		glColor3f(1, 0, 0);
    		glVertex2d(x, y);
    	}
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH + PADDING, HEIGHT + PADDING);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("generated points");
    gluOrtho2D(-PADDING, WIDTH * 2 + 2 * PADDING * 2, -PADDING, HEIGHT * 2 + 2 * PADDING);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(draw_car);
    glutMainLoop();

    return 0;
}