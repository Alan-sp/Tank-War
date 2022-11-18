#pragma once
#include <cstddef>

struct collapse_result {
	bool isCollapse;
	float dx, dy;
};

class plane_model
{
private:
	int type, r, n;
	float* points_x, * points_y;
public:
	plane_model() {
		this->type = r = n = 0;
		points_x = points_y = NULL;
	}
	plane_model(int r) {
		type = 1, this->r = r, n = 0;
		points_x = points_y = NULL;
	}
	plane_model(int n, float* x,float* y) {
		type = 2, r = 0, this->n = n;
		points_x = x, points_y = y;
	}
	int get_type() { return type; }
	int get_r() { return r; }
	int get_n() { return n; }
	float* get_xs() { return points_x; }
	float* get_ys() { return points_y; }
};

