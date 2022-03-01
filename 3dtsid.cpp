#include<GL/glut.h>
#include<vector>
#include<cmath>
#include<iostream>

using namespace std;

double ORIGINX = 0.0, ORIGINY = 0.0;
double XMIN = 0, YMIN = 0, XMAX = 600, YMAX = 600;

void myInit() {
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.f, 0.f, 0.f, 1.f);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("Error: %s\n", gluErrorString(error));
	}
}

void plotObj(vector<vector<double>> points) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < points.size(); i++)
		glVertex3d(points[i][0], points[i][1], points[i][2]);
	glEnd();
}

vector<double> multiply(vector<vector<double>> mat, vector<double> vec) {
	vector<double> res(vec.size(), 0.0);
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[0].size(); j++) {
			res[i] += mat[i][j] * vec[j];
		}
	}
	return res;
}

void drawAxes() {
	glBegin(GL_LINES);
	glVertex2f(-250, 0);
	glVertex2f(250, 0);
	glVertex2f(0, -250);
	glVertex2f(0, 250);
	glEnd();
}


void translate(vector<vector<double>> points, double tx, double ty, double tz) {
	vector<vector<double>> mat = {
		{1, 0, 0, tx},
		{0, 1, 0, ty},
		{0, 0, 1, tz},
		{0, 0, 0,  1}
	};
	for (int i = 0; i < points.size(); i++)
		points[i] = multiply(mat, points[i]);
	plotObj(points);
}

void scale(vector<vector<double>> points, double sx, double sy, double sz) {
	vector<vector<double>> mat = {
		{sx,  0,  0, 0},
		{ 0, sy,  0, 0},
		{ 0,  0, sz, 0},
		{ 0,  0,  0, 1}
	};
	for (int i = 0; i < points.size(); i++)
		points[i] = multiply(mat, points[i]);
	plotObj(points);
}

void rotateZ(vector<vector<double>> points, double theta) {
	double c = cos(theta * 3.14159 / 180), s = sin(theta * 3.14159 / 180);
	vector<vector<double>> mat = {
		{ c,  -s,  0, 0},
		{ s,   c,  0, 0},
		{ 0,   0,  1, 0},
		{ 0,   0,  0, 1}
	};
	for (int i = 0; i < points.size(); i++)
		points[i] = multiply(mat, points[i]);
	plotObj(points);
}

void rotateY(vector<vector<double>> points, double theta) {
	double c = cos(theta * 3.14159 / 180), s = sin(theta * 3.14159 / 180);
	vector<vector<double>> mat = {
		{ c,   0,  s, 0},
		{ 0,   1,  0, 0},
		{-s,   0,  c, 0},
		{ 0,   0,  0, 1}
	};
	for (int i = 0; i < points.size(); i++)
		points[i] = multiply(mat, points[i]);
	plotObj(points);
}

void rotateX(vector<vector<double>> points, double theta) {
	double c = cos(theta * 3.14159 / 180), s = sin(theta * 3.14159 / 180);
	vector<vector<double>> mat = {
		{ 1,   0,   0, 0},
		{ 0,   c,  -s, 0},
		{ 0,   s,   c, 0},
		{ 0,   0,   0, 1}
	};
	for (int i = 0; i < points.size(); i++)
		points[i] = multiply(mat, points[i]);
	plotObj(points);
}


void plot() {
	glTranslatef(0, 0, -30);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);

	int option;
	cout << "1. Translate\n2. Scale\n3. Rotate\n";
	cout << "Enter option (1-3): " << endl;
	cin >> option;

	drawAxes();
	vector<vector<vector<double>>> pointsList = {
		{{-5, -5, 5, 1}, {5, -5, 5, 1}, {5, 5, 5, 1}, {-5, 5, 5, 1}},
		{{-5, -5, -5, 1}, {5, -5, -5, 1}, {5, 5, -5, 1}, {-5, 5, -5, 1}},
		{{-5, 5, -5, 1}, {5, 5, -5, 1}, {5, 5, 5, 1}, {-5, 5, 5, 1}},
		{{-5, -5, -5, 1}, {5, -5, -5, 1}, {5, -5, 5, 1}, {-5, -5, 5, 1}},
		{{5, -5, -5, 1}, {5, -5, 5, 1}, {5, 5, 5, 1}, {5, 5, -5, 1}},
		{{-5, -5, -5, 1}, {-5, -5, 5, 1}, {-5, 5, 5, 1}, {-5, 5, -5, 1}},
	};
	glColor3f(0.0f, 1.0f, 0.0f);
	for (vector<vector<double>> points : pointsList)
		plotObj(points);

	glColor3f(1.0f, 1.0f, 1.0f);
	if (option == 1) {
		double tx, ty, tz;
		cout << "Enter tx, ty, tz: " << endl;
		cin >> tx >> ty >> tz;
		for (vector<vector<double>> points : pointsList)
			translate(points, tx, ty, tz);
	}
	else if (option == 2) {
		double sx, sy, sz;
		cout << "Enter sx, sy, sz: " << endl;
		cin >> sx >> sy >> sz;
		for (vector<vector<double>> points : pointsList)
			scale(points, sx, sy, sz);
	}
	else if (option == 3) {
		double theta; char axis;
		cout << "Enter angle: " << endl;
		cin >> theta;
		cout << "Enter axis: " << endl;
		cin >> axis;
		if (axis == 'x') {
			for (vector<vector<double>> points : pointsList)
				rotateX(points, theta);
		}
		else if (axis == 'y') {
			for (vector<vector<double>> points : pointsList)
				rotateY(points, theta);
		}
		else if (axis == 'z') {
			for (vector<vector<double>> points : pointsList)
				rotateZ(points, theta);
		}
	}

	glFlush();
}

void runLoop(int val) {
	plot();
	glutTimerFunc(1000 / 60, runLoop, val);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutCreateWindow("3D Transformations: ");
	myInit();
	glutDisplayFunc(plot);
	glutTimerFunc(1000 / 60, runLoop, 0);
	glutMainLoop();
	return 1;
}