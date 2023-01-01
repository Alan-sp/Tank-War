#include "object.h"
#include <cstdio>
#include <cmath>

#ifndef BULLET_CPP
#define BULLET_CPP

class bullet :public object {
public:
	double speed, real_speed;
	void* from;
	int hitpoint;
	int attack_id;
	bool invisible;
	bullet(double dx, double dy, double dir, void* num, int d_attack) :object(dx, dy, dir), speed(5), from(num) {
		invisible = false, attack_id = d_attack, state = 3, hitpoint = 10, real_speed = speed;
	}
	void ticking();
	void collapse(object* other, collapse_result result);
	void change_direct(double newdirect) { this->direct = newdirect; }
	~bullet() {};
};
void bullet::ticking() {
	x += real_speed * cos(direct),
		y += real_speed * sin(direct);
	real_speed += (speed - real_speed) * 0.01;
}
void bullet::collapse(object* other, collapse_result result) {
	if ((*other).get_state() == 1&&!invisible) {
		x += result.dx, y += result.dy, hitpoint--;
		double temp = sqrt(result.dx * result.dx + result.dy * result.dy);
		if (temp > real_speed)real_speed = temp - real_speed;
		double dir3ct = atan2(result.dy, result.dx);
		if (abs(direct - dir3ct) < 3.1415926 / 2)
			direct = 2 * (3.1415926 + dir3ct) - direct + 3.1415926;
		else
			direct = 2 * dir3ct - direct + 3.1415926;
	}
	if ((*other).get_state() / 10 == 2) state = -1;
	if (hitpoint == 0 || x < 0 || x>1200 || y < 0 || y>800)state = -1;
}
#endif // !BULLET_CPP


