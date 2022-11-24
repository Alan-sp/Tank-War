#pragma once
#include <cstddef>
#include <cmath>

struct collapse_result {
	bool isCollapse;
	double dx, dy;

	collapse_result operator-() {
		collapse_result ret;
		ret.isCollapse = isCollapse, ret.dx = -dx, ret.dy = -dy;
		return ret;
	}
};

class plane_model
{
private:
	int type, n;
	double r;
	double* points_x, * points_y;
public:
	plane_model() {
		this->type = r = n = 0;
		points_x = points_y = NULL;
	}
	plane_model(double r) {
		type = 1, this->r = r, n = 0;
		points_x = points_y = NULL;
	}
	plane_model(int n, double* x,double* y) {
		type = 2, r = 0, this->n = n;
		points_x = x, points_y = y;
		double t;
		for (int i = 0; i < n; i++) {
			t = sqrt(x[i] * x[i] + y[i] * y[i]);
			if (t > r)r = t;
		}
	}
	int get_type() { return type; }
	int get_r() { return r; }
	int get_n() { return n; }
	double* get_xs() { return points_x; }
	double* get_ys() { return points_y; }
};

