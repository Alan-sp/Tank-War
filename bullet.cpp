class object{
	public :
		object(int dx,int dy,int dir){
			x=dx,y=dy;		
			direct=dir;
		}
		object(const object &other){
			x=other.x,y=other.y,direct=other.direct;
		}
		bool collapase(object other);
		~object(){}
	protected :
		int x,y,direct,state;		
};
class bullet:public object{
	public:
		int speed,from;
		int mov=10;
		bullet(int dx,int dy,int dir,int num):object(dx,dy,dir),speed(1),from(num){}
		void move(bullet &thing);
		~bullet(){};
};
void bullet::move(bullet &thing){
	switch(thing.direct)
	{
		case 1 : thing.x+=thing.speed;break;
		case 2 : thing.x-=thing.speed;break;
		case 3 : thing.y+=thing.speed;break;
		case 4 : thing.y-=thing.speed;break;
	}
	thing.mov--;
}
void create_bullet(tank &thing){
	bullet x(thing.x,thing.y,thing.dir,thing.num); 
}
