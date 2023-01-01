
#include "object.h"

#ifndef BOOM_ANIME_H
#define BOOM_ANIME_H

class boom_animation :public object
{
	int time;
public:
	boom_animation(int dx, int dy) : object(dx, dy, 0) {
		state = 101, time = 0;
	}
	void ticking();
	void collapse(object* other, collapse_result result);
};


#endif // !BOOM_ANIME_H
