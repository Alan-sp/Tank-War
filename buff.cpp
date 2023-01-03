
#include "object.h"
#include <ctime>
#include "tank.h"
#ifndef BUFF_CPP
#define BUFF_CPP

class buff :public object
{
public:
	buff();
	buff(double, double, double, int);
	void get_buff(object* other);
	~buff() {};
	int buff_state;
	virtual void collapse(object* other, collapse_result result);
	virtual void ticking() {}
};

buff::buff() {
	x = double(rand() % 800+ 200),
		y = double(rand() % 400 + 200) ;
	buff_state = rand() % 4;
	direct = double(rand() % 700) / 700;
	state = 50+buff_state+1;
	return;
}

buff::buff(double xx, double yy , double dir, int type)
{
	x = xx, y = yy, direct = dir, state = 50 + type + 1;
	buff_state = type;
}

void buff::collapse(object* other, collapse_result result) {
	if (other->get_state() / 10 == 2)
	{
		get_buff(other);
		state = -1;
	}
}

void buff::get_buff(object* other) {
	tank* test_tank = static_cast<tank*>(other);
	test_tank->buff_state = (test_tank->buff_state | (1 << buff_state));
	return;
}

#endif // !BUFF_CPP

