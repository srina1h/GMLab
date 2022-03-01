#include <stdlib.h>
#include <gl/glut.h>
#include <iostream>
using namespace std;

int xc, yc, r;

void myinit()
{
    glclearcolor(1.0, 1.0, 1.0, 0.0);
    glcolor3f(0.4, 0.4, 0.9);
    glmatrixmode(gl_projection);
    glloadidentity();
    glpointsize(2);
    gluortho2d(-250.0, 250.0, -250.0, 250.0);
}

void plotall(int x, int y, int xc, int yc)
{
    glvertex2d(x + xc, y + yc);
    glvertex2d(x + xc, -y + yc);
    glvertex2d(-x + xc, y + yc);
    glvertex2d(-x + xc, -y + yc);

    glvertex2d(y + xc, x + yc);
    glvertex2d(y + xc, -x + yc);
    glvertex2d(-y + xc, x + yc);
    glvertex2d(-y + xc, -x + yc);
}

void circle()
{
    int x = r, y = 0, pk = 1 - r;
    glclear(gl_color_buffer_bit);
    glbegin(gl_points);
    plotall(x, y, xc, yc);
    while (x > y)
    {
        y++;

        if (pk < 0)
        {
            pk += (2 * y) + 1;
        }
        else
        {
            x--;
            pk += (2 * y) - (2 * x) + 1;
        }
        plotall(x, y, xc, yc);
    }

    glvertex2d(100, 200);
    glvertex2d(50, 200);
    glvertex2d(20, 100);
    glvertex2d(40, 100);

    glend();
    glflush();
}

int main(int argc, char* argv[])
{
    cout << "enter coordinates of line center of circle and radius xc,yc,r: ";
    cin >> xc >> yc >> r;

    glutinit(&argc, argv);
    glutinitdisplaymode(glut_single | glut_rgb);
    glutinitwindowsize(500, 500);
    glutcreatewindow("expt 04a - mid point circle algorithm");
    glutdisplayfunc(circle);
    myinit();
    glutmainloop();
    return 1;
}