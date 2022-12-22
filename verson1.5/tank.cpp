#pragma once
#include "object.h"
#include <cmath>
const double pi=acos(-1);
class tank :public object {
public:
	double speed;
    double wspeed;
    tank(double dx, double dy, double dir,int State) :object(dx, dy, dir), speed(1), wspeed(0.01) { state = State; };
    void rotate(int x)
    {
        if(x>0) direct+=wspeed;
        if(x<0) direct-=wspeed;
    }
	void shoot();
    void ticking(int op)
    {
        double dx,dy;
        x+=op*speed*(sin(direct));
        y+=op*speed*(cos(direct));
    }
    void change_speed(int op){speed*=op;}
    void collapse(object * other, collapse_result result){
        x += result.dx, y += result.dy, hitpoint--;
        double temp = sqrt(result.dx * result.dx + result.dy * result.dy);
//        if (temp > real_speed)real_speed = temp - real_speed;
        double dir3ct = atan2(result.dy, result.dx);
        if (abs(direct - dir3ct) < 3.1415926 / 2)
            direct = 2 * (3.1415926 + dir3ct) - direct+ 3.1415926;
        else
            direct = 2 * dir3ct - direct+ 3.1415926;
    }
};
/*
void tank::shoot()
{
	create_bullet();
}*/
