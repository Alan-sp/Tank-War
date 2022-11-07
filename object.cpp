#include <bits/stdc++.h>
using namespace std;
class object{
	public :
		object (int dx,int dy,int dir){
			x=dx,y=dy;		
			direct=dir;
		}
		object (const object &other){
			x=other.x,y=other.y,direct=other.direct;
		}
		bool collapase(object other) {}
		~object(){}
	protected :
		int x,y,direct,state;
		
};
