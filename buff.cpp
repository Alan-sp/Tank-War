#pragma once
#include "object.h"
#include <ctime>
#include "bullet.cpp"
class buff :public object
{
public:
	int buff_state;
	int buff_cnt;
	buff();
	~buff() {};
	void bullet_across(bullet bt);
	void bullet_depart(bullet bt);
	virtual void collapse(object* other, collapse_result result) {}
	virtual void ticking() {}
};
buff::buff()
{
	srand(time(0));
	x=double(rand()%10000+1)/100.0,
	y=double(rand()%10000+1)/100.0;
	state=4;
	buff_state=rand()%4+1;
	buff_cnt=0;
	return ;
}
void Q_buff(bullet bt){
	if(bt.my_buff.buff_state==-1) return ;
	if(bt.my_buff.buff_state==1) bt.speed*=2;
	else if(bt.my_buff.buff_state==2) return;
	else if(bt.my_buff.buff_state==3) ;
	else if(bt.my_buff.buff_state==4) bt.my_buff.bullet_depart(bt);
	bt.my_buff.buff_state=-1;
	return ;
}
void buff::bullet_depart(bullet bt){
	bullet *ts1=new bullet(bt.x,bt.y,bt.dir+PI/6,bt.from);
	bullet *ts2=new bullet(bt.x,bt.y,bt.dir-PI/6,bt.from);
	return ;
}
