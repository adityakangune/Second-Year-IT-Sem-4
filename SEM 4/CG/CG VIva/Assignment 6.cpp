



#include<GL/glut.h>
#include<stdio.h>

#include<math.h>

static int flag;

int length, xi, yi, choice;
double angle, ET[3][3], ETResult[3][3];
double Rh[4][4], RhResult[4][4];

//------------------DRAW-------------//

void drawET(double ET[3][3])
{
        int i;

        glBegin(GL_LINE_LOOP);
        for(i=0;i<3;i++)
        {
         glVertex2i(ET[i][0],ET[i][1]);
        }
        glEnd();
}

void drawR(double Rh[4][4])
{
        int i;
     
        glBegin(GL_LINE_LOOP);
        for(i=0;i<4;i++)
        {
         glVertex2i(Rh[i][0],Rh[i][1]);
        }
        glEnd();
}
//----------------------------Display---------------------//

void Display()
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
 
    glLoadIdentity();
    gluOrtho2D(-320,320,-240,240);//note

    glColor3f(1,1,1);
    glBegin(GL_LINES);
        glVertex2d(-320,0);
        glVertex2d(320,0);
        glVertex2d(0,-240);
        glVertex2d(0,240);
    glEnd();
 
    glColor3f(1,0,0);
    if(flag == 0)
     drawET(ET);
    else if(flag == 1)
     drawR(Rh);

    glFlush();
}


//---------MULTIPLY--------------//

void mult3X3(double ET[3][3],double temp[3][3])
{
 double sum;
 int i,j,k;
    for(i=0;i<3;i++)
    {
       for(j=0;j<3;j++)
        {     
         sum=0;
            for(k=0;k<3;k++)
            {
               sum=sum+ET[i][k]*temp[k][j];
            }
            ETResult[i][j]=sum;
        }
    }
}

void mult4X4(double Rh[4][4],double temp[4][4])
{
 double sum;
    int i,j,k;     
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {     
         sum=0;
            for(k=0;k<4;k++)
            {
                sum=sum+Rh[i][k]*temp[k][j];
   }                             
            RhResult[i][j]=sum;
        }
 }
}

//----------Translation-----------//

void translationET()
{
 double tx,ty,temp[3][3];

    printf("\nTranslating Equilateral triangle");
    printf("\nEnter Tx: ");
    scanf("%lf",&tx);
    printf("\nEnter Ty: ");
    scanf("%lf",&ty);

 temp[3][3]={0};     
    temp[0][0]=1;
    temp[1][1]=1;
    temp[2][2]=1;
    temp[2][0]=tx;
    temp[2][1]=ty;

    mult3X3(ET,temp); 
    glColor3f(0.0,1.0,0.0);
    drawET(ETResult);
}

void translationRh()
{
 double tx,ty,temp[4][4];

    printf("\nTranslating Rhombus");
    printf("\nEnter Tx: ");
    scanf("%lf",&tx);
    printf("\nEnter Ty: ");
 scanf("%lf",&ty);

    temp[4][4]={0};
    temp[0][0]=1;     
 temp[1][1]=1;
 temp[2][2]=1;
 temp[3][3]=1;
 temp[3][0]=tx;
    temp[3][1]=ty;

    mult4X4(Rh,temp);     
    glColor3f(0.0,1.0,0.0);
    drawR(RhResult);
}

//------------Rotation------------//

void rotationET()
{
 double rx,ry,angle, temp[3][3];

    printf("\n**ROTATION**\n");                             
    printf("\nArbitrary Point (x,y) : ");
    scanf("%lf %lf",&rx,&ry);
    printf("\nAngle (in degrees) : ");
    scanf("%lf",&angle);

    angle=angle*(M_PI/180);

    temp[3][3]={0};                                 
    temp[0][0]=cos(angle);
    temp[0][1]=sin(angle);
    temp[1][0]=-sin(angle);
    temp[1][1]=cos(angle);
    temp[2][0]=(-(rx*cos(angle))+(ry*sin(angle))+rx);
    temp[2][1]=(-(rx*sin(angle))-(ry*cos(angle))+ry);
    temp[2][2]=1;

    mult3X3(ET,temp);     
    glColor3f(0.0,1.0,0.0);
    drawET(ETResult);
}

void rotationRh()
{
 double rx,ry,angle, temp[4][4];

    printf("\nRotating Rhombus");                             
    printf("\nArbitrary Point (x,y): ");
    scanf("%lf %lf",&rx,&ry);
    printf("\nAngle (in degree): ");
    scanf("%lf",&angle);
 
    angle=angle*(M_PI/180);

    temp[4][4]={0};                                 
    temp[0][0]=cos(angle);
    temp[0][1]=sin(angle);
    temp[1][0]=-sin(angle);
    temp[1][1]=cos(angle);
    temp[2][2]=1;
    temp[3][0]=(-(rx*cos(angle))+(ry*sin(angle))+rx);
    temp[3][1]=(-(rx*sin(angle))-(ry*cos(angle))+ry);
    temp[3][3]=1;

    mult4X4(Rh,temp);     
    glColor3f(0.0,1.0,0.0);
    drawR(RhResult);
}

//----------Scaling-------------//

void scaleET()
{
 double sx,sy, temp[3][3];

    printf("\nScaling Equilateral triangle");
    printf("\nSx: ");
    scanf("%lf",&sx);
    printf("\nSy: ");
    scanf("%lf",&sy);

    temp[3][3]={0};
 temp[0][0]=sx;     
 temp[1][1]=sy;
 temp[2][2]=1;

    mult3X3(ET,temp);     
    glColor3f(1.0,1.0,0.0);
    drawET(ETResult);
}

void scaleRh()
{
    double sx,sy,temp[4][4];

    printf("\nScaling Rhombus");
    printf("\nSx: ");
    scanf("%lf",&sx);
    printf("\nSy: ");
    scanf("%lf",&sy);

    temp[4][4]={0};
 temp[0][0]=sx;     
 temp[1][1]=sy;
 temp[2][2]=1;
 temp[3][3]=1;

    mult4X4(Rh,temp);     
    glColor3f(1.0,1.0,0.0);
    drawR(RhResult);
}

//-----------Shearing-------------//
void shearET()
{
 double xs,ys,temp[3][3];

    printf("\nShear Equilateral triangle");
    printf("\nPress 1: X - Shear");
    printf("\nPress 2: Y - Shear");
    printf("\nEnter your Choice: ");
    scanf("%d",&choice);

    temp[3][3]={0};

    switch(choice)
    {
     case 1: printf("\nX-shear value: ");
       scanf("%lf",&xs);
                temp[0][0]=1;
                temp[1][0]=xs;
                temp[1][1]=1;
                temp[2][2]=1;             
                break;
  case 2: printf("\nY-shear value: ");
       scanf("%lf",&ys);
    temp[0][0]=1;
    temp[0][1]=ys;
    temp[1][1]=1;
    temp[2][2]=1;                             
                break;
    }

    mult3X3(ET,temp);     
    glColor3f(1.0,1.0,0.0);
    drawET(ETResult);
}

void shearRh()
{
 double xs,ys,temp[4][4];

    printf("\nPress 1: X - Shear");
    printf("\nPress 2: Y - Shear");
    printf("\nEnter your Choice: ");
    scanf("%d",&choice);

    temp[4][4]={0};
     
    switch(choice)
    {
     case 1: printf("\nX-shear value: ");
                scanf("%lf",&xs);
                temp[0][0]=1;
                temp[1][0]=xs;
                temp[1][1]=1;
                temp[2][2]=1;
                temp[3][3]=1;             
                break;
  case 2: printf("\nY-shear value: ");
       scanf("%lf",&ys);
                temp[0][0]=1;
                temp[0][1]=ys;
                temp[1][1]=1;
                temp[2][2]=1;
                temp[3][3]=1;
                break;
 }     
    mult4X4(Rh,temp);
    glColor3f(0.0,1.0,0.0);
    drawR(RhResult);
}

//----------MENU--------------//
void Menu(int item)
{     
 switch(item)
    {         
        case 1: if(choice==1) 
                 translationET();
                else
                 translationRh();

                break;

        case 2: if(choice==1)
                 rotationET();     
                else
                 rotationRh();

                break;                     
        case 3: if(choice==1)
                 scaleET();
                else
                 scaleRh();

                break;                     
        case 4: if(choice==1)
                {
                 shearET();
                }
                else
                {
                 shearRh();
                }
                break;                     
        case 5:
          exit(0);
          break;
    }
}

//----------MAIN-------------------//

int main(int argc,char** argv)
{
    printf("\n*MENU");
    printf("\n1. To draw Equilateral Triangle");
    printf("\n2. To draw Rhombus");
    printf("\n3. To Exit");
    printf("\nEnter your choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
     int i, j;

       case 1:
         flag = 0;
         printf("\nEnter X co-ordinate of a Base point: ");
         scanf("%d",&xi);
         printf("\nEnter Y co-ordinate of the Base point: ");
          scanf("%d",&yi);
          printf("\nEnter length of sides: ");
          scanf("%d",&length);

          for(i=0;i<3;i++)
                {
                 for(j=0;j<3;j++)
                    {
                        ET[i][j]=1;
                    }
                }   
          ET[0][0]=xi;
          ET[0][1]=yi;
          ET[1][0]=xi+length;
          ET[1][1]=yi;
          ET[2][0]=length/2+xi;
          ET[2][1]=(sqrt(3)/2*length)+yi;
          break;

        case 2:
          flag = 1;
          printf("\nEnter X co-ordinates of a Base point: ");
          scanf("%d",&xi);
          printf("\nEnter Y co-ordinates of the Base point: ");
          scanf("%d",&yi);
          printf("\nEnter length of sides: ");
          scanf("%d",&length);
          printf("\nEnter angle of Rhombus (in degrees): ");
          scanf("%lf",&angle);
          angle = angle * M_PI / 180;

          for(i=0;i<4;i++)
                {
                 for(j=0;j<4;j++)
                    {
                        Rh[i][j]=1;
                    }
                }     
          Rh[0][0]=xi;
          Rh[0][1]=yi;
          Rh[1][0]=xi+length;
          Rh[1][1]=yi;
          Rh[2][0]=length+xi+length*cos(angle);
          Rh[2][1]=yi+length*sin(angle);
          Rh[3][0]=xi+length*cos(angle);
          Rh[3][1]=yi+length*sin(angle);
          break;

        case 3:
          exit(0);
          break;

        default:printf("\nInvalid Input!");
          break;
 }
 
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("2D - TRANSFORMATIONS");

    glutDisplayFunc(Display);

    glutCreateMenu(Menu);
     glutAddMenuEntry("1.Translation",1);
     glutAddMenuEntry("2.Rotation",2);
     glutAddMenuEntry("3.Scaling",3);
     glutAddMenuEntry("4.Shear",4);
     glutAddMenuEntry("5.EXIT",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}

