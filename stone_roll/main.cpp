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
#include <string.h>

using namespace std;
GLfloat pallet[10][3] ={};
GLfloat width = 10;
GLfloat x_location = 0.0;
GLfloat y_location = 0.0;
GLfloat x = 0.3;

void DrawFloor()
{
    //draw floor
    glPushMatrix(); //push translate view
    glBegin(GL_POLYGON);
    glColor3f(pallet[2][0],pallet[2][1],pallet[2][2]);
    glVertex3f(-10.0,-5.0,0.0);
    glVertex3f( 10.0,-5.0,0.0);
    glVertex3f( 10.0,-3.5,0.0);
    glVertex3f(-10.0,-3.5,0.0);
    glEnd();
    glPopMatrix();
}

class NPC {
private :
    int color;
    GLfloat npc_x;
    GLfloat npc_y;
public :
    NPC(GLfloat x, GLfloat y, int c)
        : npc_x(x), npc_y(y), color(c)
    {

    }
    void draw_NPC()
    {
        glPushMatrix();
            glTranslatef(npc_x,npc_y,0.0);

        glPushMatrix();
            glColor3f(pallet[color][1],pallet[color][0],pallet[color][2]);
            glutSolidCube(2.5 * x);
        glPopMatrix();

        glPushMatrix();
            glBegin(GL_LINES);
                glColor3f(1.0 - pallet[color][1], 1.0 - pallet[color][0],1.0 - pallet[color][2]);
                glVertex3f(0.5 * x,0.5 * x,0.0);
                glVertex3f(x,x,0.0);
                glVertex3f(-0.5 * x,0.5 * x,0.0);
                glVertex3f(-x,x,0.0);
            glEnd();
            glBegin(GL_POLYGON);
                glColor3f(1.0 - pallet[color][1], 1.0 - pallet[color][0],1.0 - pallet[color][2]);
                glVertex3f(0.0, 0.0 ,0.0);
                glVertex3f(-x,-x,0.0);
                glVertex3f(x,-x,0.0);
            glEnd();
        glPopMatrix();

        glPopMatrix();

    }

    void touch_NPC()
    {
        if( -1 == ( x_location - npc_x) && y_location == npc_y)
        {
            npc_x += 1.0;
        }
        else if( ( x_location - npc_x) == 1 && y_location == npc_y )
        {
            npc_x -= 1.0;
        }
        else if( -1 == ( y_location - npc_y) && x_location == npc_x )
        {
            npc_y += 1.0;
        }
        else if(( y_location - npc_y) == 1 && x_location == npc_x)
        {
            npc_y -= 1.0;
        }

    }
};
NPC np1(5.0, 5.0,1); // call class npc
NPC np2(-5.0,-5.0,2); // call class npc
NPC np3(-5.0, 5.0,3); // call class npc

void DrawChar() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); //push orgin view
    glTranslatef(x_location,y_location,0.0); //translate as much as keyboard callback

    //draw face
    glPushMatrix();
    glTranslatef(0.0, -0.2, 0.0);
    glScalef(1.0,1.0,1.0);
    glColor3f(pallet[0][2],pallet[0][1],pallet[0][0]);
    glutSolidSphere(x,30,30);
    glPopMatrix();

    //draw cap
    glPushMatrix(); //push translate view
    glBegin(GL_POLYGON);
    glColor3f(pallet[0][0],pallet[0][1],pallet[0][2]);
    glVertex3f(x,-x/4.0,0.0);
    glVertex3f(x,x/2.0,0.0);
    glVertex3f(-1.0 * x,x/2.0,0.0);
    glVertex3f(-1.0 * x,-x/2.0,0.0);
    glVertex3f(2.0 * x,-x/2.0 ,0.0);
    glVertex3f(2.0 * x,-x/4.0 ,0.0);
    glEnd();
    glPopMatrix(); // return to translate view


    glPopMatrix(); // Eliminate translate view


}



void changeColor()
{
    srand((unsigned int)time(0));
    for(int i = 2;i<10;i++)
    {
        for(int j = 0; j< 3; j++)
            pallet[i][j] = (float)(rand()%256)/256;
    }
}

void Idlefunc()
{
    glClear(GL_COLOR_BUFFER_BIT);
    DrawChar();
    np1.draw_NPC();
    np2.draw_NPC();
    np3.draw_NPC();
    glFlush();

    glutPostRedisplay();
}


void MyKeyboard(unsigned char key, int p, int k) {
 switch (key) {
 case 'd':
     if(x_location < width - x)
        x_location=x_location+1;
    break;
 case 'a':
     if(x_location > -1.0 * width + x)
         x_location=x_location-1;
    break;
 case 'w':
     if(y_location < width - x)
        y_location=y_location+1;
    break;
 case 's':
     if(y_location > -1.0 * width + x)
         y_location=y_location-1;
     break;
 case 32 :
    np1.touch_NPC();
    np2.touch_NPC();
    np3.touch_NPC();
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
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-8.0,8.0,-8.0,8.0,-5.0,5.0);
    glutDisplayFunc(DrawChar);
    glutIdleFunc(Idlefunc);
    glutKeyboardFunc(MyKeyboard);
    glutMainLoop();
    return 0;
}
