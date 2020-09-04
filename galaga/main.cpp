/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <iostream>
using namespace std;

//GLfloat MyVertices[8][3] = {{-0.25,-0.25,0.25}, {-0.25,0.25,0.25}, {0.25,0.25,0.25},{0.25,-0.25,0.25},
//                            {-0.25,-0.25,-0.25}, {-0.25,0.25,-0.25}, {0.25,0.25,-0.25}, {0.25,-0.25,-0.25} };

GLfloat pallet[10][3] ={};
//GLubyte MyVertexList[24] = {0,3,2,1, 2,3,6,7, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4};

int color1,color2,color3;
GLfloat width = 5;
GLfloat x_location = 0.0;
GLfloat x = 1.0;
GLfloat obs_y = 5.0;
GLfloat obs_x = 0.0;
int heart_count = 3;


void DrawAirplane() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); //push orgin view

    glTranslatef(x_location,-3.0,0.0); //translate as much as keyboard callback

    //draw wing edge
    glPushMatrix(); //push translate view
    glScalef(1.1,1.0,1.0);
    glBegin(GL_POLYGON);
    glColor3f(pallet[0][0],pallet[0][1],pallet[0][2]);
    glVertex3f(x,-x,0.0);
    glVertex3f(x,-x/2.0,0.0);
    glVertex3f(x/2.0,0.0,0.0);
    glVertex3f(-x/2.0,0.0,0.0);
    glVertex3f(-x,-x/2.0,0.0);
    glVertex3f(-x,-x,0.0);
    glEnd();
    glPopMatrix(); // return to translate view

    //draw wing
    glBegin(GL_POLYGON);
    glColor3f(pallet[1][0],pallet[1][1],pallet[1][2]);
    glVertex3f(0,-x,0.0);
    glVertex3f(x,-x,0.0);
    glVertex3f(x,-x/2.0,0.0);
    glVertex3f(x/2.0,0.0,0.0);
    glVertex3f(0.0,x,0.0);
    glEnd();

    //draw wing
    glBegin(GL_POLYGON);
    glColor3f(pallet[1][0],pallet[1][1],pallet[1][2]);
    glVertex3f(-x/2.0,0.0,0.0);
    glVertex3f(-x,-x/2.0,0.0);
    glVertex3f(-x,-x,0.0);
    glVertex3f(0,-x,0.0);
    glVertex3f(0.0,x,0.0);
    glEnd();

    //eliminate bottom triangle
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,0.0);
    glVertex3f(0.0,-x/3.0,0.0);
    glVertex3f(-x,-x,0.0);
    glVertex3f(x,-x,0.0);
    glEnd();

    //draw bottom long tale
    glBegin(GL_POLYGON);
    glColor3f(pallet[1][0],pallet[1][1],pallet[1][2]);
    glVertex3f(-x/7.0,0.0,0.0);
    glVertex3f(-x/7.0,-x,0.0);
    glVertex3f(x/7.0,-x,0.0);
    glVertex3f(x/7.0,0.0,0.0);
    glEnd();

    //draw bottom short tale
    glBegin(GL_POLYGON);
    glColor3f(pallet[1][0],pallet[1][1],pallet[1][2]);
    glVertex3f(-x/4.0,0.0,0.0);
    glVertex3f(-x/4.0,-x/1.5,0.0);
    glVertex3f(x/4.0,-x/1.5,0.0);
    glVertex3f(x/4.0,0.0,0.0);
    glEnd();

    //draw window
    glPushMatrix();
    glTranslatef(0.0, 0.2, 0.0);
    glScalef(1.0,2.0,1.0);
    glColor3f(pallet[2][0],pallet[2][1],pallet[2][2]);
    glutSolidSphere(0.15 *x,30,30);
    glPopMatrix();

    glPopMatrix(); // Eliminate translate view


}

void DrawObstacle()
{
    glPushMatrix();
    glTranslatef(obs_x,obs_y,0.0);
        glColor3f(1.0,1.0,0.0);
        glutSolidCube(0.3);
    glPopMatrix();

}

void DrawHeart()
{
    for(int i = 0; i < heart_count;i++)
    {
        glPushMatrix();
        glTranslatef(4.5 - 0.5 *i,4.0,0.0);
        glScalef(1.0,2.0,1.0);
            glColor3f(1.0,0.0,0.0);
            glutSolidSphere(0.15,30,30);
        glPopMatrix();
    }
}

void Idlefunc()
{
    glClear(GL_COLOR_BUFFER_BIT);
    DrawAirplane();
    DrawObstacle();
    DrawHeart();
    glFlush();
    // change obstacle position
    if(obs_y < -3.0 && obs_x < x_location + x && x_location - x < obs_x)
    {
        if(heart_count <= 0)
            exit(1);
        else
        {
            heart_count -= 1;
            obs_y = 5.0;
            obs_x = (float)(rand()%10)- 5;
        }
    }
    else if(obs_y < -5.0)
    {
        obs_y = 5.0;
        obs_x = (float)(rand()%10)- 5;
    }
    else
    {
        obs_y = obs_y - 0.01;
    }

    glutPostRedisplay();
}


void MyKeyboard(unsigned char key, int p, int k) {
 switch (key) {
 case 'd':
     if(x_location < width - x)
        x_location=x_location+0.3;
    break;
 case 'a':
     if(x_location > -1.0 * width + x)
         x_location=x_location-0.3;
    break;
 default:
     break;

 }
 glutPostRedisplay();
}



int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("AIRPLANE");
    srand((unsigned int)time(0));
    for(int i = 0;i<10;i++)
    {
        for(int j = 0; j< 3; j++)
            pallet[i][j] = (float)(rand()%256)/256;
    }
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0,5.0,-5.0,5.0,-5.0,5.0);
    glutDisplayFunc(DrawAirplane);
    glutIdleFunc(Idlefunc);
    glutKeyboardFunc(MyKeyboard);
    glutMainLoop();
    return 0;
}
