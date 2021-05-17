#include "gl/glut.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>

using namespace std;

int score1 = 0, score2 = 0, score_check;
GLfloat xb1 = 1, yb1 = 1;
GLfloat xb2 = 0, yb2 = 0;

void renderbitmap(float x, float y, void *font, char *string) {
    char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
    }
}

void introscreen() {
    glColor3f(1, 1, 1);
    char buf[10];
    sprintf(buf, "%d  -  %d", score1, score2);
    renderbitmap(-7, 60, GLUT_BITMAP_TIMES_ROMAN_24, buf);
}

void init() {
    glOrtho(-80, 80, -80, 80, -80, 80);
}

void display() {
    float theta, x, y, pi = 3.141592653589793;
    int i = -1;

    glClearColor(0.9, 0.5, 0.05, 0); // orange for the space outside of the field
    glClear(GL_COLOR_BUFFER_BIT);

    if (xb2 < 61 && xb2 > -61) {
        glColor3f(0, 0.75, 0); // green for the field
    }
    else {
        glColor3f(1, 0, 0); // red field when a goal is scored
    }
	glRectf(-69, -54, 69, 54); // the green rectangular in which the field will be designed

    glColor3f(1, 1, 1); // white color for the filed lines and the ball

    do {
        glBegin(GL_LINE_LOOP); // the left side of the filed will be created the first time this loop will be executed
        glVertex2f(i * 60, -45);
        glVertex2f(0, -45);
        glVertex2f(0, 45);
        glVertex2f(i * 60, 45);
        glEnd();

        glBegin(GL_LINE_LOOP); // the left penalty area will be created the first time this loop will be executed
        glVertex2f(i * 60, -20.15);
        glVertex2f(i * 43.5, -20.15);
        glVertex2f(i * 43.5, 20.15);
        glVertex2f(i * 60, 20.15);
        glEnd();

        glBegin(GL_LINE_LOOP); // the left goal area will be created the first time this loop will be executed
        glVertex2f(i * 60, -9.15);
        glVertex2f(i * 54.5, -9.15);
        glVertex2f(i * 54.5, 9.15);
        glVertex2f(i * 60, 9.15);
        glEnd();

        glBegin(GL_LINE_LOOP); // the left goalkeeper's area will be created the first time this loop will be executed
        glVertex2f(i * 62.44, -3.65);
        glVertex2f(i * 60, -3.65);
        glVertex2f(i * 60, 3.65);
        glVertex2f(i * 62.44, 3.65);
        glEnd();

        theta = -22 * pi/75;
        glBegin(GL_LINE_LOOP); // the left penalty arc will be created the first time this loop will be executed
        while(theta <= 22 * pi/75){
            x = 9.15 * cos(theta);
            y = 9.15 * sin(theta);
            glVertex2f(i * (x - 49), y);
            theta += 2*pi/256;
        }
        glEnd();

        i = -i;
    }
    while(i > 0);

    theta = 0;
    glBegin(GL_LINE_LOOP); // center
    while(theta <= 2*pi){
        x = 9.15 * cos(theta);
        y = 9.15 * sin(theta);
        glVertex2f(x, y);
        theta += 2*pi/64;
    }
    glEnd();

    theta = 0;
    glBegin(GL_POLYGON); // ball
    while(theta <= 2*pi){
        xb1 = cos(theta);
        yb1 = sin(theta);
        glVertex2f(xb1 + xb2, yb1 + yb2);
        theta += 2*pi/64;
    }
    glEnd();
    introscreen();
    glFlush();
}

void specialKeys(int key, int a, int b) {
    score_check = xb2;

    if (key == GLUT_KEY_RIGHT && xb2 <= 59) {
        xb1++;
	xb2++;
    }
    else if (key == GLUT_KEY_RIGHT && xb2 <= 61.44 && yb2 <= 3.65 && yb2 >= -3.65) {
        xb1++;
        xb2++;
    }

    if (key == GLUT_KEY_LEFT && xb2 >= -59) {
        xb1--;
	xb2--;
    }
    else if (key == GLUT_KEY_LEFT && xb2 >= -61.44 && yb2 <= 3.65 && yb2 >= -3.65) {
        xb1--;
	xb2--;
    }

    if (key == GLUT_KEY_UP && yb2 <= 44 && xb2 <= 60.44 && xb2 >= -60.44) {
	yb1++;
	yb2++;
    }
    else if (key == GLUT_KEY_UP && yb2 <= 2.65 && xb2 <= -59) {
	yb1++;
	yb2++;
    }
    else if (key == GLUT_KEY_UP && yb2 <= 2.65 && xb2 >= 59) {
        yb1++;
        yb2++;
    }

    if (key == GLUT_KEY_DOWN && yb2 >= -44 && xb2 <= 60.44 && xb2 >= -60.44) {
        yb1--;
        yb2--;
    }
    else if (key == GLUT_KEY_DOWN && yb2 >= -2.65 && xb2 <= -59) {
	yb1--;
	yb2--;
    }
    else if (key == GLUT_KEY_DOWN && yb2 >= -2.65 && xb2 >= 59) {
        yb1--;
        yb2--;
    }

    if (score_check == 60 && xb2 == 61) {
        score1++;
    }
    
    if (score_check == -60 && xb2 == -61) {
        score2++;
    }
    
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(744, 744);
    glutInitWindowPosition(600, 100);
    glutCreateWindow(argv[0]);

    init();
    glutSpecialFunc(specialKeys);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
