#pragma once
#include "object.h"
#include <cmath>
const double pi=acos(-1);
class tank :public object {
public:
	double speed;
	double wspeed;//弧度制 
	buff my_buff;
	int name;
	tank(double dx, double dy, double dir,int m) :object(dx, dy, dir), speed(1), wspeed(0.001) { state = 2; my_buff.buff_state=-1;name=m};
	void rotate(int x);
	void shoot();
	void ticking();
	void get_buff(buff x);
	void create_bullet();
	void collapse(object * other, collapse_result result);
};
void tank::create_bullet(){
	bullet *nw=new bullet(x,y,dir,name);
	if(my_buff.buff_state!=0)	my_buff.buff_cnt++;
	nw.my_buff=my_buff;
	Q_buff(nw);
	if(my_buff.buff_cnt==20)	my_buff.buff_cnt=my_buff.buff_state=0;
	return ;
}
void tank::get_buff(buff x){
	my_buff=x;
	return ;
}
void tank::collapse(object * other, collapse_result result) {
	return;
}
void tank::ticking()//按右键，dir>0,左键，dir<0 
{
	double dx,dy;
	x+=speed*(sin(direct));
	y+=speed*(cos(direct));
}
void tank::rotate(int x){//提供左转<0 右转>0 
	if(x>0) direct+=wspeed;
	if(x<0) direct-=wspeed; 
}
void tank::shoot()
{
	create_bullet();
}
