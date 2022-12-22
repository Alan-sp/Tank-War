#include "boom_anime.h"

void boom_anime::ticking()
{
	time++;
	if(time==2)
		time=0,state++;
}

void boom_anime::collapse(object* other, collapse_result result)
{
}
