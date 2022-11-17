#include "main_game.h"
#include<windows.h>
#include <iostream>

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

main_game::main_game() {
	game_mode = 1;
	tank_num = 0;
	bullet_num = 0;
	wall_num = 0;

	
	obj_pool[tank_num] = new tank(1, 1, 1);

}



main_game::~main_game() {
	std::cout << "GAME OVER";
}



int main_game::keyboard_detection() {
	int ret = 0;
	if (KEY_DOWN('A')) {
		ret = 1;
	}
	else if (KEY_DOWN('D')) {
		ret = 2;
	}
	else if (KEY_DOWN('W')) {
		ret = 3;
	}
	else if (KEY_DOWN('S')) {
		ret = 4;
	}
	else if (KEY_DOWN(' ')) {
		ret = 5;
	}
	return ret;
}



int main_game::flushed(main_game* game) {
	for (int i = 0; i < game->tank_num; i++) {
		game->obj_pool[i]->ticking();
	}
	return 0;
}
#undef KEY_DOWN(VK_NONAME)