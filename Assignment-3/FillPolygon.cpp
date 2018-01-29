/*
Kunal Gupta
150001015

Sample Inputs:
4
10 10
250 10
250 150
150 200
2
2
30 20
1 0 0
4


*/

#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define WIDTH 800
#define HEIGHT 600
#define TIMEOUT 20


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
};

class Polygon {
    public:
    int numOfVertices;
    Point * vertices;
    int lineWidth;
    int renderStyle;
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

Color getPixelColor(Point p){
    Color col;
    glReadPixels(p.x, p.y, 1, 1, GL_RGB, GL_FLOAT, &col);
    return col;
}
void setPixelColor(Point p, Color pixelColor){
    glBegin(GL_POINTS);
    glColor3f(pixelColor.r, pixelColor.g, pixelColor.b);
    glVertex2i(p.x, p.y);
    glEnd();
}
// Old Recursive Solution
// void seedFill4(Point p, Color boundary, Color fill){
//     Point nxt=p;
//     cout<<"Trying Pixel : "<<p.x<<' '<<p.y<<' '<<endl;
//     if(number>110000)
//         return;
//     number++;
//     if(boundary!=getPixelColor(p) && fill!=getPixelColor(p)){
//         setPixelColor(p, fill);
//         nxt=p;
//         nxt.x=p.x+1;
//         seedFill4(nxt, boundary, fill);
//         nxt=p;
//         nxt.x=p.x-1;
//         seedFill4(nxt, boundary, fill);
//         nxt=p;
//         nxt.y=p.y+1;
//         seedFill4(nxt, boundary, fill);
//         nxt=p;
//         nxt.y=p.y-1;
//         seedFill4(nxt, boundary, fill);
//     }
// }
void seedFill4(Point p, Color boundary, Color fill){
    stack <Point> pts;
    pts.push(p);
    Point cur, nxt=p;
    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    while(! pts.empty()){
        cur=pts.top();
        pts.pop();
        if(boundary!=getPixelColor(cur) && fill!=getPixelColor(cur)){
            setPixelColor(cur, fill);
            nxt=cur;
            nxt.x=cur.x+1;
            pts.push(nxt);
            nxt=cur;
            nxt.y=cur.y+1;
            pts.push(nxt);
            nxt=cur;
            nxt.x=cur.x-1;
            pts.push(nxt);
            nxt=cur;
            nxt.y=cur.y-1;
            pts.push(nxt);
        }
        end = chrono::steady_clock::now();
        if(chrono::duration_cast<chrono::seconds>(end-start).count() > TIMEOUT){
            cerr<<"Premature Fill exit due to timeout, try increasing timeout in the #define TIMEOUT!"<<endl;
            break;
        }
    }
    end = chrono::steady_clock::now();
    cout<<"Done with 4-Neighbour Fill in "<<chrono::duration_cast<chrono::seconds>(end-start).count()<<" seconds!"<<endl;
}

void seedFill8(Point p, Color boundary, Color fill){
    stack <Point> pts;
    pts.push(p);
    Point cur, nxt=p;
    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    while(! pts.empty()){
        cur=pts.top();
        pts.pop();
        if(boundary!=getPixelColor(cur) && fill!=getPixelColor(cur)){
            setPixelColor(cur, fill);
            nxt=cur;
            nxt.x=cur.x+1;
            pts.push(nxt);
            nxt=cur;
            nxt.y=cur.y+1;
            pts.push(nxt);
            nxt=cur;
            nxt.x=cur.x-1;
            pts.push(nxt);
            nxt=cur;
            nxt.y=cur.y-1;
            pts.push(nxt);
            nxt=cur;
            nxt.x=cur.x+1;
            nxt.y=cur.y+1;
            pts.push(nxt);
            nxt=cur;
            nxt.x=cur.x+1;
            nxt.y=cur.y-1;
            pts.push(nxt);
            nxt=cur;
            nxt.x=cur.x-1;
            nxt.y=cur.y+1;
            pts.push(nxt);
            nxt=cur;
            nxt.x=cur.x-1;
            nxt.y=cur.y-1;
            pts.push(nxt);
        }
        end = chrono::steady_clock::now();
        if(chrono::duration_cast<chrono::seconds>(end-start).count() > TIMEOUT){
            cerr<<"Premature Fill exit due to timeout, try increasing line width from 1 or try increasing timeout in the #define TIMEOUT!"<<endl;
            break;

        }
    }
    end = chrono::steady_clock::now();
    cout<<"Done with 8-Neighbour Fill in "<<chrono::duration_cast<chrono::seconds>(end-start).count()<<" seconds!"<<endl;
}

void drawLine(Point P1, Point P2){
    glBegin(GL_POINTS);

    int dy = P2.y - P1.y;
    int dx = P2.x - P1.x;
    bool greaterThanOne = (abs(dy)>abs(dx)?true:false);
    
    glVertex2i(P1.x, P1.y);
    if(greaterThanOne){
        swap(P1.x, P1.y);
        swap(P2.x, P2.y);
        swap(dx, dy);
    }
    int P_i = 2*abs(dy) - abs(dx);
    int x_i = P1.x;
    int y_i = P1.y;
    for (int i = 0; i < abs(dx); ++i)
    {

        x_i+=sign(dx);
        if(P_i > 0){
            P_i = P_i - 2*abs(dx);
            y_i+=sign(dy);
        }

        P_i = P_i + 2*abs(dy);
        if(greaterThanOne){
            glVertex2i(y_i, x_i);
        }
        else{
            glVertex2i(x_i, y_i);
        }

    }
    glEnd();
}
void drawCustomPolygon(Polygon *p){
    int n = p->numOfVertices;
    for (int i = 0; i < n; ++i)
    {
        drawLine(p->vertices[i%n], p->vertices[(i+1)%n]);
    }
}


void drawCustomPolygon(void){
    drawCustomPolygon(polygon);
}

void drawCanvas(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    if(polygon->renderStyle == 1){
        glPolygonMode(GL_FRONT, GL_LINE);
        glLineWidth(polygon->lineWidth);
        glBegin(GL_POLYGON);
        
        for (int i = 0; i < polygon->numOfVertices; ++i)
        {
            glVertex2i(polygon->vertices[i].x, polygon->vertices[i].y);
        }
        glEnd();

        glPointSize(polygon->lineWidth);
        glBegin(GL_POINTS);
        for (int i = 0; i < polygon->numOfVertices; ++i)
        {
            glVertex2i(polygon->vertices[i].x,polygon->vertices[i].y);
        }
        glEnd();
        glPointSize(1.0);
    }
    else{
        glPointSize(polygon->lineWidth);
        drawCustomPolygon();
        glPointSize(1.0);
    }
    Color boundary;
    boundary = getPixelColor(polygon->vertices[0]);
    cout<<"Boundary colour is "<<boundary.r<<' '<<boundary.g<<' '<<boundary.b<<' '<<endl;
    cout<<"Please wait for a few seconds if the screen is black."<<endl;
    if(numberOfNeighbours==4)
        seedFill4(seed, boundary, fillColor);
    else
        seedFill8(seed, boundary, fillColor);
    glutSwapBuffers();
}


void myInit(void){
    glClearColor(1.0,1.0,1.0,0);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);

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

    cout<<"Enter Line width for drawing [use 2 as default value] (if selected 1, can cause overflow for 8-Neighbour) : ";
    cin>>polygon->lineWidth;
    cout<<"(1) Use inbuilt polygon maker or (2) Use Bresenham Algorithm manually : ";
    do{
        cin>>polygon->renderStyle;
    }while(polygon->renderStyle!=1 && polygon->renderStyle!=2);
    cout<<"Enter seed Pixel (as x y ) : ";
    cin>>seed.x>>seed.y;
    cout<<"Enter Fill Colour (as r g b [between 0 and 1]) : ";
    cin>>fillColor.r>>fillColor.g>>fillColor.b;
    cout<<"Enter number of neighbours to colour (4/8) : ";
    do{
        cin>>n;
    }while(n!=4 && n!=8);

    numberOfNeighbours = n;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);

    glutCreateWindow("Polygon Filling");

    glutDisplayFunc(drawCanvas);

    myInit();

    glutMainLoop();
    return 0;
}