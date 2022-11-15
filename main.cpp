#pragma once
#include<iostream>
#include<bitset>
#include<windows.h>
#include "qthread.h"
#include <QtWidgets/QApplication>

//#include "bullet.cpp"
#include "object.cpp"
#include "tank.cpp"
#include "TankWarGUI.h"
#include "statics.h"
#include "ImageResource.h"
#include "MyThread.h"

#define tank_max 2//坦克的上限为2辆
#define bullet_max 10//子弹的上限为10颗
#define wall_max 100//墙的数量上限为100面
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

class main_game {//主游戏的一个类，用于实现大部分游戏功能
public:
	int game_mode;//决定了游戏的状态，当game_mode为1时，游戏继续
	main_game();
	~main_game();
	tank* obj_pool[tank_max];//坦克池，用于储存所有坦克
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

int arg0 = 1;
int& arg1 = arg0;
char **arg2;

image_resource statics::image_resourse;
QApplication statics::qapp(arg1,arg2);
TankWarGUI statics::gui;
int main()
{
    statics st;
    st.gui.show();
    
    st.image_resourse.add_image_resource(0, "D:/q.jpg");

    QThread thd;
    MyThread mthd;
    mthd.moveToThread(&thd);
    thd.start();

    QObject::connect(&st.gui, SIGNAL(repaint_signal()), &st.gui, SLOT(repaint_slot()));
    QObject::connect(&mthd, SIGNAL(MyThreadTTRan()), &mthd, SLOT(ran()));

    emit mthd.MyThreadTTRan();

    st.qapp.exec();

    //初始化
    main_game* new_game = new main_game;
    while (new_game->game_mode) {
	    //检测键盘输入并处理对象的值
	    new_game->flushed(new_game);
	    //移动所有对象
	    //new_game->crash(new_game);
	    //检测并处理所有碰撞
	    //new_game->move(new_game);
	    //打印所有的对象
    }

    return 0;
}