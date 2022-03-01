#include<iostream>
#include<gl/glut.h>
#include<math.h>

using namespace std;

float a1, b1, a2, b2;
float xmin, xmax, ymin, ymax;

int c1, c2;

int regioncode(float x, float y)
{
	int code = 0;
	if (y > ymin) {
		code = 8;
	}
	if (y < ymin) {
		code = 4;
	}
	if (x > xmax) {
		code += 2;
	}
	if (x < xmin) {
		code += 1;
	}
	return code;
}

void cohenSutherland()
{
	c1 = regioncode(a1, b1);
	c2 = regioncode(a2, b2);

	float m = (b2 - b1) / (a2 - a1);

	// check if needs to be clipped , i.e both have region code other than 0000
	if ((c1 | c2) > 0) {
		if ((c1 & c2) > 0) {
			exit(0); // no need clipping out of bounds
		}

		float ai = a1;
		float bi = b1;
		int c = c1;
		
		if (c == 0) {
			ai = a2;
			bi = b2;
			c = c2;
		}
		
		float a, b;
		
		// clipping bottom
		if ((c & 4) > 0) {
			b = ymin;
			a = (1.0f / m) * (b - bi) + ai;
		}
		if (c == c1) {
			a1 = a;
			b1 = b;
			c1 = regioncode(a1, b1);
		}
		else{
			a2 = a;
			b2 = b;
			c2 = regioncode(a2, b2);
		}
	}

}

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3d(1.0, 0.0, 0.0);
	glPointSize(2.0);
	glLineWidth(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}



void clipLine(unsigned char c, int x, int y)
{
	if (c == 'c') {
		cohenSutherland();

		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_LINE_LOOP);
		glColor3d(1.0, 0.0, 0.0);
		glVertex2d(xmin, ymin);
		glVertex2d(xmin, ymax);
		glVertex2d(xmax, ymax);
		glVertex2d(xmax, ymin);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2d(a1, b1);
		glVertex2d(a2, b2);
		glEnd();
	}

}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	// Drawing the clipping window
	glBegin(GL_LINE_LOOP);
	glColor3d(1.0, 0.0, 0.0);
	glVertex2d(xmin, ymin);
	glVertex2d(xmin, ymax);
	glVertex2d(xmax, ymax);
	glVertex2d(xmax, ymin);
	glEnd();
	// Drawing unclipped line
	glBegin(GL_LINES);
	glColor3d(0.0, 0.0, 1.0);
	glVertex2d(a1, b1);
	glVertex2d(a2, b2);
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	xmin = 300;
	xmax = 500;
	ymin = 100;
	ymax = 300;

	a1 = 300;
	b1 = 50;
	a2 = 550;
	b2 = 350;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Cohen Sutherland Line Clipping");
	myInit();
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(clipLine);
	glutMainLoop();
	return 1;
}