/*
Kunal Gupta
150001015

Sample Inputs:
4
100 100
200 100
250 250
100 200
2
3
-135



*/

#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define WIDTH 1200
#define HEIGHT 800
#define SPACING 50
struct Point{
    float x,y;
};

struct Color{
    GLfloat r,g,b;
    GLfloat alpha;
    bool operator==(const Color &b){
        return (this->r==b.r && this->g==b.g && this->b==b.b);
    }
    bool operator!=(const Color &b){
        return (this->r!=b.r || this->g!=b.g || this->b!=b.b);
    }
    Color(){};
    Color(GLfloat r, GLfloat g, GLfloat b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

class Polygon {
    public:
    int numOfVertices;
    Point * vertices;
    int lineWidth;
    Polygon(){
        numOfVertices=0;
        vertices=NULL;
    }
    Polygon(int n){
        numOfVertices = n;
        vertices = new Point[numOfVertices];
    }
    void clear(){
        delete [] vertices;
        vertices = NULL;
    }
    ~Polygon(){
        if (vertices)
            delete [] vertices;
    }
};

Polygon* polygon;

Color C, fillColor;

Point seed;

int numberOfNeighbours;



int sign(double x){
	return ((x > 0) ? 1 : ((x < 0) ? -1 : 0));
}

struct TransformValues{
    int tx, ty;
    float sx, sy;
    float theta;
    int choice;
    int axis; // x=1, y=2
} transformationValues;



void drawPolygon(int first=0){
    // glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    if (first)
        glColor3f(1.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT, GL_LINE);
    glLineWidth(polygon->lineWidth);
    glBegin(GL_POLYGON);
    
    for (int i = 0; i < polygon->numOfVertices; ++i)
    {
        glVertex2i(polygon->vertices[i].x, polygon->vertices[i].y);
    }
    glEnd();
}

void multiplyAndTransform(float matrix[3][3]){
    int P[3];
    float F[3] = {0};
    for (int i = 0; i < polygon->numOfVertices; ++i)
    {
        P[0] = polygon->vertices[i].x;
        P[1] = polygon->vertices[i].y;
        P[2] = 1;
        F[0] = F[1] = F[2] = 0;
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                F[j]+= matrix[j][k] * P[k];
            }
        }
        polygon->vertices[i].x = F[0];
        polygon->vertices[i].y = F[1];
           
    }
    return;
}
void translate(){
    float matrix[3][3] = { {1, 0, (float)transformationValues.tx},
                         {0, 1, (float)transformationValues.ty},
                         {0, 0, 1} };
                         
    multiplyAndTransform(matrix);
}

void scale(){
    float matrix[3][3] = { {transformationValues.sx, 0, 0},
                         {0, transformationValues.sy, 0},
                         {0, 0, 1} };
    multiplyAndTransform(matrix);
}

void rotate(){
    float rads = transformationValues.theta * 3.14159265358979 / 180.0;
    float matrix[3][3] = { {cos(rads), -sin(rads), 0},
                         {sin(rads), cos(rads), 0},
                         {0, 0, 1} };
    multiplyAndTransform(matrix);
}
void reflect(){
    float matrix[3][3] = { {1, 0, 0},
                         {0, 1, 0},
                         {0, 0, 1} };
    
    switch(transformationValues.axis){
        case 1: matrix[0][0] = -1;
            break;
        case 2: matrix[1][1] = -1;
            break;
    }
    multiplyAndTransform(matrix);
    reverse(polygon->vertices, polygon->vertices+polygon->numOfVertices);
}
typedef void (*voidfunctions) (void);

voidfunctions tranformations[] = {
    translate,
    scale,
    rotate,
    reflect
};
void drawGrid(){
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_LINES);
    for (int i = SPACING; i < WIDTH/2; i+=SPACING)
    {
        glVertex2i(i, HEIGHT/2);
        glVertex2i(i, -HEIGHT/2);

        glVertex2i(-i, HEIGHT/2);
        glVertex2i(-i, -HEIGHT/2);
    }
    for (int i = SPACING; i < HEIGHT/2; i+=SPACING)
    {
        glVertex2i(WIDTH/2, i);
        glVertex2i(-WIDTH/2, i);
        glVertex2i(WIDTH/2, -i);
        glVertex2i(-WIDTH/2, -i);
    }
    glEnd();

    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_LINES);
    glVertex2i(0, HEIGHT/2);
    glVertex2i(0, -HEIGHT/2);
    glVertex2i(WIDTH/2, 0);
    glVertex2i(-WIDTH/2, 0);
    glEnd();

}
void drawCanvas(void){
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawPolygon();
    tranformations[transformationValues.choice-1]();
    drawPolygon(2);
    glutSwapBuffers();
}


void myInit(void){
    glClearColor(1.0,1.0,1.0,0);
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);

}

int main(int argc, char *argv[])
{
    cout << "Enter number of vertices : ";
    int n;
    cin>>n;
    polygon = new Polygon(n);
    cout<<"Enter the "<< n <<" vertices of the Polygon ( as x y ) :"<<endl;
    for (int i = 0; i < n; ++i)
    {
        cin>>polygon->vertices[i].x>>polygon->vertices[i].y;
    }

    cout<<"Enter Line width for drawing : ";
    cin>>polygon->lineWidth;
    cout<<"\n (1) Translation\n (2) Scaling\n (3) Rotation\n (4) Reflection\nEnter your choice : ";
    do{
        cin>>transformationValues.choice;
    }while(transformationValues.choice > 4 || transformationValues.choice < 1);
    switch(transformationValues.choice){
        case 1:
            cout<<"Enter tx ty : ";
            cin>>transformationValues.tx>>transformationValues.ty;
            break;
        case 2:
            cout<<"Enter sx sy : ";
            cin>>transformationValues.sx>>transformationValues.sy;
            break;
        case 3:
            cout<<"Enter theta (in degrees) : ";
            cin>>transformationValues.theta;
            break;
        case 4:
            cout<<"Rotate about (1) X-axis or (2) Y-axis : ";
            break;
    }
    if(transformationValues.choice==4){
        do{
            cin>>transformationValues.axis;
        }while(transformationValues.axis!=1 && transformationValues.axis!=2);
    }
    cout<<endl<<"Grid Size is "<<SPACING<<'.'<<endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("Polygon Filling");

    glutDisplayFunc(drawCanvas);

    myInit();

    glutMainLoop();
    return 0;
}