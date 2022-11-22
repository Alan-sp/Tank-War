#include "object.h"
#include <cmath>
class bullet:public object{
	public:
		double speed;
		int from;
		bullet(double dx, double dy, double dir, int num) :object(dx, dy, dir), speed(1), from(num) { state = 3; }
		void ticking();
		void collapse(object * other, collapse_result result);
		~bullet(){};
};
void bullet::ticking(){
	x += speed * cos(direct),
	y += speed * sin(direct);
}
void bullet::collapse(object * other, collapse_result result){
	//x += result.dx, y += result.dy;
	if ((*other).get_state() == 1) {
		if (abs(direct - other->get_direction()) < 3.1415926 / 2)
			direct = 2 * (3.1415926 + other->get_direction()) - direct+ 3.1415926;
		else
			direct = 2 * other->get_direction() - direct+ 3.1415926;
	}
}
