#include<GL/glut.h>
#include<stdio.h>
float vertics[8][3]={{-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1},{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1}};
float color[8][3]={{0,0,0},{1,0,0},{1,1,0},{0,1,0},{0,0,1},{1,0,1},{1,1,1},{0,1,1}};
int axis=0;
float theta[3]={0.0,0.0,0.0};

void polygon(int a,int b,int c,int d){
	glBegin(GL_POLYGON);
	glColor3fv(color[a]);
	glVertex3fv(vertics[a]);

	glColor3fv(color[b]);
	glVertex3fv(vertics[b]);
	
	glColor3fv(color[c]);
	glVertex3fv(vertics[c]);

	glColor3fv(color[d]);
	glVertex3fv(vertics[d]);
	glEnd();
}
void colorcube(){
	polygon(0,3,2,1);
	polygon(2,1,5,6);
	polygon(4,7,6,5);
	polygon(0,4,5,1);
	polygon(0,4,7,3);
	polygon(2,6,7,3);
}
void mydisplay(){
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta[0],1.0,0.0,0.0);
	glRotatef(theta[1],0.0,1.0,0.0);
	glRotatef(theta[2],0.0,0.0,1.0);
	colorcube();
	glFlush();
	glutSwapBuffers();
}
void spincube(){
	theta[axis]+=1;
	if(theta[axis]>360){
		theta[axis]=0;
	}
	glutPostRedisplay();
}
void mouse(int btn,int state,int x,int y){
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
		axis=0;
	if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
		axis=1;
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
		axis=2;
	spincube();
}
void myreshape(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<h){
		glOrtho(-5.0,5.0,-5.0*(float)h/(float)w,5.0*(float)h/(float)w,-10.0,10.0);
	}
	else{
		glOrtho(-5.0*(float)h/(float)w,5.0*(float)h/(float)w,-5.0,5.0,-10.0,10.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
int main(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Spin Cube");
	glutReshapeFunc(myreshape);
	glutDisplayFunc(mydisplay);
	glutIdleFunc(spincube);
	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}
