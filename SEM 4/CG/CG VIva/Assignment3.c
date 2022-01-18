#include<GL/freeglut.h>
#include<GL/gl.h>
#include<stdio.h>
#include<math.h>
#include<vector>

static int menu_id;
static int value=0;
int r,xc,yc;
void menu(int num)
{
	value=num;
	glutPostRedisplay();
}
//Drawing a
void setPixel(int x,int y)
{
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}

//To plot in 8 octants
void plotPixel(int xc,int yc,int x,int y) 
{
	setPixel(xc+x, yc+y);
	setPixel(xc-x, yc+y);
	setPixel(xc+x, yc-y);
    	setPixel(xc-x, yc-y);
    	setPixel(xc+y, yc+x);
    	setPixel(xc-y, yc+x);
    	setPixel(xc+y, yc-x);
    	setPixel(xc-y, yc-x);
}

// Bresenham’s circle drawing algorithm:
void drawCircle(int xc,int yc,int r){
	int x=0,y=r;
	int d = 3-2*r;

	// First point plot in 8 octants
	plotPixel(xc,yc,x,y); 
	while(x<=y)
	{
		
		x++;
		if(d<=0)
		{
			d=d+4*x+6;
			y=y;
		}
		else
		{
			d=d+4*(x-y)+10;
			y=y-1;
		}
		plotPixel(xc,yc,x,y);
	}
}

// Pattern 1
void pattern1()
{
	drawCircle(xc,yc,r);
    //Outer circle
	drawCircle(xc,yc,2*r);
    //Outer circle
	drawCircle(xc,yc,3*r);
	
	// To draw the outer circle
	drawCircle(xc-(2*r),yc,r);
	//2
	drawCircle(xc-r,yc+sqrt(3)*r,r);
	//3
	drawCircle(xc+r,yc+sqrt(3)*r,r);
	//4
	drawCircle(xc+2*r,yc,r);
	//5
	drawCircle(xc+r,yc-sqrt(3)*r,r);
	//6
	drawCircle(xc-r,yc-sqrt(3)*r,r);
}


// Pattern 2
void pattern2()
{
	drawCircle(xc,yc,r);
	drawCircle(xc,yc,2*r);
	
	drawCircle(xc+(r/sqrt(2)),yc+(r/sqrt(2)),r);
      drawCircle(xc+(r/sqrt(2)),yc-(r/sqrt(2)),r);
      drawCircle(xc-(r/sqrt(2)),yc+(r/sqrt(2)),r);
      drawCircle(xc-(r/sqrt(2)),yc-(r/sqrt(2)),r);
      drawCircle(xc+r,yc,r);
      drawCircle(xc-r,yc,r);
      drawCircle(xc,yc-r,r);
      drawCircle(xc,yc+r,r);
}

// Pattern 3
void pattern3()
{
	drawCircle(xc,yc,r);
    //Outer circle
	drawCircle(xc,yc,2*r);
	
	//To draw the outer circle
	//1
	drawCircle(xc-(2*r),yc,r);
	//2
	drawCircle(xc-r,yc+sqrt(3)*r,r);
	//3
	drawCircle(xc+r,yc+sqrt(3)*r,r);
	//4
	drawCircle(xc+2*r,yc,r);
	//5
	drawCircle(xc+r,yc-sqrt(3)*r,r);
	//6
	drawCircle(xc-r,yc-sqrt(3)*r,r);
}

// Mouse Click function
void mouseClick(int button,int state,int x,int y)
{
	switch(button)
	{
	
	case GLUT_LEFT_BUTTON:
		if(state==GLUT_DOWN)
		{
			printf("(%d %d)",x,y);
			xc=x;
			yc=480-y;
           		 
           		 if(value==1)
           		 {
           		 	pattern1();
           		 }
           		 else if(value==2)
           		 {
           		 	pattern2();
           		 }
           		 else if(value==3)
           		 {
           		 	pattern3();
           		 }
           		 glutSwapBuffers();

         
		}
		else if (state == GLUT_UP)
		{
		    printf("UP\n");
		}

		break;
	    default:
		break;
	}
	 fflush(stdout);
}

void createMenu()
{
	menu_id=glutCreateMenu(menu);
	glutAddMenuEntry("Pattern 1",1);
	glutAddMenuEntry("Pattern 2",2);
	glutAddMenuEntry("Pattern 3",3);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void renderFunction(){

    glClearColor(1, 1, 1, 1);
    glColor3f(1.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
    glBegin(GL_LINES);
		//X-axis
		glVertex2i(0,240);
		glVertex2i(640,240);
		//Y-axis
		glVertex2i(320,0);
		glVertex2i(320,480);
		
	glEnd();
    glutSwapBuffers();

}

// Main function
int main(int argc,char** argv)
{
	
	printf("Enter radius:");
	scanf("%d",&r);
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Assignment 3");
	createMenu();
	glutMouseFunc(mouseClick);
	glutDisplayFunc(renderFunction);
	glutMainLoop();
	return 0;
	
}