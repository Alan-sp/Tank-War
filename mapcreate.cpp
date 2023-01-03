#include <cstdlib>
#include <sstream>
#include <iostream>
#include <random>

#ifndef MAPCREATE_CPP
#define MAPCREATE_CPP

#define pai 3.1415926
namespace mapcreate {
	struct mapx {
		double x, y;
		int id;
		double special;
	}wall[10][10];
	void generateMap(std::ostringstream cout)
	{
		double mapx = 1200, mapy = 800;
		int n = 5, m = 5;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				double sx = mapx * (j - 1) / m;
				double sy = mapy * (i - 1) / n;
				int lx = mapx / m;
				int ly = mapy / n;
				int type = rand() % 2 + 1;
				if (type == 1) {
					wall[i][j].id = (i - 1) * n + j;
					double ssx = rand() % (int)lx + ((double)(rand() % 10)) / 100 + sx;
					double ssy = rand() % (int)ly + ((double)(rand() % 10)) / 100 + sy;
					wall[i][j].x = ssx;
					wall[i][j].y = ssy;
					wall[i][j].special = 0;
					cout << "1" << " " << ssx << " " << ssy << " " << (rand() % 180) * pai << std::endl;
				}
				else {
					wall[i][j].id = (i - 1) * n + j;
					double ssx = rand() % (int)lx + ((double)(rand() % 10)) / 100 + sx;
					double ssy = rand() % (int)ly + ((double)(rand() % 10)) / 100 + sy;
					wall[i][j].x = ssx;
					wall[i][j].y = ssy;
					wall[i][j].special = (rand() % 180) * pai;
					cout << "2" << " " << ssx << " " << ssy << " " << wall[i][j].special << std::endl;
				}
			}
		}
		for (int i = 1; i <= 8; i++) {
			double ssx = rand() % (int)mapx + ((double)(rand() % 10)) / 100;
			double ssy = rand() % (int)mapy + ((double)(rand() % 10)) / 100;
			int buff = rand() % 4 + 1;
			cout << "3" << " " << ssx << " " << ssy << " " << buff << std::endl;
		}
		double ssx = rand() % (int)mapx + ((double)(rand() % 10)) / 100;
		double ssy = rand() % (int)mapy + ((double)(rand() % 10)) / 100;
		cout << "4" << ssx << " " << ssy << " " << 0 << std::endl;
		ssx = rand() % (int)mapx + ((double)(rand() % 10)) / 100;
		ssy = rand() % (int)mapy + ((double)(rand() % 10)) / 100;
		cout << "4" << ssx << " " << ssy << " " << 0 << std::endl;
		return;
	}
}
#undef pai
#endif // !MAPCREATE_CPP



