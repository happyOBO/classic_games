#include "user.h"

User::User(GLfloat x, GLfloat y)
    : user_x(x), user_y(y)
{
    balloon.Init(0);
}
void User::DrawChar() {
    GLfloat x = 0.3;
    glPushMatrix(); //push orgin view
    glTranslatef(user_x,user_y,0.0); //translate as much as keyboard callback

    //draw head
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glutSolidSphere(x * 1.2,100,30);
    glPopMatrix();

    //draw ears
    glPushMatrix(); //push translate view
    glTranslatef(0.3, 0.3, 0.0);
    glScalef(1.0, 1.0, 1.0);
    glColor3f(1.0,0.0 ,0.0);
    glutSolidSphere(x * 0.6, 30,30);
    glPopMatrix(); // return to translate view


    glPushMatrix(); //push translate view
    glTranslatef(-0.3, 0.3, 0.0);
    glScalef(1.0, 1.0, 1.0);
    glColor3f(1.0,0.0 ,0.0);
    glutSolidSphere(x * 0.6, 30,30);
    glPopMatrix(); // return to translate view

    //draw face
    glPushMatrix(); //push translate view
    glTranslatef(0.0, -0.1, 0.0);
    glScalef(0.8,0.7,0.9);
    glColor3f(0.95,0.87,0.83);
    glutSolidSphere(x * 1.2 ,100,30);
    glPopMatrix(); // return to translate view

    //draw hair
    glPushMatrix(); //push translate view
    glTranslatef(0.0, 0.1, 0.0);
    glScalef(0.7,0.3,0.8);
    glColor3f(0.6,0.4,0.28);
    glutSolidSphere(x * 1.0 ,30,30);
    glPopMatrix(); // return to translate view


    glPopMatrix(); // Eliminate translate view


}
pair <GLfloat, GLfloat> User::Return_loc()
{
    return make_pair(user_x,user_y);
}

void User::move_user(GLfloat add_x, GLfloat add_y)
{
    user_x += add_x;
    user_y += add_y;
}

void User::Draw_My_balloon()
{
    balloon.Draw_balloon(user_x,user_y);
}

void User::add_balloon_counts()
{
    balloon.add_ball_counts();
}

