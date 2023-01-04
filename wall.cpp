#pragma once
#include"object.h"

#ifndef WALL_CPP
#define WALL_CPP

class wall :public object {
public:
	wall(int dx, int dy, double dir) :object(dx, dy, dir) {
		state = 1;
	}
	void collapse(object* other, collapse_result result);
	void ticking();
};

void wall::collapse(object* other, collapse_result result)
{

}

void wall::ticking()
{
}

#endif // !WALL_CPP
