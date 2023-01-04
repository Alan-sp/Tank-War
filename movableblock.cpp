#pragma once
#include"object.h"

#ifndef MOVABLEBLOCK_CPP
#define MOVABLEBLOCK_CPP

class movableblock :public object {
public:
	movableblock(int dx, int dy, double dir) :object(dx, dy, dir) {
		state = 12;
	}
	void collapse(object* other, collapse_result result);
	void ticking();
};

void movableblock::collapse(object* other, collapse_result result)
{
	if (other->get_state() / 10 != 50)
		x += result.dx,y+=result.dy;
}

void movableblock::ticking()
{
}

#endif // !MOVABLEBLOCK_CPP
