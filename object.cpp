#pragma once
class object{
	public :
		object() {
			x=y=direct=0,state = -1;
		}
		object (int dx,int dy,int dir){
			x=dx,y=dy;		
			direct=dir;
			state = 0;
		}
		object (const object &other){
			x=other.x,y=other.y,direct=other.direct,state=other.state;
		}
		bool collapase(object other) {}
		~object(){}
		int getX() { return x; }
		int getY() { return y; }
		int getDirection() { return direct; }
		int getState() { return state; }
	protected :
		int x,y,direct,state;
		
};
