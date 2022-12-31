#pragma once
#include "object.h"
#include <cmath>
#include "bullet.cpp"
#include <iostream>
#include "boom_anime.h"
#include "statics.h"
const double pi=acos(-1);
class tank :public object {
public:
	double speed;
	double wspeed;//弧度制 
	int name,tw,ta,ts,td,tshoot,cd_time;
	tank(double dx, double dy, double dir, int m,int tw,int ta,int ts,int td,int tshoot) :object(dx, dy, dir), speed(4), wspeed(0.05) {
		state = 20+m; name = m;
		this->tw = tw, this->ta = ta, this->ts = ts, this->td = td;
		this->tshoot = tshoot;
		hitpoint = 5 ,cd_time=100;
	};
	void ticking();
	void collapse(object * other, collapse_result result);
};

void tank::collapse(object* other, collapse_result result) {
	x += result.dx, y += result.dy;
	if (other->get_state() == 3)hitpoint--;
}
void tank::ticking()
{
	statics st;
	double dx,dy;
	if (cd_time > 0)cd_time--;
	if(st.maingame.down[tw])
		x+=speed*(cos(direct)),
		y+=speed*(sin(direct));
	if (st.maingame.down[ts])
		x -= speed * (cos(direct)),
		y -= speed * (sin(direct));
	if (st.maingame.down[ta])
		direct -= wspeed;
	if (st.maingame.down[td])
		direct += wspeed;
	if (st.maingame.down[tshoot] && cd_time == 0)
	{
		st.maingame.add_object(new bullet(x + 50*cos(direct), y + 50*sin(direct), direct, name));
		cd_time = 100;
	}
	if (hitpoint < 0)
	{
		state = -1;
		st.maingame.add_object(new boom_animation(x, y));
	}
}