#include<gl/glut.h>
#include<iostream>
#include<math.h>
using namespace std;
#define pi 3.14159265358979323846264338327950288419716939937510582
typedef struct point {
	double x, y, z, h;
}point;
typedef struct face {
	point v[4];
}face;
typedef struct cuboid {
	point v[8];
	face faces[6];
}cuboid;
int assignlist[6][4] = { {0, 1, 3, 2}, {0, 4, 5, 1}, {0, 4, 6, 2},
{4, 5, 7, 6}, {2, 6, 7, 3}, {1, 5, 7, 3}
};
float colors[6][3] = { {0, 1, 0}, {1, 0, 0}, {0, 0, 1},
{1, 1, 0}, {0, 1, 1}, {1, 0, 1}
};
double tmat[4][4];
bool tflag = false;
cuboid cuboid, tcuboid;
cuboid initcuboid() {
	cuboid cuboid;
	double po[8][3] = { {-25, 25, 0}, {25, 25, 0}, {-25, -25, 0}, {25,
	-25, 0},
	{-25, 25, 50}, {25, 25, 50}, {-25, -25, 50}, {25,
	-25, 50}
	};
	for (int i = 0; i < 8; i++) {
		cuboid.v[i].x = po[i][0];
		cuboid.v[i].y = po[i][1];
		cuboid.v[i].z = po[i][2];
		cuboid.v[i].h = 1;
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cuboid.faces[i].v[j] = cuboid.v[assignlist[i][j]];
		}
	}
	return cuboid;
}
void myinit() {
	glclearcolor(1.0, 1.0, 1.0, 0.0);
	glcolor3f(0, 0, 0);
	glenable(gl_blend);
	glblendfunc(gl_src_alpha, gl_one_minus_src_alpha);
	glloadidentity();
	glortho(-200, 200, -200, 200, -200, 200);
	glenable(gl_depth_test);
}
void disp() {
	glrotatef(30, 1, 0, 0);
	glrotatef(30, 0, 1, 0);
}
void transformcuboid() {
	tflag = true;
	for (int i = 0; i < 8; i++) {
		cout << cuboid.v[i].x << " " << cuboid.v[i].y << " "<<cuboid.v[i].z<<"\n";
	}
	cout << "\n\n";
	for (int p = 0; p < 8; p++) {
		double pnt[4][1], pnt1[4][1];
		pnt[0][0] = cuboid.v[p].x;
		pnt[1][0] = cuboid.v[p].y;
		pnt[2][0] = cuboid.v[p].z;
		pnt[3][0] = cuboid.v[p].h;
		memset(pnt1, 0, sizeof(pnt1));
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 1; j++) {
				for (int k = 0; k < 4; k++) {
					pnt1[i][j] += tmat[i][k] * pnt[k][j];
				}
			}
		}
		tcuboid.v[p].x = pnt1[0][0];
		tcuboid.v[p].y = pnt1[1][0];
		tcuboid.v[p].z = pnt1[2][0];
		tcuboid.v[p].h = pnt1[3][0];
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			tcuboid.faces[i].v[j] =
				tcuboid.v[assignlist[i][j]];
		}
	}
	for (int i = 0; i < 8; i++) {
		cout << tcuboid.v[i].x << " " << tcuboid.v[i].y << " "<<tcuboid.v[i].z<<"\n";
	}
	glutpostredisplay();
}
void gettransformmatrix() {
	memset(tmat, 0, sizeof(tmat));
	tmat[0][0] = tmat[1][1] = tmat[2][2] = tmat[3][3] = 1;
	int ch;
	cout << "menu:\n\t1.translation\n\t2.rotation\n\t3.scaling\n\tchoice:";
	cin >> ch;
	switch (ch) {
	case 1:
		cout << "enter translation parameters: ";
		cin >> tmat[0][3] >> tmat[1][3] >> tmat[2][3];
		break;
	case 2:
		cout << "enter degree of rotation: ";
		double deg;
		cin >> deg;
		deg = deg * pi / 180;
		tmat[0][0] = cos(deg);
		tmat[0][1] = -sin(deg);
		tmat[1][1] = tmat[0][0];
		tmat[1][0] = -tmat[0][1];
		break;
	case 3:
		cout << "enter scaling parameters: ";
		cin >> tmat[0][0] >> tmat[1][1] >> tmat[2][2];
		break;
	default: cout << "incorrect choice\n";
	}
	transformcuboid();
}
void displaycuboid(cuboid cuboid, double alpha = 0.6) {
	for (int i = 0; i < 6; i++) {
		glcolor4f(colors[i][0], colors[i][1], colors[i][2], alpha);
		glbegin(gl_polygon);
		for (int j = 0; j < 4; j++) {
			glvertex3d(cuboid.faces[i].v[j].x, cuboid.faces[i].v[j].y, cuboid.faces[i].v
				[j].z);
		}
		glend();
	}
}
void mydisplay() {
	glclear(gl_color_buffer_bit | gl_depth_buffer_bit);
	glcolor4f(0, 0, 0, 1);
	glbegin(gl_lines);
	glvertex3d(300, 0, 0);
	glvertex3d(-300, 0, 0);
	glend();
	glbegin(gl_lines);
	glvertex3d(0, 300, 0);
	glvertex3d(0, -300, 0);
	glend();
	glbegin(gl_lines);
	glvertex3d(0, 0, 300);
	glvertex3d(0, 0, -300);
	glend();
	displaycuboid(cuboid);
	if (tflag)displaycuboid(tcuboid, 1);
	glflush();
	gettransformmatrix();
}
int main(int argc, char** argv) {
	cuboid = initcuboid();
	glutinit(&argc, argv);
	glutinitdisplaymode(glut_single | glut_rgb | glut_depth);
	glutinitwindowsize(960, 960);
	glutinitwindowposition(0, 0);
	glutcreatewindow("3d transformations");
	myinit();
	disp();
	glutdisplayfunc(mydisplay);
	glutmainloop();
}
