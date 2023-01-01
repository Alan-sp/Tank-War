#pragma once
#include "PolygonUtil.cpp"
#include "plane_model.h"
#include <iostream>
#include "statics.h"
#include "resource_lib.h"
#include "object.h"

#define _2(X) ((X)*(X))
collapse_result object::collapseWith(object & other)
{
	statics st;
	plane_model a = st.resource_library->get_model(state),b=st.resource_library->get_model(other.state);
	collapse_result ret; ret.isCollapse = false, ret.dx = ret.dy = 0;
	if (a.get_type() == 0 || b.get_type() == 0 || other.get_state() == -1 || state == -1) {
		return ret;
	}
	double dist = sqrt(_2(x - other.x) + _2(y - other.y));
	if (a.get_type() == 1 && b.get_type() == 1) {
		if ( dist < a.get_r() + b.get_r()) {
			ret.isCollapse = true,
			ret.dx = (x - other.x) * (a.get_r() + b.get_r() - dist) / dist,
			ret.dy = (y - other.y) * (a.get_r() + b.get_r() - dist) / dist;
		}
		return ret.opposide();
	}
	if (dist > a.get_r() + b.get_r())return ret;
	else if (a.get_type() == 1 && b.get_type() == 2) {
		PolygonUtil::node* an = new PolygonUtil::node[2];
		an[0].x = this->x, an[0].y = this->y, an[1].x = a.get_r();
		PolygonUtil::node* bn = new PolygonUtil::node[b.get_n()+1];
		for (int i = 1; i <= b.get_n(); i++)
			bn[i].x = other.x + b.get_xs()[i - 1] * cos(other.direct) - b.get_ys()[i - 1] * sin(other.direct),
			bn[i].y = other.y + b.get_ys()[i - 1] * cos(other.direct) + b.get_xs()[i - 1] * sin(other.direct);
		ret = PolygonUtil::Q_Cross_Array(an, -1, bn, b.get_n());
		delete[] an; delete[] bn;
		return ret;
	}
	else if (a.get_type() == 2 && b.get_type() == 1) {
		PolygonUtil::node* an = new PolygonUtil::node[a.get_n()+1];
		for (int i = 1; i <= a.get_n(); i++)
			an[i].x = this->x + a.get_xs()[i - 1] * cos(direct) - a.get_ys()[i - 1] * sin(direct),
			an[i].y = this->y + a.get_ys()[i - 1] * cos(direct) + a.get_xs()[i - 1] * sin(direct);
		PolygonUtil::node* bn = new PolygonUtil::node[2];
		bn[0].x = other.x, bn[0].y = other.y, bn[1].x = b.get_r();
		ret = PolygonUtil::Q_Cross_Array(an, a.get_n(), bn, -1);
		delete[] an; delete[] bn;
		return ret;
	}
	else if (a.get_type() == 2 && b.get_type() == 2) {
		PolygonUtil::node* an = new PolygonUtil::node[a.get_n()+1];
		for (int i = 1; i <= a.get_n(); i++)
		{
			an[i].x = this->x + a.get_xs()[i - 1] * cos(direct) - a.get_ys()[i - 1] * sin(direct),
			an[i].y = this->y + a.get_ys()[i - 1] * cos(direct) + a.get_xs()[i - 1] * sin(direct);
		}
		PolygonUtil::node* bn = new PolygonUtil::node[b.get_n()+1];
		for (int i = 1; i <= b.get_n(); i++)
		{
			bn[i].x = other.x + b.get_xs()[i - 1] * cos(other.direct) - b.get_ys()[i - 1] * sin(other.direct),
			bn[i].y = other.y + b.get_ys()[i - 1] * cos(other.direct) + b.get_xs()[i - 1] * sin(other.direct);
		}
		ret = PolygonUtil::Q_Cross_Array(an, a.get_n(), bn, b.get_n());
		delete[] an; delete[] bn;
		return ret;
	}
	else {
		std::cout << "Unexpected type of plane_model:" << a.get_type() << " and " << b.get_type() << std::endl;
		return ret;
	}
}

#undef _2(X)
