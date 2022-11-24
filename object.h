#pragma once
#include "plane_model.h"
class object {
public:
	object() {
		x = y = direct = 0, state = -1;
	}
	object(double dx, double dy, double dir) {
		x = dx, y = dy;
		direct = dir;
		state = 0;
	}
	object(const object& other) {
		x = other.x, y = other.y, direct = other.direct, state = other.state;
	}
	collapse_result collapseWith(object & other);
	virtual void collapse(object * other, collapse_result result) = 0;
	virtual void ticking() = 0;
	~object() {}
	double get_x() { return x; }
	double get_y() { return y; }
	double get_direction() { return direct; }
	int get_state() { return state; }
protected:
	double x, y;
	int state;
	double direct;
};