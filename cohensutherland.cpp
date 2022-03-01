#include<iostream>
#include<gl/glut.h>
#include<math.h>
using namespace std;
double Xmin, Ymin, Xmax, Ymax;
double x1, yone, x2, y2;
void myInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3d(1.0, 0.0, 0.0);
	glPointSize(2.0);
	glLineWidth(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
int regioncode(int x, int y) {
	int code = 0;
	if (y > Ymax)
		code = 8; // above
	if (y < Ymin)
		code = 4; // below
	if (x > Xmax)
		code += 2; // to right
	if (x < Xmin)
		code += 1; // to left
	return code;
}
void CohenSutherland() {
	int c1 = regioncode(x1, yone);
	int c2 = regioncode(x2, y2);
	float m = (y2 - yone) / (x2 - x1);
	int c = c1;
	double a = x1;
	double b = yone;
	double x, y;
	if (c == 0) {
		c = c2;
		a = x2;
		b = y2;
	}
	// checking trivial accept, then no need to clip
	if ((c1 | c2) > 0) {
		if ((c1 & c2) > 0)
			exit(0); // trivial reject, if points are completely outside
		if ((c & 4) > 0) {
			y = Ymin;
			x = a + (1.0) / m * (y - b);
		}
		if (c == c1) {
			x1 = x;
			yone = y;
			c1 = regioncode(x1, yone);
		}
		else {
			x2 = x;
			y2 = y;
			c1 = regioncode(x2, y2);
		}
	}
}
void mydisp() {
	glClear(GL_COLOR_BUFFER_BIT);
	// Drawing the clipping window
	glBegin(GL_LINE_LOOP);
	glColor3d(1.0, 0.0, 0.0);
	glVertex2d(Xmin, Ymin);
	glVertex2d(Xmin, Ymax);
	glVertex2d(Xmax, Ymax);
	glVertex2d(Xmax, Ymin);
	glEnd();
	// Drawing unclipped line
	glBegin(GL_LINES);
	glColor3d(0.0, 0.0, 1.0);
	glVertex2d(x1, yone);
	glVertex2d(x2, y2);
	glEnd();
	glFlush();
}
void keypress(unsigned char key, int x, int y) {
	if (key == 'c') {
		CohenSutherland(); // clipping the line
		glClear(GL_COLOR_BUFFER_BIT);
		// Drawing the clipping window
		glBegin(GL_LINE_LOOP);
		glColor3d(1.0, 0.0, 0.0);
		glVertex2d(Xmin, Ymin);
		glVertex2d(Xmin, Ymax);
		glVertex2d(Xmax, Ymax);
		glVertex2d(Xmax, Ymin);
		glEnd();
		// Drawing clipped line
		glBegin(GL_LINES);
		glColor3d(1.0, 0.0, 1.0);
		glVertex2d(x1, yone);
		glVertex2d(x2, y2);
		glEnd();
		glFlush();
	}
}
void main(int argc, char** argv) {
	// Window parameters:
	Xmin = 300.0;
	Ymin = 100.0;
	Xmax = 500.0;
	Ymax = 300.0;
	// Line Paramaeters
	x1 = 300.0;
	yone = 50.0;
	x2 = 550.0;
	y2 = 350.0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Cohen Sutherland Line Clipping Algorithm");
	myInit();
	glutDisplayFunc(mydisp);
	glutKeyboardFunc(keypress);
	glutMainLoop();
}