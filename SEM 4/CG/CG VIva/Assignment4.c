#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
struct Color
{
 float r;
 float g;
 float b;
};
struct Circle
{
 int xc, yc, r;
};
struct Pattern
{ int patternType, x0, y0, r0;
 vector<Circle> circs;
};
//
bool drawMode = false;
bool colorMode = false;
int patternNumber = 2;
int patternXc = 250;
int patternYc = 250;
int radius = 25;
Color bkg = {1.0, 1.0, 1.0};
Color bd = {0.0, 0.0, 0.0};
Color red = {1.0, 0.0, 0.0};
Color green = {0.0, 1.0, 0.0};
Color blue = {0.0, 0.0, 1.0};
Color fillColor = red;
char algo = 'f'; // f or b are two options
void init()
{
 glClearColor(1.0, 1.0, 1.0, 0.0);
 glClear(GL_COLOR_BUFFER_BIT);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}
Color getPixel(int x, int y)
{
 Color color;
 glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, 
&color);
 return color;
}
void setPixel(int x, int y)
{
 glColor3f(fillColor.r, fillColor.g, fillColor.b);
 glBegin(GL_POINTS);
 glVertex2i(x, y); glEnd();
 glFlush();
}
void boundaryFill(int x, int y)
{
 float r = getPixel(x, y).r;
 float g = getPixel(x, y).g;
 float b = getPixel(x, y).b;
 if ((r != bd.r || g != bd.g || b != bd.b) && (r != 
fillColor.r || g != fillColor.g || b != fillColor.b))
 {
 setPixel(x, y);
 boundaryFill(x, y + 1);
 boundaryFill(x - 1, y);
 boundaryFill(x + 1, y);
 boundaryFill(x, y - 1);
 }
}
void floodFill(int x, int y)
{ float r = getPixel(x, y).r;
 float g = getPixel(x, y).g;
 float b = getPixel(x, y).b;
 if (r == bkg.r && g == bkg.g && b == bkg.b)
 {
 setPixel(x, y);
 floodFill(x, y + 1);
 floodFill(x - 1, y);
 floodFill(x + 1, y);
 floodFill(x, y - 1);
 }
}
void drawPoints(int x, int y, int xc, int yc)
{
 x += xc;
 y += yc;
 glColor3f(0.0, 0.0, 0.0);
 glBegin(GL_POINTS);
 glVertex2i(x, y);
 glEnd();
 glFlush();}
void drawCircle(Circle c)
{
 int x = 0;
 int y = c.r;
 int d = 3 - (2 * c.r);
 while (x <= y)
 {
 drawPoints(x, y, c.xc, c.yc);
 drawPoints(-x, y, c.xc, c.yc);
 drawPoints(x, -y, c.xc, c.yc);
 drawPoints(-x, -y, c.xc, c.yc);
 drawPoints(y, x, c.xc, c.yc);
 drawPoints(-y, x, c.xc, c.yc);
 drawPoints(y, -x, c.xc, c.yc);
 drawPoints(-y, -x, c.xc, c.yc);
 x++;
 if (d <= 0)
 { d += (4 * x) + 6;
 }
 else
 {
 d += 4 * (x - y) + 10;
 y--;
 }
 }
}
void generatePattern()
{
 Pattern temp;
 if (patternNumber == 1)
 {
 cout << "The chosen type is of patterType 1" << 
endl;
 drawCircle({patternXc, patternYc, radius});
 drawCircle({(patternXc + radius), 
(int)round(patternYc + 1.73 * radius), radius});
 drawCircle({patternXc + 2 * radius, patternYc, 
radius});
 drawCircle({patternXc + radius, 
(int)round(patternYc - 1.73 * radius), radius}); drawCircle({patternXc - radius, (int)round(patternYc 
- 1.73 * radius), radius});
 drawCircle({patternXc - 2 * radius, patternYc, 
radius});
 drawCircle({patternXc - radius, (int)round(patternYc 
+ 1.73 * radius), radius});
 drawCircle({patternXc, patternYc, 2 * radius});
 }
 else if (patternNumber == 3)
 {
 cout << "The chosen type is of patterType 2" << 
endl;
 drawCircle({patternXc, patternYc, radius});
 drawCircle({(patternXc + radius), 
(int)round(patternYc + 1.73 * radius), radius});
 drawCircle({patternXc + 2 * radius, patternYc, 
radius});
 drawCircle({patternXc + radius, 
(int)round(patternYc - 1.73 * radius), radius});
 drawCircle({patternXc - radius, (int)round(patternYc 
- 1.73 * radius), radius});
 drawCircle({patternXc - 2 * radius, patternYc, 
radius}); drawCircle({patternXc - radius, (int)round(patternYc 
+ 1.73 * radius), radius});
 drawCircle({patternXc, patternYc, 2 * radius});
 drawCircle({patternXc, patternYc, 3 * radius});
 }
 else if (patternNumber == 2)
 {
 cout << "The chosen type is of patternType 3" << 
endl;
 drawCircle({patternXc, patternYc, radius});
 drawCircle({patternXc, patternYc + radius, radius});
 drawCircle({(int)round(patternXc + 0.7 * radius), 
(int)round(patternYc + 0.7 * radius), radius});
 drawCircle({patternXc + radius, patternYc, radius});
 drawCircle({(int)round(patternXc + 0.7 * radius), 
(int)round(patternYc - 0.7 * radius), radius});
 drawCircle({patternXc, patternYc - radius, radius});
 drawCircle({(int)round(patternXc - 0.7 * radius), 
(int)round(patternYc - 0.7 * radius), radius});
 drawCircle({patternXc - radius, patternYc, radius});
 drawCircle({(int)round(patternXc - 0.7 * radius), 
(int)round(patternYc + 0.7 * radius), radius});
 drawCircle({patternXc, patternYc, 2 * radius});
 }}
void display()
{
}
void myMouseFunc(int button, int state, int x, int y)
{
 if (button == GLUT_LEFT_BUTTON && state == 
GLUT_DOWN)
 {
 if (drawMode)
 {
 patternXc = x;
 patternYc = 500 - y;
 generatePattern();
 }
 else if (colorMode)
 {
 if (algo == 'f')
 {
 floodFill(x, 500 - y);
 } else
 {
 boundaryFill(x, 500 - y);
 }
 }
 }
}
void myMenu(int value)
{
 glutIdleFunc(display);
 if (drawMode)
 {
 if (value == 1)
 {
 patternNumber = 1;
 cout << "Pattern 1 is selected" << endl;
 cout << "now enter the radius(a=5, b=10, c=15 and so on)" << endl;
 }
 else if (value == 2)
 { patternNumber = 2;
 cout << "Pattern 2 is selected" << endl;
 cout << "now enter the radius(a=5, b=10, c=15 and so on)" << endl;
 }
 else if (value == 3)
 {
 patternNumber = 3;
 cout << "Pattern 3 is selected" << endl;
 cout << "now enter the radius(a=5, b=10, c=15 and so on)" << endl;
 }
 }
 else if (colorMode)
 {
 if (value == 4)
 {
 fillColor = red;
 cout << "Red color is selected, select algo if not selected yet" << endl;
 }
 else if (value == 5)
 {
 fillColor = green; cout << "Green color is selected, select algo if not selected yet" << endl;
 }
 else if (value == 6)
 {
 fillColor = blue;
 cout << "Blue color is selected, select algo if not selected yet" << endl;
 }
 else if (value == 7)
 {
 algo = 'f';
 cout << "flood fill algorithm selected, select color if not selected yet" << endl;
 }
 else if (value == 8)
 {
 algo = 'b';
 cout << "boundary fill algorithm selected, select color if not selecte yet" << endl;
 }
 }
}void myKeyboard(unsigned char key, int x, int y)
{
 if ((int)key == 48)
 {
 drawMode = true;
 colorMode = false;
 cout << "Draw-mode selected.. " << endl;
 cout << "Right click and select the pattern type by again right clicking." << endl;
 }
 else if ((int)key == 49)
 {
 drawMode = false;
 colorMode = true;
 cout << "color-Mode selected.." << endl;
 cout << "Right click and select the color and algorithm to fill" << endl;
 }
 else
 {
 radius = ((int)key - 96) * 5;
 cout << "radius is equal to " << radius << endl;
 cout << "click the screen to select the central point for the pattern: " << endl; }
}
int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitWindowPosition(500, 500);
 glutInitWindowSize(500, 500);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutCreateWindow("Bresenham Circle");
 cout << "1. Draw mode (click 0)" << endl;
 cout << "2. Color mode (click 1)" << endl;
 init();
 glutMouseFunc(myMouseFunc);
 int subMenuId01 = glutCreateMenu(myMenu);
 glutAddMenuEntry("Pattern 1", 1);
 glutAddMenuEntry("Pattern 2", 2);
 glutAddMenuEntry("Pattern 3", 3);
 int subMenuId02 = glutCreateMenu(myMenu);
 glutAddMenuEntry("Red", 4);
 glutAddMenuEntry("Green", 5); glutAddMenuEntry("Blue", 6);
 int subMenuId03 = glutCreateMenu(myMenu);
 glutAddMenuEntry("Flood-Fill", 7);
 glutAddMenuEntry("Boundary-Fill", 8);
 glutCreateMenu(myMenu);
 glutAddSubMenu("Pattern", subMenuId01);
 glutAddSubMenu("Color", subMenuId02);
 glutAddSubMenu("Algorithm", subMenuId03);
 glutAttachMenu(GLUT_RIGHT_BUTTON);
 glutKeyboardFunc(myKeyboard);
 glutDisplayFunc(display);
 glutMainLoop();
}
