#pragma once
#include"object.h"

#ifndef MIDWALL_CPP
#define MIDWALL_CPP

class midwall :public object {
public:
	midwall(int dx, int dy, double dir) :object(dx, dy, dir) {
		state = 11;
	}
	void collapse(object* other, collapse_result result);
	void ticking();
};

void midwall::collapse(object* other, collapse_result result)
{

}

void midwall::ticking()
{
}

#endif // !MIDWALL_CPP
