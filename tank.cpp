#include "statics.h"
#include "tank.h"
#include <cmath>
#include "bullet.cpp"
#include "main_game.h"
#include <iostream>
#include "boom_anime.h"

#ifndef TANK_CPP
#define TANK_CPP

tank::tank(double dx, double dy, double dir, int m, int tw, int ta, int ts, int td, int tshoot, std::string strname) :object(dx, dy, dir) {
	state = 20 + m; name = m;
	statics st;
	speed = st.maingame->tankSpeed, wspeed = 0.05;
	this->tw = tw, this->ta = ta, this->ts = ts, this->td = td;
	this->tshoot = tshoot;
	hitpoint = st.maingame->tankHP, currentcd = cd_time = st.maingame->tankCD;
	shootcount = hitcount = 0;
	this->strname = strname;
	attack_id = st.maingame->bulletDamage, buff_state = 0;
};

void tank::Q_buff() {
	statics st;
	bullet* test_bullet = new bullet(x + 50 * cos(direct), y + 50 * sin(direct), direct, this, attack_id);
	if (buff_state & 1)
	{
		test_bullet->speed *= 2;
	}
	if (buff_state & 2)
	{
		test_bullet->attack_id = st.maingame->buffBulletDamage;
	}
	if (buff_state & 4)
	{
		test_bullet->invisible = true;
	}
	st.maingame->add_object(test_bullet);
	if (buff_state & 8)
	{
		bullet* up = new bullet(*test_bullet);
		up->change_direct(direct + 3.1415926 / 6);
		st.maingame->add_object(up);
		bullet* down = new bullet(*test_bullet);
		down->change_direct(direct - 3.1415926 / 6);
		st.maingame->add_object(down);
		shootcount += 2;
	}
	buff_state = 0;
	return;
}
void tank::collapse(object* other, collapse_result result) {
	if(other->get_state()<50)x += result.dx, y += result.dy;
	if (other->get_state() == 3)
	{
		bullet* bulletptr = static_cast<bullet*>(other);
		tank* murder = static_cast<tank*>(bulletptr->from);
		murder->hitcount++;
		hitpoint-=bulletptr->attack_id;
	}
}
void tank::ticking()
{
	statics st;
	double dx, dy;
	if (currentcd > 0)currentcd--;
	if (st.maingame->down[tw])
		x += speed * (cos(direct)),
		y += speed * (sin(direct));
	if (st.maingame->down[ts])
		x -= speed * (cos(direct)),
		y -= speed * (sin(direct));
	if (st.maingame->down[ta])
		direct -= wspeed;
	if (st.maingame->down[td])
		direct += wspeed;
	if (st.maingame->down[tshoot] && currentcd == 0)
	{
		if(buff_state)
			Q_buff();
		else
			st.maingame->add_object(new bullet(x + 50 * cos(direct), y + 50 * sin(direct), direct, this,1));
		
		currentcd = cd_time, shootcount++;
	}
	if (hitpoint <= 0)
	{
		state = -1;
		st.maingame->add_object(new boom_animation(x, y));
		st.maingame->tank_num--;
	}
}

#endif // !TANK_CPP

