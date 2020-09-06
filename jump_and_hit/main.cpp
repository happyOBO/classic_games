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
GLfloat width = 10;
GLfloat x_location = 0.0;
GLfloat y_location = 0.0;
GLfloat x = 0.3;
GLfloat boss_y = -3.0;
GLfloat boss_x = 7.0;
GLfloat obs_y = 0.0;
GLfloat obs_x = 0.0;
GLfloat my_ball_x = 0.0;
GLfloat my_ball_y = 0.0;
GLfloat boss_level = 1.0;
GLfloat boss_ball_strt_x = boss_x;
GLfloat boss_ball_strt_y = boss_y;
GLfloat my_ball_strt_x = x_location;
GLfloat my_ball_strt_y = y_location - 3.0;
int heart_count = 3;
int boss_basic_heart_count = 3;
int my_heart_count = 3;
bool jump_on = false;
bool jump_done = false;
bool shoot_ball = false;

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

void DrawChar() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); //push orgin view
    glTranslatef(x_location,-3.0 + y_location,0.0); //translate as much as keyboard callback

    //draw face
    glPushMatrix();
    glTranslatef(0.0, -0.2, 0.0);
    glScalef(1.0,1.0,1.0);
    glColor3f(pallet[1][2],pallet[1][1],pallet[1][0]);
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

void DrawBoss()
{
    glPushMatrix();
        glTranslatef(boss_x,boss_y,0.0);

    glPushMatrix();
        glColor3f(pallet[3][1],pallet[3][0],pallet[3][2]);
        glutSolidCube(2.5 * x);
    glPopMatrix();

    glPushMatrix();
        glBegin(GL_LINES);
            glColor3f(1.0 - pallet[3][1], 1.0 - pallet[3][0],1.0 - pallet[3][2]);
            glVertex3f(0.5 * x,0.5 * x,0.0);
            glVertex3f(x,x,0.0);
            glVertex3f(-0.5 * x,0.5 * x,0.0);
            glVertex3f(-x,x,0.0);
        glEnd();
        glBegin(GL_POLYGON);
            glColor3f(1.0 - pallet[3][1], 1.0 - pallet[3][0],1.0 - pallet[3][2]);
            glVertex3f(0.0, 0.0 ,0.0);
            glVertex3f(-x,-x,0.0);
            glVertex3f(x,-x,0.0);
        glEnd();
    glPopMatrix();

    glPopMatrix();
}

// Character shoot ball
void DrawShootball(GLfloat * char_x, GLfloat * char_y, GLfloat * ball_x, GLfloat * ball_y )
{
    glPushMatrix();
    glTranslatef(*char_x + *ball_x,*char_y + *ball_y,0.0);
        glColor3f(1.0,1.0,0.0);
        glutSolidCube(0.3);
    glPopMatrix();

}


void DrawHeart()
{
    for(int i = 0; i < heart_count;i++)
    {
        glPushMatrix();
        glTranslatef(9.5 - 0.5 *i,4.0,0.0);
        glScalef(1.0,2.0,1.0);
            glColor3f(0.5,0.0,0.5);
            glutSolidSphere(0.15,30,30);
        glPopMatrix();
    }
}

void DrawMyHeart()
{
    for(int i = 0; i < my_heart_count;i++)
    {
        glPushMatrix();
        glTranslatef(-9.5 + 0.5 *i,4.0,0.0);
        glScalef(1.0,2.0,1.0);
            glColor3f(1.0,0.0,0.0);
            glutSolidSphere(0.15,30,30);
        glPopMatrix();
    }
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
    DrawBoss();
    DrawShootball(&boss_ball_strt_x,&boss_ball_strt_y,&obs_x,&obs_y);
    if(shoot_ball)
    {
        DrawShootball(&my_ball_strt_x,&my_ball_strt_y,&my_ball_x,&my_ball_y);
    }
    DrawFloor();
    DrawHeart();
    DrawMyHeart();
    glFlush();
    // change obstacle position
    if(shoot_ball)
    {

        if( my_ball_strt_y + my_ball_y < boss_y + x && boss_y - x < my_ball_strt_y + my_ball_y && my_ball_strt_x + my_ball_x < boss_x + x && boss_x - x < my_ball_strt_x +my_ball_x)
        {
            if(heart_count <= 1)
            {
                boss_level += 1;
                heart_count = boss_basic_heart_count + boss_level;
                changeColor();
            }
            else
            {
                heart_count -= 1;
                my_ball_strt_y = y_location - 3.0 ;
                my_ball_strt_x = x_location;
                my_ball_y = 0.0;
                my_ball_x = 0.0;
                shoot_ball = false;
            }

        }
        else if(obs_x + boss_x > 10.0)
        {
            my_ball_strt_y = y_location - 3.0 ;
            my_ball_strt_x = x_location;
            my_ball_y = 0.0;
            my_ball_x = 0.0;
            shoot_ball = false;
        }
        else
        {
            my_ball_x = my_ball_x + 0.01;
        }

    }

    if( boss_ball_strt_y + obs_y < -3.0 + y_location + x && -3.0 + y_location - x < boss_ball_strt_y + obs_y && boss_ball_strt_x + obs_x < x_location + x && x_location - x < boss_ball_strt_x + obs_x)
    {

        if(my_heart_count <= 1)
            exit(1);
        else
        {
            my_heart_count -= 1;
            boss_ball_strt_y = boss_y;
            boss_ball_strt_x = boss_x;
            obs_y = 0.0;
            obs_x = 0.0;
        }
    }
    else if(obs_x + boss_x < -10.0)
    {
        boss_ball_strt_y = boss_y;
        boss_ball_strt_x = boss_x;
        obs_y = 0.0;
        obs_x = 0.0;
    }
    else
    {
        obs_x = obs_x - 0.01 * boss_level;
    }

    // change jump_position

    if(jump_on)
    {
        if(y_location <= 0.0 && jump_done)
        {
            y_location = 0.0;
            jump_on = false;
            jump_done = false;
        }
        else if(y_location <= 2.0 && !jump_done)
        {
            y_location += 0.01;
        }
        else
        {
            jump_done = true;
            y_location -= 0.01;
        }

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
 case 32:
     if(y_location == 0.0)
        jump_on = true;
    break;
 case 'f':
    if(!shoot_ball)
    {
        shoot_ball = true;
        my_ball_strt_y = y_location - 3.0 ;
        my_ball_strt_x = x_location;
    }

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
    glutInitWindowSize(1000,500);
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
    glOrtho(-10.0,10.0,-5.0,5.0,-5.0,5.0);
    glutDisplayFunc(DrawChar);
    glutIdleFunc(Idlefunc);
    glutKeyboardFunc(MyKeyboard);
    glutMainLoop();
    return 0;
}
