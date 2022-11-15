#pragma once
#include "object.cpp"
class tank :public object {
public:
	int speed;
	tank(int dx, int dy, int dir) :object(dx, dy, dir), speed(1) {};
	void rotate(tank& thing);
	void shoot();
	void ticking();
};
void tank::ticking()
{
	switch (direct)
	{
	case 1: x += speed; break;
	case 2: x -= speed; break;
	case 3: y += speed; break;
	case 4: y -= speed; break;
	}
}
/*void tank::rotate(tank& thing)
{
	thing.object::direct = read();
}
void tank::shoot()
{
	create_bullet();
}*/
