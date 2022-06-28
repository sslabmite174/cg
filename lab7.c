#include<stdio.h>
#include<stdbool.h>
#include<GL/glut.h>
float xmin,ymin,xmax,ymax;
float xvmin=200,yvmin=200,xvmax=300,yvmax=300;
float x0,y0,x1,y11;
const int RIGHT=2;
const int LEFT=1;
const int TOP=8;
const int BOTTOM=4;
int ComputeOutCode(float x, float y);

void CSLCAD(float x0, float y0, float x1, float y11)
{
    int outcode0, outcode1, outcodeOut;
    bool accept=false, done=false;
    outcode0=ComputeOutCode(x0,y0);
    outcode1=ComputeOutCode(x1,y11);
    do
    {
        if((outcode0 | outcode1)==0)
        {
            accept=true;
            done=true;
        }
        else if((outcode0 & outcode1)!=0)
            done=true;
        else
        {
            double x, y;
            outcodeOut=outcode0?outcode0:outcode1;
            if(outcodeOut & TOP)
            {
                x=x0+(x1-x0)*(ymax-y0)/(y11-y0);
                y=ymax;
            }
            else if(outcodeOut & BOTTOM)
            {
                x=x0+(x1-x0)*(ymin-y0)/(y11-y0);
                y=ymin;
            }
            else if(outcodeOut & RIGHT)
            {
                y=y0+(y11-y0)*(xmax-x0)/(x1-x0);
                x=xmax;
            }
            else
            {
                y=y0+(y11-y0)*(xmin-x0)/(x1-x0);
                x=xmin;
            }
            if(outcodeOut==outcode0)
            {
                x0=x;
                y0=y;
                outcode0=ComputeOutCode(x0,y0);
            }
            else
            {
                x1=x;
                y11=y;
                outcode1=ComputeOutCode(x1,y11);
            }
        }
    }while(!done);
    
    if(accept)
    {
        double sx=(xvmax-xvmin)/(xmax-xmin);
        double sy=(yvmax-yvmin)/(ymax-ymin);
        double vx0=xvmin+(x0-xmin)*sx;
        double vy0=yvmin+(y0-ymin)*sy;
        double vx1=xvmin+(x1-xmin)*sx;
        double vy11=yvmin+(y11-ymin)*sy;
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(xvmin, yvmin);
            glVertex2f(xvmax, yvmin);
            glVertex2f(xvmax, yvmax);
            glVertex2f(xvmin, yvmax);
        glEnd();
        glColor3f(0.0,0.0,1.0);
        glBegin(GL_LINES);
            glVertex2d(vx0,vy0);
            glVertex2d(vx1,vy11);
        glEnd();
    }
}

int ComputeOutCode(float x, float y)
{
    int code=0;
    if(y > ymax)
        code =  TOP;
    else if(y < ymin)
        code = BOTTOM;
    if(x > xmax)
        code = RIGHT;
    else if(x < xmin)
        code = LEFT;
    return code;
}
void drawline()
{
    glBegin(GL_LINES);
        glVertex2d(x0,y0);
        glVertex2d(x1,y11);
    glEnd();
}
void drawrect()
{
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
    glEnd();
}

void display()
{
    
    glColor3f(1.0,0.0,0.0);
    drawline();
    glColor3f(0.0,0.0,1.0);
    drawrect();
    CSLCAD(x0,y0,x1,y11);
    glFlush();
}

void myinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}

void main(int argc, char *argv[])
{
    printf("Enter the end points of clipping window: ");
    scanf("%f%f%f%f", &xmin,&ymin,&xmax,&ymax);
    printf("Enter the end points of the line: ");
    scanf("%f%f%f%f", &x0,&y0,&x1,&y11);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("4MT19CS174 Cohen-Sutherland Line Clipping");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}
