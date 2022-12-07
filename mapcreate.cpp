#include <bits/stdc++.h>
using namespace std;
struct Point{
	double x,y,rad;
}point[50];
bool cmp(Point a,Point b){
	return a.rad<b.rad;
}
bool check(Point a,Point b){
	if(a.x*b.y>a.y*b.x){
		return 1;
	}
	else return 0; 
}
void create2(double sx,double sy,int lx,int ly,int num){
	int vis=0;
//	cout<<num<<endl;
	for(int i=1;i<=num;i++){
		point[i].x=rand()%lx+((double)(rand()%10))/100;
		point[i].y=rand()%ly+((double)(rand()%10))/100;
		point[i].rad=atan(point[i].y/point[i].x);
	}
	point[0].x=sx,point[0].y=sy,point[0].rad=0;
	sort(point+1,point+1+num,cmp);
	stack<Point>convex;
	while(vis<=num){
	//	cout<<vis<<" "<<convex.size()<<endl;
		if(convex.size()<2){
			convex.push(point[vis]);
			vis++;
			continue;
		} 
		Point nowx=convex.top();
	//	cout<<nowx.x<<" "<<nowx.y<<" "<<nowx.rad<<endl;
		while(!check(nowx,point[vis])){
			convex.pop();
			nowx=convex.top();
		}
		convex.push(point[vis]);
		vis++;
	}
	cout<<"2"<<" "<<num<<endl;
	while(!convex.empty()){
		Point nowx=convex.top();
		cout<<nowx.x+sx<<" "<<nowx.y+sy<<" "<<endl;
		convex.pop();
	}
}
int main(){
	srand(time(0));
	double mapx=1200,mapy=800;
	int n=5,m=5;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			double sx=mapx*(j-1)/m;
			double sy=mapy*(i-1)/n;
			int lx=mapx/m;
			int ly=mapy/n;
			int type=rand()%2+1;
			cout<<type<<" "<<sx<<" "<<sy<<" "<<lx<<" "<<ly<<endl;
			if(type==1){
				int num=4;
				double ssx=rand()%(int)lx+((double)(rand()%10))/100+sx;
				double ssy=rand()%(int)ly+((double)(rand()%10))/100+sy;
				double l=rand()%(int)(mapx*j/m-ssx)+((double)(rand()%10))/100;
				double d=rand()%(int)(mapy*j/n-ssx)+((double)(rand()%10))/100; 
				cout<<"1"<<" "<<"4"<<endl;
				cout<<ssx+l<<" "<<ssy+d<<endl;
				cout<<ssx-l<<" "<<ssy+d<<endl;
				cout<<ssx+l<<" "<<ssy-d<<endl;
				cout<<ssx-l<<" "<<ssy-d<<endl;
			}
			else{
				int num=rand()%20+10;
				create2(sx,sy,lx,ly,num);
			}
		}
	}
	return 0;
}
