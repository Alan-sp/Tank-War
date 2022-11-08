class object{
	public :
		object (int dx,int dy,int dir){
			x=dx,y=dy;		
			direct=dir;
		}
		object (const object &other){
			x=other.x,y=other.y,direct=other.direct;
		}
		bool collapase(object other);
		~object(){}
	protected :
		int x,y,direct,state;		
};
class tank:public object{
	public :
		int speed;
		tank(int dx,int dy,int dir):object(dx,dy,dir),speed(1){};
		void move(tank &thing);
		void rotate(tank &thing);
		void shoot();	
};
void tank::move(tank &thing)
{
	switch(thing.object::direct)
	{
		case 1 : thing.object::x+=thing.speed;break;
		case 2 : thing.object::x-=thing.speed;break;
		case 3 : thing.object::y+=thing.speed;break;
		case 4 : thing.object::y-=thing.speed;break;
	}
}
void tank::rotate(tank &thing)
{
	thing.object::direct=read();
}
void tank::shoot()
{
	create_bullet();
}