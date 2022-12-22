#pragma once
#include"object.h"

class wall:public object{
	public:
		wall(int dx,int dy,double dir):object(dx,dy,dir){
			state=1;
		}
        void collapse(object* other, collapse_result result){}
        void ticking(){}
};
