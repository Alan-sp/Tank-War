#pragma once
#include"object.h"

#ifndef SHORTWALL_CPP
#define SHORTWALL_CPP

class shortwall :public object {
public:
	shortwall(int dx, int dy, double dir) :object(dx, dy, dir) {
		state = 10;
	}
	void collapse(object* other, collapse_result result);
	void ticking();
};

void shortwall::collapse(object* other, collapse_result result)
{

}

void shortwall::ticking()
{
}

#endif // !SHORTWALL_CPP
