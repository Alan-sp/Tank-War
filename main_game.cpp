#include "main_game.h"
#include<windows.h>
#include <iostream>

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

main_game::main_game() {
	game_mode = 1;
	tank_num = 0;
	bullet_num = 0;
	wall_num = 0;

	//————————————————————————————————————————————
	//我想把这里写进对象里面
	obj_pool[tank_num] = new tank(1, 1, 1);//这里应该是默认出生点，但目前啥也不知道；
	tank_num++;
	//就是以后，每个类的对象写构造函数的时候，就把自己加到对应的池子里
	// 我这里写一个creat_tank就行了
	//————————————————————————————————————————————


	//绘制地图---------地图就是数组，数组里就是所有的wall的x，y和类型

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
	//刷新状态的一个函数，
	//消灭多余子弹、死亡坦克、坦克复活等等
	for (int i = 0; i < game->tank_num; i++) {
		game->obj_pool[i]->ticking();
	}
	return 0;
}
#undef KEY_DOWN(VK_NONAME)