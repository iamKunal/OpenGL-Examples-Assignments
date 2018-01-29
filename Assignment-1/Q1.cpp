#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define WIDTH 800
#define HEIGHT 800


struct Point{
    float x,y;
};

Point P1,P2;

struct Color{
    float r,g,b;
};

Color C;

void drawCanvas(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    glColor3f(C.r, C.g, C.b);
    glVertex3f((float) P1.x, (float) P1.y,0);
    glVertex3f((float) P2.x, (float) P2.y,0);
    glEnd();
    glutSwapBuffers();
}


void myInit(void){
    glClearColor(1.0,1.0,1.0,0);
}

int main(int argc, char *argv[])
{
    cout << "Enter P1, P2 ( as x, y in [0,1] ) : ";
    cin >> P1.x >> P1.y >> P2.x >> P2.y;

    cout << "Enter Color (RGB) ( in [0,1] ): ";
    cin >> C.r >> C.g >> C.b;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("Polygon Maker");

    glutDisplayFunc(drawCanvas);

    myInit();

    glutMainLoop();
    return 0;
}