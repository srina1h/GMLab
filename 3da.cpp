#include<iostream>
#include<stdio.h>
#include<GL/glut.h>
using namespace std;

double rotateX = 0, rotateY = 0;

void myDisplay() {

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    gluPerspective(120, 1, 0.1, 50);

    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
    glRotatef(rotateX, 1, 0, 0);
    glRotatef(rotateY, 0, 1, 0);

    glColor3f(0.4, 0.4, 0.9);
    glutSolidTorus(0.3, 0.3, 5, 5);

    glPopMatrix();

    glFlush();
}

static void Timer(int v) {
    rotateX += 5;

    glutPostRedisplay();
    glutTimerFunc(100, Timer, 0);

}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("3d animation");
    glutDisplayFunc(myDisplay);
    Timer(0);
    glutMainLoop();

    return 0;
}