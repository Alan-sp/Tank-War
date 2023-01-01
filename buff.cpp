
#include "object.h"
#include <ctime>
#include "tank.cpp"
#ifndef BUFF_CPP
#define BUFF_CPP

class buff :public object
{
public:
	buff();
	void get_buff(object* other);
	~buff() {};
	int buff_state;
	virtual void collapse(object* other, collapse_result result);
	virtual void ticking() {}
};

buff::buff() {
	x = double(rand() % 600+ 200),
		y = double(rand() % 1000 + 200) ;
	state = 4;
	buff_state = rand() % 4;
	return;
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

