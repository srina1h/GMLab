#include<iostream>
#include<gl/glut.h>
#include<math.h>

float rotateX, rotateY;

bool isperspective = true;
bool isscale = false;

void mydisp()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	if (isperspective) {
		gluPerspective(120, 1, 0.5, 10);
		gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
	}
	else {
		glOrtho(-2, 2, -2, 2, -2, 2);
	}
	glRotatef(rotateX, 1, 0, 0);
	glRotatef(rotateY, 0, 1, 0);

	if(isscale)
		glScalef(2.0, 2.0, 2.0);

	glColor3d(0.0, 1.0, 0.0);
	glLineWidth(2.0);
	glutWireCone(0.5, 0.5, 10, 5);
	
	glPopMatrix();
	glFlush();
}

void timer(int x) {
	rotateX += 50;
	rotateY += 50;
	glutPostRedisplay();
	glutTimerFunc(1000, timer, 10);
}

void keypress(unsigned char c, int x, int y) {
	switch (c) {
		case 32:
			isperspective = false;
			break;
		case 'd':
			rotateX += 50;
			break;
		case 'a':
			rotateX -= 50;
			break;
		case 'w':
			rotateY += 50;
			break;
		case 's':
			rotateY -= 50;
			break;
		case 'g':
			isscale = true;
			break;
	}
	glutPostRedisplay();
}

void main(int argc, char** argv) {
	rotateX = 10;
	rotateY = 10;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("3D objects");
	glutDisplayFunc(mydisp);
	glutKeyboardFunc(keypress);
	//timer(0);
	glutMainLoop();
}