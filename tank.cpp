#pragma once
#include "object.cpp"
const double pi=acos(-1);
class object{
	public :
		object() {
			x=y=direct=0,state = -1;
		}
		object (double dx,double dy,double dir){
			x=dx,y=dy;		
			direct=dir;
			state = 0;
		}
		object (const object &other){
			x=other.x,y=other.y,direct=other.direct,state=other.state;
		}
		bool collapase(object other) {}
		//virtual void ticking();
		~object(){}
		int get_x() { return x; }
		int get_y() { return y; }
		int get_direction() { return direct; }
		int get_state() { return state; }
	protected :
		double x,y;
		int state;
		double direct;
};
class tank :public object {
public:
	double speed;
	double wspeed;//弧度制 
	tank(double dx, double dy, double dir) :object(dx, dy, dir), speed(1),wspeed(0.001) {};
	void rotate(int x);
	void shoot();
	void ticking();
};
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
/*
void tank::shoot()
{
	create_bullet();
}*/
