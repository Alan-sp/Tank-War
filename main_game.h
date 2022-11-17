#pragma once
#include "tank.cpp"

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

class main_game {//主游戏的一个类，用于实现大部分游戏功能
public:
	int game_mode;//决定了游戏的状态，当game_mode为1时，游戏继续
	main_game();
	~main_game();
	tank* obj_pool[1000];//坦克池，用于储存所有坦克
	//bullet* bullet_pool[bullet_max];//子弹池，用于储存所有子弹
	//wall* wall_pool[wall_max];//墙池，用于储存所有的墙
	int tank_num;//下边这三个成员变量用于表示目前该pool中对象的数量
	int bullet_num;
	int wall_num;

	int keyboard_detection();//用来检测键盘输入
	int flushed(main_game* game);
	//int move(main_game* game);//用来移动所有的对象
	int crash(main_game* game);//用来检测所有碰撞
};



