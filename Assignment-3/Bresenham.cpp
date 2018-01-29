/*
Kunal Gupta
150001015

Sample Inputs:
400 300 200

100 100 50



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

struct Circle{
	Point centre;
	int radius;
};

struct Color{
    float r,g,b;
};

Circle Cir;

Color C;

int sign(double x){
	return ((x > 0) ? 1 : ((x < 0) ? -1 : 0));
}

void plotAllOctants(int x_i, int y_i){
	glVertex2i(x_i+Cir.centre.x, y_i+Cir.centre.y);
	glVertex2i(-x_i+Cir.centre.x, y_i+Cir.centre.y);
	glVertex2i(x_i+Cir.centre.x,-y_i+Cir.centre.y);
	glVertex2i(-x_i+Cir.centre.x, -y_i+Cir.centre.y);
	glVertex2i(y_i+Cir.centre.x, x_i+Cir.centre.y);
	glVertex2i(-y_i+Cir.centre.x, x_i+Cir.centre.y);
	glVertex2i(y_i+Cir.centre.x, -x_i+Cir.centre.y);
	glVertex2i(-y_i+Cir.centre.x, -x_i+Cir.centre.y);
	
}

void drawCanvas(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    glColor3f(0, 0, 0);

    int r = Cir.radius;
    int x_i = 0;
    int y_i = Cir.radius;

    plotAllOctants(x_i, y_i);
    int P_i = 3-2*r;

    while(y_i>x_i){
    	if(P_i>=0){
    		P_i = P_i + 4*x_i - 4*y_i + 10;
    		y_i--;
    	}
    	else{
    		P_i = P_i + 4*x_i +6;
    	}
    	x_i++;
    	plotAllOctants(x_i,y_i);

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
    cout << "Enter Center of circle and radius ( as x y r) : ";
    cin >> Cir.centre.x >> Cir.centre.y >> Cir.radius;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("DDA Algo");

    glutDisplayFunc(drawCanvas);

    myInit();

    glutMainLoop();
    return 0;
}



