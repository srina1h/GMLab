#include<iostream>
#include<gl/glut.h>
#include<math.h>

void bresenham(double x0, double y0, double x1, double y1) {
	double dx = x1 - x0;
	double dy = y1 - y0;

	int incx = dx > 0 ? 1 : -1;
	int incy = dy > 0 ? 1 : -1;

	if (dx > dy) {
		glBegin(GL_POINTS);
		double pk = 2 * dy - dx;
		double x = x0;
		double y = y0;
		glVertex2d(ceill(x), ceill(y));
		for (int i = 0; i < dx; i++) {
			x++;
			if (pk < 0) {
				pk += 2*dy;
			}
			else {
				pk += 2 * dy - 2 * dx;
				y++;
			}
			glVertex2d(x, y);
		}
		glEnd();
	}
	else {
		glBegin(GL_POINTS);
		double pk = 2 * dx - dy;
		double x = x0;
		double y = y0;
		glVertex2d(ceill(x), ceill(y));
		for (int i = 0; i < dy; i++) {
			y++;
			if (pk < 0) {
				pk += 2 * dx;
			}
			else {
				pk += 2 * dx - 2 * dy;
				x++;
			}
			glVertex2d(x, y);
		}
		glEnd();
		glFlush();
	}
}

void plotAll(double xc, double yc, double x, double y) {
	glBegin(GL_POINTS);
	glVertex2d(xc + x, yc + y);
	glVertex2d(xc + x, yc - y);
	glVertex2d(xc - x, yc + y);
	glVertex2d(xc - x, yc - y);

	glVertex2d(xc + y, yc + x);
	glVertex2d(xc + y, yc - x);
	glVertex2d(xc - y, yc + x);
	glVertex2d(xc - y, yc - x);
	glEnd();
	glFlush();
}

void midpointCircle(double r, double xc, double yc) {
	double p0 = 5 / 4 - r;
	double x = 0;
	double y = r;
	plotAll(xc, yc, x, y);
	double pk = p0;
	while (x < y) {
		x++;
		if (pk < 0) {
			pk += 2 * x + 1;
		}
		else {
			pk += 2 * x - 2 * y + 1;
			y--;
		}
		plotAll(xc, yc, x, y);
	}
}

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3d(1.0, 0.0, 0.0);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void myDisp() {
	bresenham(100, 100, 200, 200);
	midpointCircle(50, 400, 400);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("line and circle");
	myInit();
	glutDisplayFunc(myDisp);
	glutMainLoop();
	return 1;
}