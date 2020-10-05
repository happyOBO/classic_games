#include "water_balloon.h"

Water_balloon::Water_balloon()
{
    balloon_color = 0;
    max_balloons = 3;
    water_steams = 2;
    drawed_ballons = 0;
}
void Water_balloon::Init(int color)
{
    balloon_color = color;
}
void Water_balloon::Draw_balloon(GLfloat x, GLfloat y)
{
    if(drawed_ballons > 0)
    {
        glPushMatrix(); //push orgin view
        glTranslatef(x,y,0.0); //translate as much as keyboard callback
        float ColorArray[4] = {0,};
        ColorArray[balloon_color] = 0.8;
        //draw balloon
        glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glScalef(1.0,1.0,1.0);
        glColor3f(ColorArray[0],ColorArray[1],ColorArray[2]);
        glutSolidSphere(0.3 * 1.2,100,30);
        glPopMatrix();
        glPopMatrix(); // Eliminate translate view
    }
}

void Water_balloon::add_ball_counts()
{
    drawed_ballons = 1;
}

