class bullet:public object{
	public:
		double speed;
		int from;
		double wspeed;
		bullet(double dx,double dy,double dir,int num):object(dx,dy,dir),speed(1),wspeed(0.001),from(num){}
		void move();
		~bullet(){};
};
void bullet::move(){
	double dx,dy;
	x+=speed*(sin(direct));
	y+=speed*(cos(direct));
}
