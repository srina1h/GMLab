//#include <iostream>
//#include <gl/glut.h>
//
//using namespace std;
//
//float rotateX =0, rotateY = 0;
//
//void mydisplay() {
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	
//	glPushMatrix();
//
//	gluPerspective(120, 1, 0.5, 50);
//	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
//
//	glRotatef(rotateX, 1, 0, 0);
//	glRotatef(rotateY, 0, 1, 0);
//
//	glColor3f(1.0f, 0.0f, 0.0f);
//
//	glutSolidTorus(0.3, 0.6, 5, 50);
//
//	glPopMatrix();
//
//	glFlush();
//}
//
//static void timer(int time) {
//	rotateX += 5;
//	glutPostRedisplay();
//	glutTimerFunc(100, timer, 0);
//}
//
//int main(int argc, char ** argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowSize(640, 480);
//
//	glutCreateWindow("Nice 3D");
//	glutDisplayFunc(mydisplay);
//	timer(0);
//	glutMainLoop();
//}