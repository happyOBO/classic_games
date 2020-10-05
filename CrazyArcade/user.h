#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include "basic_setting.h"
#include "water_balloon.h"
using namespace std;
class User {
private :
    GLfloat user_x;
    GLfloat user_y;
    Water_balloon balloon;
public :
    User(GLfloat x, GLfloat y);
    void DrawChar();
    pair <GLfloat, GLfloat> Return_loc();

    void move_user(GLfloat add_x, GLfloat add_y);

    void Draw_My_balloon();

    void add_balloon_counts();
};
#endif // USER_H_INCLUDED
