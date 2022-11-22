#pragma once
#include "plane_model.h"
#include <iostream>
#include "statics.h"
#include "object.h"

#define _2(X) ((X)*(X))
collapse_result object::collapseBetweenTwoType(object const& circle, plane_model plg, plane_model cir) {
	double* xs = new double[plg.get_n()], * ys = new double[plg.get_n()];
	collapse_result ret; ret.isCollapse = false, ret.dx = ret.dy = 0;
	for (int i = 0; i < plg.get_n(); i++)
		xs[i] = x + plg.get_xs()[i] * cos(direct) + plg.get_ys()[i] * sin(direct),
		ys[i] = y + plg.get_ys()[i] * cos(direct) - plg.get_xs()[i] * sin(direct);
	int k = -1; double minr = cir.get_r(), temp;
	for (int i = 0; i < plg.get_n(); i++) {
		temp = sqrt(_2(xs[i] - x) + _2(ys[i] - y));
		if (temp < minr)
			k = i, minr = temp;
	}
	if (k != -1) {
		ret.isCollapse = true,
		ret.dx = (x - xs[k]) * cir.get_r() / minr,
		ret.dy = (y - ys[k]) * cir.get_r() / minr;
	}
	else {
		k = -1;
		for (int i = 1; i < plg.get_n(); i++) {
			double k = (ys[i] - ys[i - 1]) / (xs[i] - xs[i - 1]), b = ys[i] - k * xs[i];
			double A = _2(k) + 1, B = 2 * (k * b - k * circle.x - circle.y), C = _2(circle.x) + _2(circle.y) + _2(b) - _2(cir.get_r()) - 2 * circle.x * b;
			double delta = _2(B) - 4 * A * C;
			if (delta < 0)continue;
			double x1 = (-B - sqrt(delta)) / 2 * A, x2 = (-B + sqrt(delta)) / 2 * A,x0=(x1+x2)/2;
			if (x0<std::min(xs[i - 1], xs[i]) || x0>std::max(xs[i - 1], xs[i]))continue;
			//Work In Progress
		}
	}
	delete[] xs; delete[] ys;
	return ret;
}
collapse_result object::collapseWith(object & other)
{
	statics st;
	plane_model a = st.resource_library.get_model(state),b=st.resource_library.get_model(other.state);
	collapse_result ret; ret.isCollapse = false, ret.dx = ret.dy = 0;
	if (a.get_type() == 0 || b.get_type() == 0) {
		return ret;
	}
	float dist = sqrt(_2(x - other.x) + _2(y - other.y));
	if (a.get_type() == 1 && b.get_type() == 1) {
		if ( dist < a.get_r() + b.get_r()) {
			ret.isCollapse = true,
			ret.dx = (x - other.x) * (a.get_r() + b.get_r() - dist) / dist,
			ret.dy = (y - other.y) * (a.get_r() + b.get_r() - dist) / dist;
		}
		return ret;
	}
	if (dist > a.get_r() + b.get_r())return ret;
	else if (a.get_type() == 1 && b.get_type() == 2) {
		return other.collapseBetweenTwoType(*this, b, a);
	}
	else if (a.get_type() == 2 && b.get_type() == 1) {
		return this->collapseBetweenTwoType(other, a, b);
	}
	else if (a.get_type() == 2 && b.get_type() == 2) {
		//EPA
		return ret;
	}
	else {
		std::cout << "plane_model:Unexpected type\n";
		return ret;
	}
}
#undef _2(X)
