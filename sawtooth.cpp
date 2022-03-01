#include<iostream>
#include<vector>
#include<GL/glut.h>
#include<cmath>
using namespace std;
double a[3][1], b[3][1], c[3][1];
double aw[3][1], bw[3][1], cw[3][1];
double a1[3][1], b1[3][1], c1[3][1];
double a2[3][1], b2[3][1], c2[3][1];
double t[3][3];
void drawTriangle(double a[3][1], double b[3][1], double
	c[3][1], int transformed = 0) {
	a[0][0] += 960;
	b[0][0] += 960;
	c[0][0] += 960;
	a[1][0] += 540;
	b[1][0] += 540;
	c[1][0] += 540;
	glBegin(GL_TRIANGLES);
	if (transformed == 1)
		glColor4f(0.1f, 0.3f, 0.9f, 0.5f);
	else
		glColor4f(0.9f, 0.2f, 0.1f, 0.5f);
	glVertex2d(a[0][0], a[1][0]);
	glVertex2d(b[0][0], b[1][0]);
	glVertex2d(c[0][0], c[1][0]);
	glEnd();
}
void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(2);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1920.0, 0.0, 1080.0);
}
void transformObject() {
	memset(a1, 0, sizeof(a1));
	memset(b1, 0, sizeof(b1));
	memset(c1, 0, sizeof(c1));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 1; j++) {
			for (int k = 0; k < 3; k++) {
				a1[i][j] += t[i][k] * a[k][j];
				b1[i][j] += t[i][k] * b[k][j];
				c1[i][j] += t[i][k] * c[k][j];
			}
		}
	}
	for (int i = 0; i < 3; i++)
		a2[i][0] = a1[i][0];
	for (int i = 0; i < 3; i++)
		b2[i][0] = b1[i][0];
	for (int i = 0; i < 3; i++)
		c2[i][0] = c1[i][0];
	a2[0][0] += 300;
	b2[0][0] += 300;
	c2[0][0] += 300;
}
void shearObject(double s, double ref) {
	memset(t, 0, sizeof(t));
	t[0][0] = t[1][1] = t[2][2] = 1;
	t[0][1] = s, t[0][2] = -s * ref;
}
void myDisplay() {
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2d(0, 540);
	glVertex2d(1920, 540);
	glVertex2d(960, 0);
	glVertex2d(960, 1080);
	glEnd();
	drawTriangle(a, b, c);
	drawTriangle(aw, bw, cw);
	drawTriangle(a1, b1, c1, 1);
	drawTriangle(a2, b2, c2, 1);
	glFlush();
}
int main(int argc, char** argv) {
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(c, 0, sizeof(c));
	memset(t, 0, sizeof(t));
	a[0][0] = 0;
	a[1][0] = 0;
	b[0][0] = 300;
	b[1][0] = 0;
	c[0][0] = 150;
	c[1][0] = 150;
	a[2][0] = b[2][0] = c[2][0] = 1;
	for (int i = 0; i < 3; i++)
		aw[i][0] = a[i][0];
	for (int i = 0; i < 3; i++)
		bw[i][0] = b[i][0];
	for (int i = 0; i < 3; i++)
		cw[i][0] = c[i][0];
	aw[0][0] += 300;
	bw[0][0] += 300;
	cw[0][0] += 300;
	double sh, ref;
	sh = 1;
	ref = 300;
	shearObject(sh, ref);
	transformObject();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Question 2");
	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
