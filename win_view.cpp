#include<GL/glut.h>
#include<iostream>
#include<cmath>
using namespace std;
#define WXmin 10.0
#define WXmax 410.0
#define WYmin 10.0
#define WYmax 370.0
#define VXmin 420.0
#define VXmax 620.0
#define VYmin 10.0
#define VYmax 190.0
double a[3][1], b[3][1], c[3][1];
double a1[3][1], b1[3][1], c1[3][1];
void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(10);
	glMatrixMode(GL_PROJECTION);
	/*glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void drawWindowAndViewport() {
	glBegin(GL_LINE_LOOP);
	glColor4f(0.9f, 0.9f, 0.1f, 0.5f);
	glVertex2d(WXmin, WYmin);
	glVertex2d(WXmax, WYmin);
	glVertex2d(WXmax, WYmax);
	glVertex2d(WXmin, WYmax);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor4f(0.5f, 0.3f, 0.2f, 0.5f);
	glVertex2d(VXmin, VYmin);
	glVertex2d(VXmax, VYmin);
	glVertex2d(VXmax, VYmax);
	glVertex2d(VXmin, VYmax);
	glEnd();
}
void convertViewPortTriangle() {
	memset(a1, 0, sizeof(a1));
	memset(b1, 0, sizeof(b1));
	memset(c1, 0, sizeof(c1));
	a1[2][0] = b1[2][0] = c1[2][0] = 1;
	double WXRange = WXmax - WXmin, WYRange = WYmax - WYmin;
	double VXRange = VXmax - VXmin, VYRange = VYmax - VYmin;
	a1[0][0] = VXmin + VXRange * (a[0][0] - WXmin) / WXRange;
	b1[0][0] = VXmin + VXRange * (b[0][0] - WXmin) / WXRange;
	c1[0][0] = VXmin + VXRange * (c[0][0] - WXmin) / WXRange;
	a1[1][0] = VYmin + VYRange * (a[1][0] - WYmin) / WYRange;
	b1[1][0] = VYmin + VYRange * (b[1][0] - WYmin) / WYRange;
	c1[1][0] = VYmin + VYRange * (c[1][0] - WYmin) / WYRange;
}
void drawTriangle(double a[3][1], double b[3][1], double c[3][1], int s = 0) {
	glBegin(GL_TRIANGLES);
	if (s)
		glColor4f(0.5f, 0.3f, 0.2f, 0.5f);
	else
		glColor4f(0.9f, 0.9f, 0.1f, 0.5f);
	glVertex2d(a[0][0], a[1][0]);
	glVertex2d(b[0][0], b[1][0]);
	glVertex2d(c[0][0], c[1][0]);
	glEnd();
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawWindowAndViewport();
	drawTriangle(a, b, c);
	convertViewPortTriangle();
	cout << a1[0][0] << ',' << a1[1][0] << ' ' << b1[0][0] << ',' << b1[1][0] << ' ' << c1[0][0] << ',' << c1[1][0] << ' ';
	drawTriangle(a1, b1, c1, 1);
	glFlush();
}
int main(int argc, char** argv) {
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(c, 0, sizeof(c));
	a[0][0] = 40;
	a[1][0] = 240;
	a[2][0] = 1;
	b[0][0] = 40;
	b[1][0] = 40;
	b[2][0] = 1;
	c[0][0] = 330;
	c[1][0] = 150;
	c[2][0] = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Experiment 6b");
	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}
