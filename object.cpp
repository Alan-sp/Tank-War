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
		int get_x() { return x; }
		int get_y() { return y; }
		int get_direction() { return direct; }
		int get_state() { return state; }
	protected :
		int x,y,direct,state;
		
};
