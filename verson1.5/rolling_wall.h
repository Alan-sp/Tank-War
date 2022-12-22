#pragma once
#include"object.h"
#include<QObject>

class rolling_wall :public object {
public:
	double rolling_speed;
	rolling_wall(int dx, int dy, double dir,double rs) :object(dx, dy, dir) {
		state = 1, rolling_speed = rs;
	}
    void collapse(object* other, collapse_result result){}
    void ticking()
    {
        direct += rolling_speed;
        if (direct > 3.1415926 * 2)direct -= 3.1415926 * 2;
    }
};
