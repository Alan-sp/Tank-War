#include <cmath>
#include "object.h"
#include<list>

#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

class main_game {
public:
	int game_mode;
	main_game();
	~main_game();
	std::list<object*> obj_pool;
	int tank_num;
	int bullet_num;
	int wall_num;
	int down[181];
	void* winner;

	void keyboard_detection();
	void add_object(object* obj);
};

#endif // !MAIN_GAME_H
