#include "boom_anime.h"

void boom_animation::ticking()
{
	time++;
	if(time==2)
		time=0,state++;
}

void boom_animation::collapse(object* other, collapse_result result)
{
}
