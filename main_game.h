#pragma once
#include "tank.cpp"

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 

class main_game {//����Ϸ��һ���࣬����ʵ�ִ󲿷���Ϸ����
public:
	int game_mode;//��������Ϸ��״̬����game_modeΪ1ʱ����Ϸ����
	main_game();
	~main_game();
	tank* obj_pool[1000];//̹�˳أ����ڴ�������̹��
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



