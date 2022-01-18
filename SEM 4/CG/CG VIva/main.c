// GL_POLYGON by taking user input
//#include <GL/freeglut.h>
//Core OpenGL (GL): consists of hundreds of functions, 
//which begin with a prefix "gl" (e.g., glColor, glVertex, glTranslate, glRotate). 
//The Core OpenGL models an object via a set of geometric primitives, such as 
//point, line, and polygon
//#include <GL/gl.h>  // GLUT, includes glu.h and gl.h

// #include <stdio.h> 
  
// int a, b, c, d, e, f, g, h;
// void renderFunction()              // User defined function
// {
//  glClearColor(0.0, 0.0, 0.0, 0.0);  
//  glClear(GL_COLOR_BUFFER_BIT);     // To clear initial color buffer on the black window
//  glColor3f(0.0, 1.0, 0.0);         // set white color of the shape
//  gluOrtho2D(0, 640, 0, 480);         // Maps range of the co-ordinates
//  glBegin(GL_POLYGON);              // Primitive to draw polygon
//  glVertex2i(a, b);				   // Draws line from a to b
//  glVertex2i(c, d);
//  glVertex2i(e, f);
//  glVertex2i(g, h);
//  glEnd();                         // For glBegin
//  glFlush();                       // To clear the buffer
// }

// int main(int argc, char **argv)
// {
// 	scanf("%d", &a);
// 	scanf("%d", &b);
// 	scanf("%d", &c);
// 	scanf("%d", &d);
// 	scanf("%d", &e);
// 	scanf("%d", &f);
// 	scanf("%d", &g);
// 	scanf("%d", &h);
// 	 glutInit(&argc, argv);
// 	 glutInitDisplayMode(GLUT_SINGLE);
// 	 glutInitWindowSize(640, 480);
// 	 glutInitWindowPosition(100, 100);
// 	 glutCreateWindow("OpenGL - First window demo");
// 	 glutDisplayFunc(renderFunction);
// 	 glutMainLoop();
// 	 return 0;
// }

// 320, 240 is the centre
// ****************************************************************************
// GL_LINE to make coordinate system

// #include <GL/freeglut.h>
// #include <GL/gl.h>
// #include <stdio.h> 
  
// int x1, y1, x2, y2;
// void renderFunction()              // User defined function
// {
//  glClearColor(0.0, 0.0, 0.0, 0.0);  
//  glClear(GL_COLOR_BUFFER_BIT);     // To clear initial color buffer on the black window
//  glColor3f(0.0, 1.0, 0.0);         // set white color of the shape
//  gluOrtho2D(0, 640, 0, 480);         // Maps range of the co-ordinates
//  glBegin(GL_LINES);              // Primitive to draw polygon
//  glVertex2i(0, 240);				   // Draws line from a to b
//  glVertex2i(640, 240);
//  glEnd();
//  //Second line
//  glBegin(GL_LINES);              // Primitive to draw polygon
//  glVertex2i(320, 0);				   // Draws line from a to b
//  glVertex2i(320, 480);
//  glEnd();                         // For glBegin
//  glFlush();                       // To clear the buffer

//  // // To plot the point
//  // glBegin(GL_POINTS); //starts drawing of points
//  // glVertex2i(130, 130);//upper-right corner
//  // glVertex2i(210, 210);//lower-left corner
//  // glEnd();//end drawing of points
// }

// int main(int argc, char **argv)
// {
// 	 scanf("%d", &x1);
// 	 scanf("%d", &y1);
// 	 scanf("%d", &x2);
// 	 scanf("%d", &y2);
// 	 glutInit(&argc, argv);
// 	 glutInitDisplayMode(GLUT_SINGLE);
// 	 glutInitWindowSize(640, 480);
// 	 glutInitWindowPosition(100, 100);
// 	 glutCreateWindow("OpenGL - First window demo");
// 	 glutDisplayFunc(renderFunction);
// 	 glutMainLoop();
// 	 return 0;
// }

// // glClear( GL_COLOR_BUFFER_BIT);
// //  glBegin( GL_POINTS);
// //  glVertex3f(0.0f, 0.0f, 0.0f);
// //  glVertex3f(50.0f, 40.0f, 0.0f);
// //  glVertex3f(50.0f, 50.0f, 50.0f);
// //  glEnd();


#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h> 

int x1, y1, x2, y2, dx, dy, steps xIncrement, yIncrement, x, y;

int DDA(int x1, int y1, int x2, int y2) {
	dx = x2 - x1;
	dy = y2 - y1;
	if(dx > dy) steps = dx;
	else steps = dy;
	xIncrement = dx / steps;
	yIncrement = dy / steps;

	x = x1;
	y = y1;

	for(int i = 0; i < steps; i++) {
		putpixel(x, y, RED);
		x += xIncrement;
		y += yIncrement;	
	}
}

int main() {
	printf("Enter x1 and y1: ");
	printf("Enter x2 and y2: ");
	scanf("%d", &x1);
	scanf("%d", &x2);
	scanf("%d", &y1);
	scanf("%d", &y2);

	int gd = DETECT, gm;
  
    // Initialize graphics function 
    initgraph (&gd, &gm, "");  

    DDA(x1, y1, x2, y2);
    return 0;  	
}

