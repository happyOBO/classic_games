#include "npc.h"

NPC::NPC(GLfloat x, GLfloat y, int c)
    : npc_x(x), npc_y(y), color(c)
{

}
void NPC::draw_NPC()
{
    glPushMatrix();
        glTranslatef(npc_x,npc_y,0.0);

    glPushMatrix();
        glColor3f(0.3,0.5,0.7);
        glutSolidCube(2.5 * x);
    glPopMatrix();

    glPushMatrix();
        glBegin(GL_LINES);
            glColor3f(1.0 - 0.3, 1.0 - 0.5,1.0 - 0.7);
            glVertex3f(0.5 * x,0.5 * x,0.0);
            glVertex3f(x,x,0.0);
            glVertex3f(-0.5 * x,0.5 * x,0.0);
            glVertex3f(-x,x,0.0);
        glEnd();
        glBegin(GL_POLYGON);
            glColor3f(1.0 - 0.3, 1.0 - 0.5,1.0 - 0.7);
            glVertex3f(0.0, 0.0 ,0.0);
            glVertex3f(-x,-x,0.0);
            glVertex3f(x,-x,0.0);
        glEnd();
    glPopMatrix();

    glPopMatrix();

}

void NPC::touch_NPC(User usr)
{
    pair<GLfloat,GLfloat> loc = usr.Return_loc();
    GLfloat x_location = loc.first;
    GLfloat y_location = loc.second;
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

