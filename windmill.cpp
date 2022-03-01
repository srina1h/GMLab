#include <gl/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>

//using namespace std;

float bladea[3][1];
float bladeb[3][1];
float tm[3][3];

float degree = 5;

void myinit() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glPointSize(5.0);
	glLineWidth(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void matmul() {
	float bladeta[3][1];
	float bladetb[3][1];
	memset(bladeta, 0, sizeof(bladeta));
	memset(bladetb, 0, sizeof(bladetb));
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 1; j++)
			for (int k = 0; k < 3; k++) {
				bladeta[i][j] += tm[i][k] * bladea[k][j];
				bladetb[i][j] += tm[i][k] * bladeb[k][j];
			}
	for (int i = 0; i < 3; i++) {
		bladea[i][0] = bladeta[i][0];
		bladeb[i][0] = bladetb[i][0];
	}
}

void rotate(float deg, float x, float y){
	memset(tm, 0, sizeof(tm));
	deg = (3.14) * deg / 180;
	tm[2][2] = 1;
	tm[0][0] = cos(deg);
	tm[0][1] = -sin(deg);
	tm[0][2] = x * (1 - cos(deg)) + y * sin(deg);
	tm[1][0] = sin(deg);
	tm[1][1] = cos(deg);
	tm[1][2] = y * (1 - cos(deg)) - x * sin(deg);
	tm[2][2] = 1;

	matmul();
}

void mydisp() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	glVertex2d(250, 10);
	glVertex2d(300, 10);
	glVertex2d(300, 200);
	glVertex2d(250, 200);
	glEnd();

	std::cout << bladea[0][0] << " " << bladea[1][0]<<std::endl;
	std::cout << bladeb[0][0] << " " << bladeb[1][0]<<std::endl;

	glBegin(GL_LINES);
	glVertex2d(bladea[0][0], bladea[1][0]);
	glVertex2d(bladeb[0][0], bladeb[1][0]);
	glEnd();

	rotate(-10, 275, 200);

	std::cout << bladea[0][0] <<" "<< bladea[1][0] << std::endl;
	std::cout << bladeb[0][0] << " " << bladeb[1][0] << std::endl;

	glBegin(GL_LINES);
	glVertex2d(bladea[0][0], bladea[1][0]);
	glVertex2d(bladeb[0][0], bladeb[1][0]);
	glEnd();

	glFlush();
}

void timer(int) {

	rotate(degree, 275, 200);
	degree += 45;
	glutPostRedisplay();
	glutTimerFunc(1000, timer, 0);
}

int main(int argc, char **argv) {
	bladea[0][0] = 275;
	bladea[1][0] = 200;
	bladeb[0][0] = 275;
	bladeb[1][0] = 300;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("animated windmill");
	myinit(); 
	glutDisplayFunc(mydisp);
	timer(0);
	glutMainLoop();
}