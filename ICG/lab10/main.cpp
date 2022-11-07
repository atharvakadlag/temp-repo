#include <bits/stdc++.h>
#include <GL/glut.h>  
#define HEIGHT 720
#define WIDTH 720

void grass () {
    glColor3f(0.11, 0.38, 0.16);
    glBegin(GL_POLYGON);
    glVertex2d(0,  0);
    glVertex2d(0,  450);
    glVertex2d(720, 450);
    glVertex2d(720,  0);
    glEnd();
    glFlush();
}

void tree (float scale=1, int startx=10, int starty=200) {
    float width_bottom = 60*scale;
    float width_top = 30*scale;
    float height = 220*scale;
    glColor3f(0.4, 0.17, 0.02);
    /* Draw tree bottom */
    glBegin(GL_POLYGON);
    glVertex2d(startx, starty);
    glVertex2d(startx + (width_bottom - width_top)/2, starty+height);
    glVertex2d(startx + (width_bottom + width_top)/2, starty+height);
    glVertex2d(startx+width_bottom, starty);
    glEnd();
    /* Draw tree bottom */
    glBegin(GL_POLYGON);
    glVertex2d(width_bottom/2+startx, starty+height);
    glVertex2d(width_bottom/2+startx-10, starty+height+10);
    glVertex2d(width_bottom/2+startx, starty+height-10);
    glEnd();
    glFlush();
}

void road() {
    glColor3f(1, 0.1, 0.1);
    glLineWidth(10);
    glBegin(GL_LINES);

    glVertex2d(0, 100);
    glVertex2d(250, 450);

    glVertex2d(480, 450);
    glVertex2d(720, 100);

    glVertex2d(250, 450);
    glVertex2d(480, 450);

    glEnd();
    glFlush();
}

void mountains() {
    glColor3f(0.96, 0.56, 0.49);
    // glBegin(GL_POLYGON);
    glBegin(GL_POLYGON);
    /* Mountain 1 */
    glVertex2d(0, 450);
    glVertex2d(150, 720);
    glVertex2d(150, 720);
    glVertex2d(300, 450);
    glEnd();

    /* Mountain 2 */
    glBegin(GL_POLYGON);
    glVertex2d(200, 450);
    glVertex2d(350, 650);
    glVertex2d(350, 650);
    glVertex2d(500, 450);
    glEnd();

    /* Mountain 3 */
    glBegin(GL_POLYGON);
    glVertex2d(375, 450);
    glVertex2d(450, 700);
    glVertex2d(450, 700);
    glVertex2d(525, 450);
    glEnd();

    /* Mountain 4 */
    glBegin(GL_POLYGON);
    glVertex2d(475, 450);
    glVertex2d(600, 680);
    glVertex2d(600, 680);
    glVertex2d(720, 450);
    glEnd();

    glFlush();
}

void play() {
    glClearColor(0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // grass();
    // road();
    // mountains();
    tree(0.5, 10, 200);
    tree(1, 100, 200);
    tree(1.5, 250, 200);
}

int main(int argc, char** argv)
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Bountry-Fill-Recursive");
    glutDisplayFunc(play);
    glViewport(0, 0, WIDTH, HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)WIDTH, 0.0, (GLdouble)HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glutMainLoop();
    return 0;
}