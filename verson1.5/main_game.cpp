#pragma once
#include "main_game.h"
#include<windows.h>
#include <iostream>
#include "tank.cpp"
#include "bullet.cpp"

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 


main_game::main_game() {
	game_mode = 1;
	tank_num = 0;
	bullet_num = 0;
	wall_num = 0;
}



main_game::~main_game() {
	std::cout << "GAME OVER";
}



int main_game::keyboard_detection() {
    for (int i = 1; i < 120; i++) {
            if (KEY_DOWN(i)) {
                down[i] = 0;
            }
            else {
                down[i] = 1;
            }
        }
    std::list<object*>::const_iterator it=obj_pool.begin();
    object* Tank1=(*it);++it;
    object* Tank2=(*(it));
    if(!down[87]) (*obj_pool.begin())->ticking(1);
    if(!down[83]) (*obj_pool.begin())->ticking(-1);
    if(!down[65]) (*obj_pool.begin())->rotate(1);
    if(!down[68]) (*obj_pool.begin())->rotate(-1);
    if(!down[32])
    {
        obj_pool.push_back(new bullet(Tank1->get_x(),Tank1->get_y(),Tank1->get_direction(),3));
    }
    if(!down[38]) Tank2->ticking(1);
    if(!down[40]) Tank2->ticking(-1);
    if(!down[37]) Tank2->rotate(1);
    if(!down[39]) Tank2->rotate(-1);
    if(!down[163])
    {
        obj_pool.push_back(new bullet(Tank2->get_x(),Tank2->get_y(),Tank2->get_direction(),3));
    }
    it++;
    while(it!=obj_pool.end())
    {
        (**it).ticking(1);
        if((**it).get_state()==-1) it=obj_pool.erase((it));
        else it++;
    }
}



//int main_game::flushed(main_game* game) {
//	for (int i = 0; i < game->tank_num; i++) {
//		game->obj_pool[i]->ticking();
//	}
//	return 0;
//}
#undef KEY_DOWN(VK_NONAME)
