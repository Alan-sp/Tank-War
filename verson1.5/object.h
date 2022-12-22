#pragma once
#include "plane_model.h"
class object {
public:
	object() {
        x = y = direct = 0, state = 1,hitpoint=3;
	}
	object(double dx, double dy, double dir) {
		x = dx, y = dy;
		direct = dir;
        state = 1;
        hitpoint=3;
	}
	object(const object& other) {
        x = other.x, y = other.y, direct = other.direct, state = other.state,hitpoint=other.hitpoint;
	}
	collapse_result collapseWith(object & other);
    virtual void collapse(object * other, collapse_result result){};
    virtual void ticking(int op){};
    virtual void rotate(int dir){};
	~object() {}
	double get_x() { return x; }
	double get_y() { return y; }
	double get_direction() { return direct; }
    int get_state() { return state; }
protected:
	double x, y;
    int state,hitpoint;
	double direct;
};
