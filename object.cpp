#pragma once
#include "plane_model.h"
#include <iostream>
#include "statics.h"
#include "object.h"

#define _2(X) ((X)*(X))
collapse_result object::collapseWith(object const& other)
{
	statics st;
	plane_model a = st.resource_library.get_model(state),b=st.resource_library.get_model(other.state);
	collapse_result ret; ret.isCollapse = false, ret.dx = ret.dy = 0;
	if (a.get_type() == 0 || b.get_type() == 0) {
		return ret;
	}
	else if (a.get_type() == 1 && b.get_type() == 1) {
		float dis = sqrt(_2(x - other.x) + _2(y - other.y));
		if ( dis < a.get_r() + b.get_r()) {
			ret.isCollapse = true;
			ret.dx = (x - other.x) * (a.get_r() + b.get_r() - dis) / dis,
			ret.dy = (y - other.y) * (a.get_r() + b.get_r() - dis) / dis;
			return ret;
		}
		else {
			return ret;
		}
	}
	else if (a.get_type() == 1 && b.get_type() == 2) {
		return ret;
	}
	else if (a.get_type() == 2 && b.get_type() == 1) {
		return ret;
	}
	else if (a.get_type() == 2 && b.get_type() == 2) {
		return ret;
	}
	else {
		std::cout << "plane_model:Unexcepted type\n";
		return ret;
	}
}
#undef _2(X)
