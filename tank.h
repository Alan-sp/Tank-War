#include <string>
#include "object.h"
#include "statics.h"

#ifndef TANK_H
#define TANK_H
class tank :public object {
public:
	double speed;
	double wspeed;//弧度制 
	int name, tw, ta, ts, td, tshoot, cd_time, currentcd;
	long shootcount, hitcount;
	std::string strname;
	int attack_id;
	int buff_state;
	tank(double dx, double dy, double dir, int m, int tw, int ta, int ts, int td, int tshoot, std::string strname);
	void ticking();
	void collapse(object* other, collapse_result result);
	void Q_buff();
};

#endif // !TANK_H