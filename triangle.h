
#include"object.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H

class triangle :public object {
public:
	double rolling_speed;
	triangle(int dx, int dy, double dir, double rs) :object(dx, dy, dir) {
		state = 13, rolling_speed = rs;
	}
	void collapse(object* other, collapse_result result);
	void ticking();
};

void triangle::collapse(object* other, collapse_result result)
{

}

void triangle::ticking()
{
	direct += rolling_speed;
	if (direct > 3.1415926 * 2)direct -= 3.1415926 * 2;
	if (direct < -3.1415926 * 2)direct += 3.1415926 * 2;
}

#endif // !TRIANGLE_H
