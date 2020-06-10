#include "gl/glut.h"
#include <iostream>
#include <math.h>
using namespace std;

GLfloat xb1 = 1, yb1 = 1;
GLfloat xb2 = 0, yb2 = 0;

static void display() {
    float theta, x, y, pi = 3.141592653589793;
	int i = -1;

    glClearColor(0.9, 0.5, 0.05, 0); // portokali gia to xoro ekso apo to gipedo
	glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0.75, 0); // prasino gia to gipedo
	glRectf(-69, -54, 69, 54); // to prasino orthogonio mesa sto opoio tha sxediastei to gipedo

    glColor3f(1, 1, 1); // aspro gia tis grammes kai tin mpala

    do {
        glBegin(GL_LINE_LOOP); // i aristerri perioxi tin proti fora pou trexei o vrogxos
        glVertex2f(i * 60, -45);
        glVertex2f(0, -45);
        glVertex2f(0, 45);
        glVertex2f(i * 60, 45);
        glEnd();

        glBegin(GL_LINE_LOOP); // i aristeri megali perioxi tin proti fora pou trexei o vrogxos
        glVertex2f(i * 60, -20.15);
        glVertex2f(i * 43.5, -20.15);
        glVertex2f(i * 43.5, 20.15);
        glVertex2f(i * 60, 20.15);
        glEnd();

        glBegin(GL_LINE_LOOP); // i aristeri mikri perioxi tin proti fora pou trexei o vrogxos
        glVertex2f(i * 60, -9.15);
        glVertex2f(i * 54.5, -9.15);
        glVertex2f(i * 54.5, 9.15);
        glVertex2f(i * 60, 9.15);
        glEnd();

        theta = -22 * pi/75;
        glBegin(GL_LINE_LOOP); // to deksi imikiklio ekso apo tin megali perioxi tin proti fora pou trexei o vrogxos
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
    glBegin(GL_LINE_LOOP); // i sentra
    while(theta <= 2*pi){
        x = 9.15 * cos(theta);
        y = 9.15 * sin(theta);
        glVertex2f(x, y);
        theta += 2*pi/64;
    }
    glEnd();

    theta = 0;
    glBegin(GL_POLYGON); // i mpala
    while(theta <= 2*pi){
        xb1 = cos(theta);
        yb1 = sin(theta);
        glVertex2f(xb1 + xb2, yb1 + yb2);
        theta += 2*pi/64;
    }
    glEnd();
    glFlush();
}

void specialKeys(int key, int a, int b) {
	if (key == GLUT_KEY_UP) {
		yb1++;
		yb2++;
	}
	if (key == GLUT_KEY_DOWN) {
		yb1--;
		yb2--;
	}
	if (key == GLUT_KEY_LEFT) {
		xb1--;
		xb2--;
	}
	if (key == GLUT_KEY_RIGHT) {
		xb1++;
		xb2++;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1080, 1080);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow(argv[0]);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-69, 69, -69, 69);
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutMainLoop();

	return 0;
}
