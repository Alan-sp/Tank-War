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

#define tank_max 2//̹�˵�����Ϊ2��
#define bullet_max 10//�ӵ�������Ϊ10��
#define wall_max 100//ǽ����������Ϊ100��
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

class main_game {//����Ϸ��һ���࣬����ʵ�ִ󲿷���Ϸ����
public:
	int game_mode;//��������Ϸ��״̬����game_modeΪ1ʱ����Ϸ����
	main_game();
	~main_game();
	tank* obj_pool[tank_max];//̹�˳أ����ڴ�������̹��
	//bullet* bullet_pool[bullet_max];//�ӵ��أ����ڴ��������ӵ�
	//wall* wall_pool[wall_max];//ǽ�أ����ڴ������е�ǽ
	int tank_num;//�±���������Ա�������ڱ�ʾĿǰ��pool�ж��������
	int bullet_num;
	int wall_num;

	int keyboard_detection();//��������������
	int flushed(main_game* game);
	//int move(main_game* game);//�����ƶ����еĶ���
	int crash(main_game* game);//�������������ײ
};



main_game::main_game() {
	game_mode = 1;
	tank_num = 0;
	bullet_num = 0;
	wall_num = 0;

	//����������������������������������������������������������������������������������������
	//���������д����������
	obj_pool[tank_num] = new tank(1, 1, 1);//����Ӧ����Ĭ�ϳ����㣬��ĿǰɶҲ��֪����
	tank_num++;
	//�����Ժ�ÿ����Ķ���д���캯����ʱ�򣬾Ͱ��Լ��ӵ���Ӧ�ĳ�����
	// ������дһ��creat_tank������
	//����������������������������������������������������������������������������������������


	//���Ƶ�ͼ---------��ͼ�������飬������������е�wall��x��y������

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
	//ˢ��״̬��һ��������
	//��������ӵ�������̹�ˡ�̹�˸���ȵ�
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

    //��ʼ��
    main_game* new_game = new main_game;
    while (new_game->game_mode) {
	    //���������벢��������ֵ
	    new_game->flushed(new_game);
	    //�ƶ����ж���
	    //new_game->crash(new_game);
	    //��Ⲣ����������ײ
	    //new_game->move(new_game);
	    //��ӡ���еĶ���
    }

    return 0;
}