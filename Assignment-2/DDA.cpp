/*
Kunal Gupta
150001015

Sample Inputs:
10 10
100 50

10 10
100 100

10 10
50 100

10 100
100 50

10 100
50 10

10 100
50 60

*/

#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define WIDTH 800
#define HEIGHT 600


struct Point{
    float x,y;
};

Point P1,P2;

struct Color{
    float r,g,b;
};

Color C;

int sign(double x){
	return ((x > 0) ? 1 : ((x < 0) ? -1 : 0));
}

void drawCanvas(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    glColor3f(0, 0, 0);

    int dy = P2.y - P1.y;
    int dx = P2.x - P1.x;

    float m=(dy+0.0)/dx;
    float x_i = P1.x;
    float y_i = P1.y;
    if (fabs(m)<1){
	    for (int i = 0; i <= abs(dx); ++i)
	    {
	    	glVertex2i((int) x_i, (int) y_i);
	    	x_i+=sign(dx);
	    	y_i+=fabs(m) * sign(dy);
	    }
	}
	else{
		for (int i = 0; i <= abs(dy); ++i)
	    {
	    	glVertex2i((int) x_i, (int) y_i);
	    	y_i+=sign(dy);
	    	x_i+=fabs(1.0/m) * sign(dx);
	    }
	}
    glEnd();
    glutSwapBuffers();
}


void myInit(void){
    glClearColor(1.0,1.0,1.0,0);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);

}

int main(int argc, char *argv[])
{
    cout << "Enter P1, P2 ( as x, y ) : ";
    cin >> P1.x >> P1.y >> P2.x >> P2.y;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("DDA Algo");

    glutDisplayFunc(drawCanvas);

    myInit();

    glutMainLoop();
    return 0;
}



