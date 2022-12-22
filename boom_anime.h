#pragma once
#include "object.h"
class boom_anime:public object
{
	int time;
public:
	boom_anime(int dx, int dy) : object(dx,dy,0){
		state = 101, time = 0;
	}
	void ticking();
	void collapse(object* other, collapse_result result);
};

