 #include <GL/freeglut.h>
#include<GL/gl.h>
#include<stdio.h>
#include<math.h>
#include<vector>

static int menu_id;
static int sub_menu_id;
static int value = 0;
static int mousePattern1,mousePaattern2,pattern; // To use for mouse handling



void menu(int num)
{
	value=num;
	glutPostRedisplay();
}

////////////////////////////////////// DDA Algorithm ////////////////////////////////////////////
// ************************ DDA Simple Line ******************************** 
void dda_simple(int X1,int Y1,int X2,int Y2)
{
	float dx,dy,step,i,x,y,xinc,yinc;
	
	//calculate dx and dy
	dx=X2-X1;
	dy=Y2-Y1;
	//step value
	if(abs(dx)>=abs(dy))
		step=abs(dx);
	else
		step=abs(dy);
	//x increment
	xinc=dx/step;
	yinc=dy/step;//y increment
	//plot first point
	x=X1;
	y=Y1;
	
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	//plot points
	for(i=0;i<step;i++)
	{
		x=x+xinc;
		y=y+yinc;
		glBegin(GL_POINTS);
			glVertex2i(x,y);
		glEnd();
		
	}
	
}

// ************************* DDA Dotted Line ********************************

void dda_dotted(int X1,int Y1,int X2,int Y2)
{
	float dx,dy,step,x,y,xinc,yinc;
	int i;
	
	//calculate dx and dy
	dx=X2-X1;
	dy=Y2-Y1;
	//step value
	if(abs(dx)>=abs(dy))
		step=abs(dx);
	else
		step=abs(dy);
	//x increment
	xinc=dx/step;
	yinc=dy/step;//y increment
	//plot first point
	x=X1;
	y=Y1;
	
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	//plot points
	for(i=0;i<step;i++)
	{
		x=x+xinc;
		y=y+yinc;
		if(i%2==0)
		{
			glBegin(GL_POINTS);
			glVertex2i(x,y);
		glEnd();
		}
		
		
		
		
		
	}
	
}

// ************************* DDA Dashed Line ********************************
void dda_dashed(int X1,int Y1,int X2,int Y2)
{
	float dx,dy,step,x,y,xinc,yinc;
	int i;
	
	//calculate dx and dy
	dx=X2-X1;
	dy=Y2-Y1;
	//step value
	if(abs(dx)>=abs(dy))
		step=abs(dx);
	else
		step=abs(dy);
	//x increment
	xinc=dx/step;
	yinc=dy/step;//y increment
	//plot first point
	x=X1;
	y=Y1;
	
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	//plot points
	for(i=0;i<step;i++)
	{
		x=x+xinc;
		y=y+yinc;
		if(i%5==0)
		continue;
		else
		{
		glBegin(GL_POINTS);
			glVertex2i(x,y);
		glEnd();
		
		}
		
		
		
		
	}
	
}

// ************************* DDA Solid Line ********************************
void dda_solid(int X1,int Y1,int X2,int Y2)
{
	float dx,dy,step,i,x,y,xinc,yinc;
	
	//calculate dx and dy
	dx=X2-X1;
	dy=Y2-Y1;
	//step value
	if(abs(dx)>=abs(dy))
		step=abs(dx);
	else
		step=abs(dy);
	//x increment
	xinc=dx/step;
	yinc=dy/step;//y increment
	//plot first point
	x=X1;
	y=Y1;
	
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	//plot points
	for(i=0;i<step;i++)
	{
		x=x+xinc;
		y=y+yinc;
		
			glBegin(GL_POINTS);
			glVertex2i(x,y);
			glEnd();
			
			glBegin(GL_POINTS);
			glVertex2i(x+1,y+1);
			glEnd();
			
			glBegin(GL_POINTS);
			glVertex2i(x-1,y-1);
			glEnd();
		
	}
	
}

////////////////////////////////////// Bresenham's Line Algorithm //////////////////////////////////////


// ************************* Bresenham Simple Line ********************************
void bresenham_simple(int X1,int Y1,int X2,int Y2)
{
	float dx,dy,pk,x,y,k,xinc,yinc,m;

	dx=X2-X1;
	dy=Y2-Y1;
	//slope
	m=dy/dx;
	//initial distance parameter
	dx=abs(dx);
	dy=abs(dy);
	pk=2*dx-dy;
	//plot first point
	x=X1;
	y=Y1;
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	
		if(X2>= X1)
			xinc=1;
		else
			xinc=-1;
		
		if(Y2>=Y1)
			yinc=1;
		else
			yinc=-1;
		
	//for positive slope
	if(m>=0)
	{
		
		for(k=0;k<dx;k++)
		{
			if(pk<=0)
				pk=pk+2*dy;
			else
			{
				pk=pk+2*dy-2*dx;
				y+=yinc;
			}
			x+=xinc; //x will change always
			glBegin(GL_POINTS);
				glVertex2i(x,y);
			glEnd();
		}		
	}
	//negative slope
	else{
		
		
		x=X1;
		y=Y1;
		glBegin(GL_POINTS);
			glVertex2i(x,y);
		glEnd();
		
		for(k=0;k<dy;k++)
		{
			if(pk<=0)
			{
				pk=pk+2*dx;
			}
			else
			{
				pk=pk+2*dx-2*dy;
				x=x+xinc;
			}
			y=y+yinc; //y will change always
			glBegin(GL_POINTS);
				glVertex2i(x,y);
			glEnd();
		}
	}
	
	
	
}

// ************************* Bresenham Dotted Line ********************************
void bresenham_dotted(int X1,int Y1,int X2,int Y2)
{
	float dx,dy,pk,x,y,xinc,yinc,m;
	int k;

	dx=X2-X1;
	dy=Y2-Y1;
	//slope
	m=dy/dx;
	//initial distance parameter
	dx=abs(dx);
	dy=abs(dy);
	pk=2*dx-dy;
	//plot first point
	x=X1;
	y=Y1;
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	
		if(X2>= X1)
			xinc=1;
		else
			xinc=-1;
		
		if(Y2>=Y1)
			yinc=1;
		else
			yinc=-1;
		
	//for positive slope
	if(m>=0)
	{
		
		for(k=0;k<dx;k++)
		{
			if(pk<=0)
				pk=pk+2*dy;
			else
			{
				pk=pk+2*dy-2*dx;
				y+=yinc;
			}
			x+=xinc; //x will change always
			if(k%2==0)
			{
			glBegin(GL_POINTS);
				glVertex2i(x,y);
			glEnd();
			}
			
		}		
	}
	//negative slope
	else{
		
		
		x=X1;
		y=Y1;
		glBegin(GL_POINTS);
			glVertex2i(x,y);
		glEnd();
		
		for(k=0;k<dy;k++)
		{
			if(pk<=0)
			{
				pk=pk+2*dx;
			}
			else
			{
				pk=pk+2*dx-2*dy;
				x=x+xinc;
			}
			y=y+yinc; //y will change always
			if(k%2==0)
			{
			glBegin(GL_POINTS);
				glVertex2i(x,y);
			glEnd();
			}
			
		}
	}
	
	
	
}


// ************************* Bresenham Dashed Line ********************************
void bresenham_dashed(int X1,int Y1,int X2,int Y2)
{
	float dx,dy,pk,x,y,xinc,yinc,m;
	int k;

	dx=X2-X1;
	dy=Y2-Y1;
	//slope
	m=dy/dx;
	//initial distance parameter
	dx=abs(dx);
	dy=abs(dy);
	pk=2*dx-dy;
	//plot first point
	x=X1;
	y=Y1;
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	
		if(X2>= X1)
			xinc=1;
		else
			xinc=-1;
		
		if(Y2>=Y1)
			yinc=1;
		else
			yinc=-1;
		
	//for positive slope
	if(m>=0)
	{
		
		for(k=0;k<dx;k++)
		{
			if(pk<=0)
				pk=pk+2*dy;
			else
			{
				pk=pk+2*dy-2*dx;
				y+=yinc;
			}
			x+=xinc; //x will change always
			if(k%5==0)
			continue;
			else
			{
			glBegin(GL_POINTS);
				glVertex2i(x,y);
			glEnd();
			}
			
		}		
	}
	//negative slope
	else{
		
		
		x=X1;
		y=Y1;
		glBegin(GL_POINTS);
			glVertex2i(x,y);
		glEnd();
		
		for(k=0;k<dy;k++)
		{
			if(pk<=0)
			{
				pk=pk+2*dx;
			}
			else
			{
				pk=pk+2*dx-2*dy;
				x=x+xinc;
			}
			y=y+yinc; //y will change always
			if(k%5==0)
			continue;
			else
			{
			glBegin(GL_POINTS);
				glVertex2i(x,y);
			glEnd();
			}
			
			
		}
	}
		
}

// ************************* Bresenham Solid Line ********************************
void bresenham_solid(int X1,int Y1,int X2,int Y2)
{
	float dx,dy,pk,x,y,k,xinc,yinc,m;

	dx=X2-X1;
	dy=Y2-Y1;
	//slope
	m=dy/dx;
	//initial distance parameter
	dx=abs(dx);
	dy=abs(dy);
	pk=2*dx-dy;
	//plot first point
	x=X1;
	y=Y1;
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	
		if(X2>= X1)
			xinc=1;
		else
			xinc=-1;
		
		if(Y2>=Y1)
			yinc=1;
		else
			yinc=-1;
		
	//for positive slope
	if(m>=0)
	{
		
		for(k=0;k<dx;k++)
		{
			if(pk<=0)
				pk=pk+2*dy;
			else
			{
				pk=pk+2*dy-2*dx;
				y+=yinc;
			}
			x+=xinc; //x will change always
			glBegin(GL_POINTS);
				glVertex2i(x,y);
			glEnd();
			
			glBegin(GL_POINTS);
				glVertex2i(x+1,y+1);
			glEnd();
			
			glBegin(GL_POINTS);
				glVertex2i(x-1,y-1);
			glEnd();
		}	
		
	}
	//negative slope
	else{
		
		
		x=X1;
		y=Y1;
		glBegin(GL_POINTS);
			glVertex2i(x,y);
		glEnd();
		
		for(k=0;k<dy;k++)
		{
			if(pk<=0)
			{
				pk=pk+2*dx;
			}
			else
			{
				pk=pk+2*dx-2*dy;
				x=x+xinc;
			}
			y=y+yinc; //y will change always
			glBegin(GL_POINTS);
				glVertex2i(x,y);
			glEnd();
			
			glBegin(GL_POINTS);
				glVertex2i(x+1,y+1);
			glEnd();
			
			glBegin(GL_POINTS);
				glVertex2i(x-1,y-1);
			glEnd();
		}
	}
	
	
	
}


// Mouse Click
int k = 1;
int X[100], Y[100];
void mouseClickDetector(int button, int state, int x, int y )
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        printf(" LEFT ");
        if (state == GLUT_DOWN)
        {
            printf("DOWN\n");
            printf("(%d, %d)\n", x, y);
            X[k] = x;
            Y[k] = 480 - y; // match the glut coordinate to window coordinate 
	        
            if(k>1)
            {
            	if(value==11)
            	{
            		dda_simple(X[k - 1], Y[k - 1], X[k], Y[k]);
                	printf("DDA Simple\n");	
            	}
            	else if(value==12)
            	{
            		dda_dotted(X[k - 1], Y[k - 1], X[k], Y[k]);
                	printf("DDA dotted\n");	
            	}
            	else if(value==13)
            	{
            		dda_dashed(X[k - 1], Y[k - 1], X[k], Y[k]);
                	printf("DDA dashed\n");	
            	}
            	else if(value==14)
            	{
            		dda_solid(X[k - 1], Y[k - 1], X[k], Y[k]);
                	printf("DDA solid line\n");	
            	}
            	
            	else if(value==21)
            	{
            		bresenham_simple(X[k - 1], Y[k - 1], X[k], Y[k]);
	                printf("Bresenham simple\n");
            		
            	}
            	
            	else if(value==22)
            	{
            		bresenham_dotted(X[k - 1], Y[k - 1], X[k], Y[k]);
	                printf("Bresenham dotted\n");
            		
            	}
            	else if(value==23)
            	{
            		bresenham_dashed(X[k - 1], Y[k - 1], X[k], Y[k]);
	                printf("Bresenham dashed\n");
            		
            	}
            	else if(value==24)
            	{
            		bresenham_solid(X[k - 1], Y[k - 1], X[k], Y[k]);
	                printf("Bresenham solid\n");
            		
            	}
            }

            glutSwapBuffers();

            k++;
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

// Creating the menu and sub-menu
void createMenu(void)
{
	// DDA
	mousePattern1 = glutCreateMenu(menu); 
	glutAddMenuEntry("Simple Line",11);
	glutAddMenuEntry("Dotted Line",12);
	glutAddMenuEntry("Dashed Line",13);
	glutAddMenuEntry("Solid Line",14);
	
	// Bresenham
	mousePaattern2 = glutCreateMenu(menu);
	glutAddMenuEntry("Simple Line",21);
	glutAddMenuEntry("Dotted Line",22);
	glutAddMenuEntry("Dashed Line",23);
	glutAddMenuEntry("Solid Line",24);
	
	pattern = glutCreateMenu(menu);
	//function to call menu function and return value
	glutAddSubMenu("DDA",mousePattern1);
	glutAddSubMenu("Bresenham",mousePaattern2);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	
}



// void createMenu(void)
// {
//     menu_id = glutCreateMenu(menu);
//     glutAddMenuEntry("DDA", 1);
//     glutAddMenuEntry("Bresenham", 2);
	
//     glutAttachMenu(GLUT_RIGHT_BUTTON);
// }



void renderFunction(){

    glClearColor(1, 1, 1, 1);
    glColor3f(1.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
    dda_simple(0,240,640,240);
    bresenham_simple(320,480,320,0);
    glutSwapBuffers();

}



int main(int argc,char** argv)
{
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Assignment 2");
	createMenu();

	
	glutMouseFunc(mouseClickDetector);
	glutDisplayFunc(renderFunction);
	glutMainLoop();
	return 0;
	
}
