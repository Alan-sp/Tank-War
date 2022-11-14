#include<bits/stdc++.h>
//#include"tank.cpp"
using namespace std;
class object{
	public :
		object (int dx,int dy,int dir=0){
			x=dx,y=dy;
			direct=dir;
		}
		object (const object &other){
			x=other.x,y=other.y,direct=other.direct;
		}
		void collapase(object other);
		~object(){}
	protected:
		int x,y,direct,state;
		
};//x，y指坐标位置，direct指方向，state指状态
/*state:-2 ->白墙:不可打碎
	   :-1 ->黑墙:可以打碎
	   :1 ->子弹
	   :0 ->消除
	   :2(>=2) ->坦克
*/
class wall:public object{
	public:
		wall(int dx,int dy):object(dx,dy){
			state=-1;
		}
		void collapase(tank other);
		void collapase(bullet other);
};
void wall::collapase(tank other){
	tank_return(other);
	return ;
}
void wall::collapase(bullet other){
	if(state==-1) state=0;
	other.state=0;
	return ;
}
int main()
{
	
}
