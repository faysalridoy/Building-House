#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

#define sqrt2 (sqrt(2))

typedef struct point
{
    double x,y,z;
} Point;

bool drawAxes = true;
float tyreAngle = 0;

float quadAngle = 0;
float boxAngle = 0;
float boxScaleFactor = 1;
float movefactor=1;
float windowmovefactor=0;
float rwindowmovefactor=0;
float bdoormovefactor=0;
float tyreScaleFactor = 1;
float tinyBoxAngle = 0;
float background = 0;

Point pos, u, r, l;

void displayAxes()
{
    if(drawAxes)
    {
        glBegin(GL_LINES);
        {
            glColor3f(1.0, 0, 0);

            glVertex3f( 500,0,0); // a point on pos x axis
            glVertex3f(-500,0,0); // a point on neg x axis

            glColor3f(0, 1.0, 0);

            glVertex3f(0,-500,0); // a point on pos y axis
            glVertex3f(0, 500,0); // a point on neg y axis

            glColor3f(0, 0, 1.0);

            glVertex3f(0,0, 500);  // a point on pos z axis
            glVertex3f(0,0,-500);   // a point on neg z axis
        }
        glEnd();
    }
}

Point func(Point vect, Point perp, int dir)
{
    double c = cos(pi/180);
    double s = dir * sin(pi/180);
    Point point;
    point.x = c * vect.x + s * perp.x;
    point.y = c * vect.y + s * perp.y;
    point.z = c * vect.z + s * perp.z;
    c = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
    point.x /= c;
    point.y /= c;
    point.z /= c;
    return point;
}
void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {
    case '1':
    {
        Point l1 = func(l, r, -1);
        r = func(r, l, 1);
        l = l1;
        break;
    }
    case '2':
    {
        Point l1 = func(l, r, 1);
        r = func(r, l, -1);
        l = l1;
        break;
    }

    case '3':
    {
        Point u1 = func(u, l, -1);
        l = func(l, u, 1);
        u = u1;
        break;
    }
    case '4':
    {
        Point u1 = func(u, l, 1);
        l = func(l, u, -1);
        u = u1;
        break;
    }
    case '5':
    {
        Point r1 = func(r, u, -1);
        u = func(u, r, 1);
        r = r1;
        break;
    }
    case '6':
    {
        Point r1 = func(r, u, 1);
        u = func(u, r, -1);
        r = r1;
        break;
    }

    case 'r':
    {
        quadAngle += 5;
        printf("Quad Angle %f\n", quadAngle);
        break;
    }
    case 'R':
    {
        quadAngle += 5;
        printf("Quad Angle %f\n", quadAngle);
        break;
    }
    case 'l':
    {
        quadAngle -= 5;
        printf("Quad Angle %f\n", quadAngle);
        break;
    }
    case 'L':
    {
        quadAngle -= 5;
        printf("Quad Angle %f\n", quadAngle);
        break;
    }



    case 'U':
    {
        if(!boxScaleFactor<2)
        {
            boxScaleFactor += 0.2;
            printf("Quad Angle %f\n", boxScaleFactor);
            break;
        }

    }
    case 'u':
    {
        if(boxScaleFactor<2)
        {
            boxScaleFactor += 0.2;
            printf("Quad Angle %f\n", boxScaleFactor);
            break;
        }


    }
    case 'D':
    {
        if(boxScaleFactor>0)
        {
            boxScaleFactor -= 0.2;
            printf("Quad Angle %f\n", boxScaleFactor);
            break;
        }

    }
    case 'd':
    {
        if(boxScaleFactor>0)
        {
            boxScaleFactor -= 0.2;
            printf("Quad Angle %f\n", boxScaleFactor);
            break;
        }

    }



    case '7':
    {
        tyreScaleFactor += 0.2;
        break;
    }
    case '8':
    {
        tyreScaleFactor -= 0.2;
        break;
    }


    case '9':
    {
        while(windowmovefactor <=45)
        {
            windowmovefactor +=3;

        }
        break;
    }

    case '0':
    {
      while(windowmovefactor =0)
        {
            windowmovefactor -=3;

        }
        break;
    }



    default:
        break;
    }
}

void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_DOWN: // down arrow
    {
        pos.y +=2;
        break;

    }


    case GLUT_KEY_UP:   // up arrow
    {
        pos.y -=2;
        break;


    }


    case GLUT_KEY_RIGHT:    // right arrow
    {
        pos.x -=2;
        break;
    }

    case GLUT_KEY_LEFT:     // left arrow
    {
        pos.x += 2;
        break;
    }

    case GLUT_KEY_PAGE_UP:
    {
        pos.z += 2;
        break;
    }

    case GLUT_KEY_PAGE_DOWN:
    {
        pos.z -= 2;
        break;
    }

    case GLUT_KEY_HOME:
    {
        if(movefactor>=(-55))
        {
            movefactor -= 5;
            break;
        }
    }

    case GLUT_KEY_END:
    {
        if(movefactor<=0)
        {
            movefactor += 5;
            break;
        }
    }

    default:
        break;
    }
}

void mouseListener(int button, int state, int x, int y) 	//x, y is the x-y of the screen (2D)
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN) // 2 times?? in ONE click? -- solution is checking DOWN or UP
        {
            printf("Mouse Left Button Clicked\n");
        }
        else if(state == GLUT_UP)
        {
            printf("Mouse Left Button Released\n");
        }
        break;
    default:
        break;
    }
}

void displayTyre(float tyreRadius, float tyreWidth)
{
    int tyreSlices = 36;
    float sliceWidth = (2 * M_PI * tyreRadius) / tyreSlices;
    float sliceAngle = 360 / tyreSlices;

    float halfTyreWidth = tyreWidth / 2, quartTyreWidth = halfTyreWidth / 2;
    float halfSliceWidth = sliceWidth / 2;

    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfTyreWidth, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, tyreRadius, 0);
        glVertex3f(-halfTyreWidth, -tyreRadius, 0);
        glVertex3f(halfTyreWidth, -tyreRadius, 0);
    }
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    {
        glVertex3f(halfTyreWidth, 0, tyreRadius);
        glVertex3f(halfTyreWidth, 0, -tyreRadius);
        glVertex3f(-halfTyreWidth, 0, -tyreRadius);
        glVertex3f(-halfTyreWidth, 0, tyreRadius);
    }
    glEnd();


    glColor3f(0.25, 0.5, 1);
    for(int i=0; i<tyreSlices; i++)
    {
        glPushMatrix();
        glRotatef(sliceAngle*i, 1, 0, 0);
        glTranslatef(0, tyreRadius, 0);
        glBegin(GL_QUADS);
        {
            glVertex3f(halfTyreWidth, 0, halfSliceWidth);
            glVertex3f(halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, -halfSliceWidth);
            glVertex3f(-halfTyreWidth, 0, halfSliceWidth);
        }
        glEnd();
        glPopMatrix();
    }
}

void displayQuad(float quadLength, float quadWidth) // width along x axis, length along z axis
{
    float halfQuadWidth = quadWidth / 2, halfQuadLength = quadLength / 2;

    glBegin(GL_QUADS);
    {
        /** Solid Fill Quad **/

        //glColor3f(1, 1, 0);

        //glVertex3f(halfQuadWidth, 0, halfQuadLength);
        //glVertex3f(halfQuadWidth, 0, -halfQuadLength);
        //glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        //glVertex3f(-halfQuadWidth, 0, halfQuadLength);

        /** Gradient Fill Quad **/


        glColor3f(1, 1, 0);

        glVertex3f(halfQuadWidth, 0, halfQuadLength);
        glVertex3f(halfQuadWidth, 0, -halfQuadLength);

        glColor3f(0, 1, 1);

        glVertex3f(-halfQuadWidth, 0, -halfQuadLength);
        glVertex3f(-halfQuadWidth, 0, halfQuadLength);

    }
    glEnd();
}

void displayBox(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0, 0, 0.25);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 0, 0.75);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayBox4(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(1, 0.75, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(1, 0.25, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayBox3(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0, 0.25, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0, 0.75, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
void displayBox2(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 0, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
void displayBox5(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 1, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(1, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayBox6(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 1, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(1, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayBox7(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 1, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(1, 0, 1);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
void displayBox8(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.43, 0.44, 0.46);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.30, 0.33, 0.35);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.25, 0.25, 0.25);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
void displayBox9(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0, 0.75, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0, 0.25, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
void displayBox10(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.73, 0.74, 0.76);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.69, 0.60, 0.70);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.55, 0.56, 0.58);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
void displayBox11(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 0.75, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(1, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(1, 0.25, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}


void displayBox12(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.73, 0.74, 0.76);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.69, 0.60, 0.70);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.55, 0.56, 0.58);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}




void displayBox13(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.43, 0.44, 0.46);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.30,0.33, 0.35);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.25, 0.25, 0.25);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayBox14(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.73, 0.74, 0.76);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.69, 0.60, 0.70);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.55, 0.56, 0.58);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}

void displayBox15(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0, 0.75, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0, 0.25, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}



void displayBox16(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(0.73, 0.74, 0.76);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(0.69, 0.60, 0.70);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(0.55, 0.56, 0.58);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}
void displayBox17(float boxLength, float boxWidth, float boxHeight) // length -> x axis, width -> yaxis, height -> z axis
{
    float halfBoxLength = boxLength / 2, halfBoxWidth = boxWidth / 2, halfBoxHeight = boxHeight / 2;
    glBegin(GL_QUADS);
    {
        glColor3f(1, 0.75, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);

        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);


        glColor3f(1, 1, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glColor3f(1, 0.25, 0);

        glVertex3f(halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, halfBoxHeight);

        glVertex3f(halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, halfBoxWidth, -halfBoxHeight);
        glVertex3f(-halfBoxLength, -halfBoxWidth, -halfBoxHeight);
        glVertex3f(halfBoxLength, -halfBoxWidth, -halfBoxHeight);
    }
    glEnd();
}









void displayScene()
{
    //Primitive Object dimensions

    float quadLength = 100, quadWidth = 60;
    float largeBoxLength = 500, largeBoxWidth = 300, largeBoxHeight = 36;
    float smallBoxLength = 480, smallBoxWidth = 280, smallBoxHeight = 250;
    float upperBoxLength = 490, upperBoxWidth = 290, upperBoxHeight = 15;
    float topBoxLength = 200, topBoxWidth = 100, topBoxHeight = 200;

    float s1BoxLength = 190, s1BoxWidth = 110, s1BoxHeight = 12;
    float s2BoxLength = 160, s2BoxWidth = 105, s2BoxHeight = 12;
    float s3BoxLength = 130, s3BoxWidth = 100, s3BoxHeight = 12;

    float doorlBoxLength = 60, doorlBoxWidth = 3, doorlBoxHeight = 180;
    float doorrBoxLength = 60, doorrBoxWidth = 3, doorrBoxHeight = 180;
    float updoorBoxLength = 120, updoorBoxWidth = 8, updoorBoxHeight = 10;
    float windowBoxLength = 20, windowBoxWidth = 100, windowBoxHeight = 95;
    float upwinBoxLength = 20, upwinBoxWidth = 105, upwinBoxHeight = 8;







    float tinyBoxLength = 10, tinyBoxWidth = 10, tinyBoxHeight = 10;
    float tyreRadius = 100, tyreWidth = 40;




    /** Principal Axes **/

    displayAxes();

    /**/

    /** Quad **/

    //glRotatef(quadAngle, 1, 0, 0); // rotates with respect to x axis
    //glRotatef(quadAngle, 0, 1, 0); // rotates with respect to y axis
    //glRotatef(quadAngle, 0, 0, 1); // rotates with respect to z axis
    //displayQuad(quadLength, quadWidth);

    /**/

    /** Single Box **/

    //glTranslatef(150, 0, 0); // rotation applied first, translation applied second
    //glRotatef(boxAngle, 1, 0, 0); // rotates with respect to x axis
    //glRotatef(boxAngle, 0, 1, 0); // rotates with respect to y axis
    //glRotatef(boxAngle, 0, 0, 1); // roytates with respect to z axis
    //glTranslatef(150, 0, 0);    // translation applied first, rotation applied second
    //displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight);

    /**/

    /** Double Box Stack **/

    //glRotatef(boxAngle, 0, 0, 1); // rotation applied to both boxes
    //glTranslatef(-300, 100, 100); // translation applied to both boxes
    //displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    //glRotatef(boxAngle, 0, 0, 1);   // rotation applied only on the small box
    //glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    //displayBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box

    /**/

    /** Double Box Stack - Push Pop Matrix **/


    /*glRotatef(boxAngle, 0, 0, 1); // rotation applied to both boxes

    //glPushMatrix(); // saves the matrix just before scaling, to prevent scale effect to anything other than the large box
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor); // without push-pop, scale will be applied to both boxes
    displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    //glPopMatrix();

    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    displayBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box
    */


    /**/

    /** Tyre **/

    /*glRotatef(tyreAngle, 1, 0, 0); // roates the tyre w.r.t x axis
    glRotatef(tyreAngle, 0, 1, 0); // roates the tyre w.r.t y axis
    glRotatef(tyreAngle, 0, 0, 1); // roates the tyre w.r.t z axis
    displayTyre(tyreRadius, tyreWidth);
    */
    /**/

    /** Tyre Double Box Stack **/

    /*glPushMatrix();
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    displayBox(smallBoxLength, smallBoxWidth, smallBoxHeight); // small box
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 0, tyreRadius+smallBoxHeight+(largeBoxHeight/2)); // places the tyre on top of both boxes
    glRotatef(tyreAngle, 1, 0, 0); // check what happens to the tyre after exchanging the order of translation and roation
    glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
    displayTyre(tyreRadius, tyreWidth);
    glPopMatrix();
    */

    /** Animate Function **/
    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    displayBox(largeBoxLength, largeBoxWidth, largeBoxHeight); // large box
    glPopMatrix();

    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(0, 0, (smallBoxHeight/2) + (largeBoxHeight/2)); // places the small box on top of the large box
    displayBox2(smallBoxLength, smallBoxWidth, smallBoxHeight); // house body box
    glPopMatrix();

    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(0, 0, (upperBoxHeight) + (smallBoxHeight)+2); // places the upp
    displayBox3(upperBoxLength, upperBoxWidth, upperBoxHeight); //  upper box
    glPopMatrix();

    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(0, 0, (topBoxHeight/2) + (smallBoxHeight+upperBoxHeight)); // places the small box on top of the large box
    displayBox4(topBoxLength, topBoxWidth, topBoxHeight); //  topbox
    glPopMatrix();



    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(0,(s1BoxWidth/2) + (largeBoxWidth/2),-((largeBoxHeight/2)-5)); // places the small box on top of the large box
    displayBox5(s1BoxLength, s1BoxWidth, s1BoxHeight); //  stair-1-base
    glPopMatrix();


    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(0,(s2BoxWidth/2)+s1BoxWidth+33,-1); // places the small box on top of the large box
    displayBox6(s2BoxLength, s2BoxWidth, s2BoxHeight); //  stair-2-upperbase
    glPopMatrix();


    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(0,((s3BoxWidth/2)+s2BoxWidth)+33,largeBoxHeight/2-6.5); // places the small box on top of the large box
    displayBox7(s3BoxLength, s3BoxWidth, s3BoxHeight); //  stair-3-top
    glPopMatrix();



    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(-movefactor,0,0);
    glTranslatef(30,smallBoxWidth/2, (doorlBoxHeight/2)+ (s3BoxHeight/2)); // places the small box on top of the large box
    displayBox8(doorlBoxLength, doorlBoxWidth, doorlBoxHeight); // leftdoor box
    glPopMatrix();




    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(movefactor,0,0);
    glTranslatef(-30,smallBoxWidth/2, (doorrBoxHeight/2)+ (s3BoxHeight/2)); // places the small box on top of the large box
    displayBox12(doorrBoxLength, doorrBoxWidth, doorrBoxHeight); // righttdoor box
    glPopMatrix();



    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(0,smallBoxWidth/2, (updoorBoxHeight/2)+ (doorlBoxHeight)+5); // places the small box on top of the large box
    displayBox9(updoorBoxLength, updoorBoxWidth, updoorBoxHeight); // updoor box
    glPopMatrix();

    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(0,0,windowmovefactor);
    glTranslatef(231, 0, (windowBoxHeight/2) + (largeBoxHeight/2)+50); // places the small box on top of the large box
    displayBox10(windowBoxLength, windowBoxWidth, windowBoxHeight); // window
    glPopMatrix();


    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(233,0, (upwinBoxHeight/2) + (largeBoxHeight/2)+140); // places the small box on top of the large box
    displayBox11(upwinBoxLength, upwinBoxWidth, upwinBoxHeight); // upwindow box
    glPopMatrix();





    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(-bdoormovefactor,0,0);
    glTranslatef(30,-(smallBoxWidth/2), (doorlBoxHeight/2)+ (s3BoxHeight/2)); // places the small box on top of the large box
    displayBox13(doorlBoxLength, doorlBoxWidth, doorlBoxHeight); // backleftdoor box
    glPopMatrix();




    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(bdoormovefactor,0,0);
    glTranslatef(-30,-(smallBoxWidth/2), (doorrBoxHeight/2)+ (s3BoxHeight/2)); // places the small box on top of the large box
    displayBox14(doorrBoxLength, doorrBoxWidth, doorrBoxHeight); // backrighttdoor box
    glPopMatrix();



    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(0,-(smallBoxWidth/2), (updoorBoxHeight/2)+ (doorlBoxHeight)+5); // places the small box on top of the large box
    displayBox15(updoorBoxLength, updoorBoxWidth, updoorBoxHeight); // backupupdoor box
    glPopMatrix();





    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(0,0,rwindowmovefactor);
    glTranslatef(-231, 0, (windowBoxHeight/2) + (largeBoxHeight/2)+50); // places the small box on top of the large box
    displayBox16(windowBoxLength, windowBoxWidth, windowBoxHeight); // window right side
    glPopMatrix();


    glPushMatrix();
    glRotatef(quadAngle, 0, 0, 1);
    glScalef(boxScaleFactor, boxScaleFactor, boxScaleFactor);
    glTranslatef(-233,0, (upwinBoxHeight/2) + (largeBoxHeight/2)+140); // places the small box on top of the large box
    displayBox17(upwinBoxLength, upwinBoxWidth, upwinBoxHeight); // upwindow box right side
    glPopMatrix();




    /*
        glPushMatrix();
        glTranslatef(0, 0, tyreRadius+smallBoxHeight+(largeBoxHeight/2)); // places the tyre on top of both boxes
        glRotatef(tyreAngle, 1, 0, 0); // check what happens to the tyre after exchanging the order of translation and roation
        glScalef(tyreScaleFactor, tyreScaleFactor, tyreScaleFactor);
        displayTyre(tyreRadius, tyreWidth); // tyre
        glPopMatrix();

        glPushMatrix();
        glRotatef(tinyBoxAngle, 0, 0, 1); // angle is updated in animate function
        glTranslatef(250, 40, 50);
        displayBox(tinyBoxLength, tinyBoxWidth, tinyBoxHeight);
        glPopMatrix();
        */
}





void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(background, background, background,0);	//sets background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // sets the current matrix to identity
    gluLookAt(pos.x, pos.y, pos.z, pos.x+l.x, pos.y+l.y, pos.z+l.z, u.x, u.y, u.z); // sets camera position and direction

    displayScene();

    glutSwapBuffers();
}



void animate()
{
    tinyBoxAngle += 0.05;
    glutPostRedisplay();
}


void init()
{
    glClearColor(background, background, background,0); 	//sets background color

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity(); // sets the current matrix to identity
    gluPerspective(80,	1,	1,	1000.0);

    // to understand the following values, read the specification pdf
    double d = 1 / sqrt2;
    pos = {300, 300, 150};
    u = {0, 0, 1};
    r = {-d, d, 0};
    l = {-d, -d, 0};
}

void subMenu1(int id)
{
    if(id == 3)
    {
        background = 1;
    }
    else if(id == 4)
    {
        background = 0;
    }
}

void subMenu2(int id)
{
    if(id == 5)
    {
        while(rwindowmovefactor <=45)
        {
            rwindowmovefactor +=3;

        }
    }
    else if(id == 6)
    {
        while(rwindowmovefactor =0)
        {
            rwindowmovefactor -=3;

        }
    }
}
void subMenu3(int id)
{
    if(id == 8)
    {
        for(int i=0; i<=11; i++)
        {
            if(bdoormovefactor>=(-55))
            {
                bdoormovefactor -= 5;
            }
        }

    }
    else if(id == 7)
    {
        for(int i=0; i<=11; i++)
        {
            if(bdoormovefactor<=0)
            {
                bdoormovefactor += 5;

            }
        }
    }
}






void mainMenu(int id)
{
    if(id == 1)
    {
        drawAxes = true;
    }
    else if(id == 2)
    {
        drawAxes = false;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
    glutCreateWindow("My OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    int subMenuNo1 = glutCreateMenu(subMenu1);
    glutAddMenuEntry("White", 3);
    glutAddMenuEntry("Black", 4);

    int subMenuNo2 = glutCreateMenu(subMenu2);
    glutAddMenuEntry("Sliding Up", 5);
    glutAddMenuEntry("Sliding Down", 6);

    int subMenuNo3 = glutCreateMenu(subMenu3);
    glutAddMenuEntry("Close", 7);
    glutAddMenuEntry("Open", 8);

    glutCreateMenu(mainMenu);
    glutAddMenuEntry("Axes On", 1);
    glutAddMenuEntry("Axes Off", 2);
    glutAddSubMenu("Background", subMenuNo1);
    glutAddSubMenu("Sliding Window", subMenuNo2);
    glutAddSubMenu("Back Door", subMenuNo3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();		//The main loop of OpenGL, this function never returns

    return 0;
}
