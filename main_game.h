#include <cmath>
#include "object.h"
#include<list>
#include <iostream>
#include "MapCoder.cpp"
#include <qstring.h>

#ifndef MAIN_GAME_H
#define MAIN_GAME_H

class main_game {
public:
	int game_mode;
	main_game();
	~main_game();
	std::list<object*> obj_pool;
	MapCoder::Map gamemap;
	int tank_num;
	int down[181];
	void* winner;
	QString name1="Player1", name2="Player2";
	int keybinds1[5] = { 87, 65, 83, 68, 81 }, keybinds2[5] = { 38, 37, 40, 39, 96 };
	int tankCD = 100, tankHP = 5, bulletDamage = 1, buffBulletDamage = 2;
	int bulletHP = 10, tankSpeed = 4, bulletSpeed = 5, buffFrequence = 200;

	void init();
	void load_map(std::string input);
	void clear_pool();
	void keyboard_detection();
	void add_object(object* obj);
};

#endif // !MAIN_GAME_H
