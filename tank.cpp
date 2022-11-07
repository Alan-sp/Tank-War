class object{
	public :
		int find_position_x(const object thing);
		int find_position_y(const object thing);
		int find_direct(const object thing);
		void change_position_x(object &thing,int dir);
		void change_position_y(object &thing,int dir);
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
		int x,y,direct,state,speed;
		
};
void object::change_position_x(object &thing,int dir)
{
	thing.x+=speed*(dir==1)?(1):(-1);
}
void object::change_position_y(object &thing,int dir)
{
	thing.y+=speed*(dir==1)?(1):(-1);
}
int object::find_position_x(const object thing)
{
	return thing.x;
}
int object::find_position_y(const object thing)
{
	return thing.y;
}
int object::find_direct(const object thing)
{
	return thing.direct;
}
class tank:public object{
	public :
		void move(tank &thing);
		void move_up(object &thing);	
		void move_down(object &thing);
		void move_left(object &thing);
		void move_right(object &thing);
		void rotate(tank &thing);
		void shoot();
};
void tank::move_up(object &thing)
{
	change_position_x(thing,1);
}
void tank::move_down(object &thing)
{
	change_position_x(thing,-1);
}
void tank::move_left(object &thing)
{
	change_position_y(thing,1);
}
void tank::move_right(object &thing)
{
	change_position_y(thing,-1);
}
void tank::move(tank &thing)
{
	switch(find_direct(thing))
	{
		case 1 : thing.move_up(thing);break;
		case 2 : thing.move_down(thing);break;
		case 3 : thing.move_left(thing);break;
		case 4 : thing.move_right(thing);break;
	}
}
void tank::shoot()
{
	create_bullet();
}