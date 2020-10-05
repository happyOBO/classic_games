#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include "basic_setting.h"
#include "user.h"

class NPC {
private :
    int color;
    GLfloat npc_x;
    GLfloat npc_y;
public :
    NPC(GLfloat x, GLfloat y, int c);
    void draw_NPC();

    void touch_NPC(User usr);
};
#endif // NPC_H_INCLUDED
