#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define WIDTH 800
#define HEIGHT 800

struct Point{
    float x,y;
};

Point *P;
struct Color{
    float r,g,b;
};

Point centroid;
Color boundary, inner;
int N=3;
int Vertices = 3;
string text;
void drawBitmapText(const char *string,float x,float y,float z) 
{  
    const char *c;
    glRasterPos3f(x, y,z);

    for (c=string; *c != '\0'; c++) 
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}
void drawCanvas(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glColor3f(inner.r, inner.g, inner.b);
    for (int i = 0; i < Vertices; ++i)
    {
        glVertex3f((float) P[i].x,(float) P[i].y,0);
    }
    glEnd();
    glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_POLYGON);
    glColor3f(boundary.r, boundary.g, boundary.b);
    for (int i = 0; i < Vertices; ++i)
    {
        glVertex3f((float) P[i].x,(float) P[i].y,0);
    }
    glEnd();
    glColor3f(1.0,1.0,1.0);
    drawBitmapText(text.c_str(),centroid.x,centroid.y,0.0);
    // glutSwapBuffers(); 
    glutSwapBuffers();
}


void myInit(void){
    glClearColor(1.0,1.0,1.0,0);
}

int main(int argc, char *argv[])
{
    cout<< "Enter Number of Vertices : ";
    cin >> Vertices;
    P = new Point[Vertices];
    cout << "Enter Vertices of " << Vertices << "-sided Polygon ( as x, y in [0,1] ) : ";
    for (int i = 0; i < Vertices; ++i)
    {
        cin >> P[i].x >> P[i].y;
    }

    cout << "Enter Color (Boundary) : ";
    cin >> boundary.r >> boundary.g >> boundary.b;

    cout << "Enter Color (inner) : ";
    cin >> inner.r >> inner.g >> inner.b;
    
    cout << "Enter text inside polygon : ";
    cin.ignore();
    getline(cin,text);

    centroid.x=centroid.y=0.0;
    for (int i = 0; i < Vertices; ++i)
    {
        centroid.x+=P[i].x;
        centroid.y+=P[i].y;
    }
    centroid.x=centroid.x/Vertices;

    centroid.y=centroid.x/Vertices;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("Line Maker");

    glutDisplayFunc(drawCanvas);

    myInit();
    
    glutMainLoop();
    return 0;
}