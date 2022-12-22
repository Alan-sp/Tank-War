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



void main_game::keyboard_detection() {
        for (int i = 1; i < 120; i++)
                        down[i] = KEY_DOWN(i);
}

void main_game::add_object(object * obj) {
        obj_pool.push_back(obj);
}

#undef KEY_DOWN(VK_NONAME)