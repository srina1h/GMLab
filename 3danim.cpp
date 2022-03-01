#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

int increment = 1;
void initialize(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void draw_objects(int state)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (state == 0) increment = 1;
	else if (state == 10) increment = -1;

	glLoadIdentity();
	gluLookAt(0.0, 1.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	GLfloat ball_color[] = {
		0.59,
		0.1,
		0.55,
		1.0
	};

	double scale = 0.15;
	glTranslatef(-1, 2.5 + scale * state, 0);
	/*glutSolidSphere(0.5, 10, 10);*/
	/*glutSolidCube(1.0);*/
	/*glutSolidTeapot(0.7);*/
	glutSolidTorus(2.0, 4.0, 5, 10);
	glPopMatrix();
	glutSwapBuffers();

	glutTimerFunc(1000 / 60, draw_objects, state + increment);
}

void threedanim() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutTimerFunc(1000 / 60, draw_objects, 0);
}

void reshape(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 20);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D Animations");
	initialize();
	glutDisplayFunc(threedanim);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}