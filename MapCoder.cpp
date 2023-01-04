#include <list>
#include <iostream>
#include <sstream>
#include "object.h"
#include "buff.cpp"
#include "rolling_wall.h"
#include "wall.cpp"
#include "shortwall.cpp"
#include "midwall.cpp"
#include "movableblock.cpp"
#include "tank.h"

#ifndef MAPCODER_CPP
#define MAPCODER_CPP

namespace MapCoder {
	/*
	ID|X|Y|Direction|SpecialArg
	*/

	struct Point {
		double x, y,dir;
	};

	struct Map {
		std::list<object*> objs;
		std::list<Point> spawns;
	};

	std::string encode(Map m) {
		std::ostringstream oss("");
		oss << m.objs.size() + m.spawns.size() << '\n';
		for (auto i = m.objs.begin(); i != m.objs.end(); i++) {
			if (wall* p = dynamic_cast<wall*>(*i)) {
				oss << 1 << ' ' << p->get_x() << ' ' << p->get_y() << ' ' << p->get_direction() << '\n';
			}
			else if (rolling_wall* p = dynamic_cast<rolling_wall*>(*i)) {
				oss << 2 << ' ' << p->get_x() << ' ' << p->get_y() << ' ' << p->get_direction()<<' ' << p->rolling_speed << '\n';
			}
			else if (buff* p = dynamic_cast<buff*>(*i)) {
				oss << 3 << ' ' << p->get_x() << ' ' << p->get_y() << ' ' << p->get_direction()<<' ' << p->buff_state << '\n';
			}
			else if (shortwall* p = dynamic_cast<shortwall*>(*i)) {
				oss << 10 << ' ' << p->get_x() << ' ' << p->get_y() << ' ' << p->get_direction() << '\n';
			}
			else if (midwall* p = dynamic_cast<midwall*>(*i)) {
				oss << 11 << ' ' << p->get_x() << ' ' << p->get_y() << ' ' << p->get_direction() << '\n';
			}
			else if (movableblock* p = dynamic_cast<movableblock*>(*i)) {
				oss << 12 << ' ' << p->get_x() << ' ' << p->get_y() << ' ' << p->get_direction() << '\n';
			}
		}
		for (auto i = m.spawns.begin(); i != m.spawns.end(); i++) {
			oss << 4 << ' ' << i->x << ' ' << i->y << ' ' << i->dir << '\n';
		}
		return oss.str();
	}

	Map decode(std::string code) {
		std::istringstream iss(code);
		Map ret;
		int n,id;
		double x, y, dir, sa;
		iss >> n;
		while (n--) {
			iss >> id;
			switch (id)
			{
			case 1:
				iss >> x >> y >> dir;
				ret.objs.push_back(new wall(x, y, dir));
				break;
			case 2:
				iss >> x >> y >> dir >> sa;
				ret.objs.push_back(new rolling_wall(x, y, dir, sa));
				break;
			case 3:
				iss >> x >> y >> dir >> sa;
				ret.objs.push_back(new buff(x, y, dir, sa));
				break;
			case 4:
				iss >> x >> y >> dir;
				Point t;
				t.x = x, t.y = y, t.dir = dir;
				ret.spawns.push_back(t);
				break;
			case 10:
				iss >> x >> y >> dir;
				ret.objs.push_back(new shortwall(x, y, dir));
				break;
			case 11:
				iss >> x >> y >> dir;
				ret.objs.push_back(new midwall(x, y, dir));
				break;
			case 12:
				iss >> x >> y >> dir;
				ret.objs.push_back(new movableblock(x, y, dir));
				break;
			default:
				break;
			}
		}
		return ret;
	}
}

#endif // !MAPDECODER_CPP
