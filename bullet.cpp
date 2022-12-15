#pragma once
#include "object.h"
#include <cstdio>
#include <cmath>
#include "buff.cpp"
class bullet:public object{
	public:
		friend class buff;
		friend void Q_buff(bullet bt);
		double speed,real_speed;
		int from;
		int hitpoint;
		buff my_buff;
		bullet(double dx, double dy, double dir, int num) :object(dx, dy, dir), speed(5), from(num) { state = 3, hitpoint = -1, real_speed = speed,buff_state=-1; }
		void ticking();
		void collapse(object * other, collapse_result result);
		~bullet() {};
};
void bullet::ticking(){
	x += real_speed * cos(direct),
	y += real_speed * sin(direct);
	real_speed += (speed - real_speed) * 0.01;
}
void bullet::collapse(object * other, collapse_result result){
	//if ((*other).get_state() == 1) {
		x += result.dx, y += result.dy, hitpoint--;
		double temp = sqrt(result.dx * result.dx + result.dy * result.dy);
		if (temp > real_speed)real_speed = temp - real_speed;
		double dir3ct = atan2(result.dy, result.dx);
		if (abs(direct - dir3ct) < 3.1415926 / 2)
			direct = 2 * (3.1415926 + dir3ct) - direct+ 3.1415926;
		else
			direct = 2 * dir3ct - direct+ 3.1415926;
	//}
	if (hitpoint==0 || x < 0 || x>1200 || y < 0 || y>800)state = -1;
}
