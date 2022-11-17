#pragma once
#include "tank.cpp"

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

class main_game {
public:
	int game_mode;
	main_game();
	~main_game();
	tank* obj_pool[1000];
	int tank_num;
	int bullet_num;
	int wall_num;

	int keyboard_detection();
	int flushed(main_game* game);
	int crash(main_game* game);
};



