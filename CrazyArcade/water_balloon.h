#ifndef WATER_BALLOON_H_INCLUDED
#define WATER_BALLOON_H_INCLUDED

#include "basic_setting.h"

class Water_balloon
{
private:
    int balloon_color;
    int max_balloons;
    int water_steams;
    int drawed_ballons;
public:
    Water_balloon();
    void Init(int color);
    void Draw_balloon(GLfloat x, GLfloat y);

    void add_ball_counts();
};

#endif // WATER_BALLOON_H_INCLUDED
