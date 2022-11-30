#include <queue>
#include <ctime>
#include <random>
#include "plane_model.h"

namespace PolygonUtil{
	const int M = 10;
	struct node {//点类或向量类
		double x, y;
	};
	struct re_line {//直线类
		node nd1, nd2;
		double dis;
		friend bool operator > (re_line x, re_line y) {
			return x.dis > y.dis;
		}
	};
	class Shape {//多边形类
	public:
		Shape() {
			len = 0;
		}
		Shape(node s[], int l) {
			if (l == -1)
			{
				len = l;
				k[0] = s[0];
				k[1].x = s[1].x;
				return;
			}
			for (int i = 1; i <= l; i++)
			{
				k[i] = s[i];
			}
			len = l;
		}
		//		~Shape();
		friend node Q_core(Shape ts);
		friend node Q_core_sec(Shape ts);
		friend node Support(Shape ts1, Shape ts2, node fstd);
	private:
		node k[M];
		int len;
	};
	std::priority_queue < re_line, std::vector<re_line>, std::greater<re_line >> rep;
	node wt1, wt2, wt3;//单纯形中的点
	double eps = 1e-6;
	node Q_ori(node c1, node c2) {//求垂直指向原点的方向向量
		double dltx, dlty, dlts;
		node nw;
		if (fabs(c2.y - c1.y) <= eps)
		{
			nw.x = 0;
			nw.y = c1.y;
		}
		else if (fabs(c2.x - c1.x) <= eps)
		{
			nw.x = c1.x;
			nw.y = 0;
		}
		else
		{
			dlty = (c2.y - c1.y);
			dltx = (c2.x - c1.x);
			dlts = dlty / dltx;
			nw.y = (c1.y - c1.x * dlts) / (dlts * dlts + 1);
			nw.x = -dlts * nw.y;
		}
		nw.x = -nw.x;
		nw.y = -nw.y;
		return nw;
	}
	node Q_core(Shape ts) {//求中心
		if (ts.len == -1) return ts.k[0];
		node nw;
		nw.x = 0;
		nw.y = 0;
		for (int i = 1; i <= ts.len; i++)
		{
			nw.x += ts.k[i].x;
			nw.y += ts.k[i].y;
		}
		nw.x /= ts.len;
		nw.y /= ts.len;
		return nw;
	}
	node Q_core_sec(Shape ts){
		node nw;
		if(ts.len==-1)
		{
			nw=ts.k[0];
			nw.x+=ts.k[1].x;
			return nw;
		}
		return ts.k[1];
	}
	double num_rep1(node x, node y) {//向量数量积
		return x.x * y.x + x.y * y.y;
	}
	node Support(Shape ts1, Shape ts2, node fstd) {//ts为待求点，fstd为标准方向向量
		node ans1 = ts1.k[1], re_fstd, ans2 = ts2.k[1];
		re_fstd.x = -fstd.x;
		re_fstd.y = -fstd.y;
		double fstd_len = sqrt(num_rep1(fstd, fstd)), nw1 = num_rep1(ts1.k[1], fstd) / fstd_len, nw2 = num_rep1(ts2.k[1], re_fstd) / fstd_len;
		if (ts1.len == -1)
		{
			double sx = fstd.y / fstd_len, cx = fstd.x / fstd_len;
			ans1.x = ts1.k[0].x + ts1.k[1].x * cx;
			ans1.y = ts1.k[0].y + ts1.k[1].x * sx;
		}
		else
		{
			for (int i = 2; i <= ts1.len; i++)
			{
				if (num_rep1(ts1.k[i], fstd) / fstd_len > nw1)
				{
					nw1 = num_rep1(ts1.k[i], fstd) / fstd_len;
					ans1 = ts1.k[i];
				}
			}
		}
		if (ts2.len == -1)
		{
			double sx = re_fstd.y / fstd_len, cx = re_fstd.x / fstd_len;
			ans2.x = ts2.k[0].x + ts2.k[1].x * cx;
			ans2.y = ts2.k[0].y + ts2.k[1].x * sx;
		}
		else
		{
			for (int i = 2; i <= ts2.len; i++)
			{
				if (num_rep1(ts2.k[i], re_fstd) / fstd_len > nw2)
				{
					nw2 = num_rep1(ts2.k[i], re_fstd) / fstd_len;
					ans2 = ts2.k[i];
				}
			}
		}
		ans1.x -= ans2.x;
		ans1.y -= ans2.y;
		return ans1;
	}
	double Q_len(node c1, node c2) {//求两点间距离
		return sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));
	}
	double Q_S(node c1, node c2, node c3) {
		double x1 = Q_len(c1, c2), x2 = Q_len(c2, c3), x3 = Q_len(c3, c1), p = (x1 + x2 + x3) / 2;
		return sqrt(p * (p - x1) * (p - x2) * (p - x3));
	}
	double Q_len(node nd, node c1, node c2) {//求nd到c1，c2两点确定的直线的距离
		return fabs(((c2.y - c1.y) * nd.x - (c2.x - c1.x) * nd.y) + (c1.y * (c2.x - c1.x) - c1.x * (c2.y - c1.y))) / sqrt((c2.y - c1.y) * (c2.y - c1.y) + (c2.x - c1.x) * (c2.x - c1.x));
	}
	bool check() {//判断原点是否在三角形中
		node ret;
		ret.x = 0;
		ret.y = 0;
		return fabs(Q_S(wt1, wt2, wt3) - Q_S(wt1, wt2, ret) - Q_S(wt1, wt3, ret) - Q_S(wt2, wt3, ret)) < eps;
	}
	bool check2(node fstd, node nw) {//判断是否退出GJK循环
		return fstd.x * (nw.x) + fstd.y * (nw.y) < 0;
	}
	bool cmp(node nd1, node nd2) {//两点是否相等
		return (fabs(nd1.x - nd2.x) <= eps) && (fabs(nd1.y - nd2.y) <= eps);
	}
	void usep() {
		node ret;
		ret.x = 0;
		ret.y = 0;
		double len1, len2;
		len1 = Q_len(ret, wt1, wt3);
		len2 = Q_len(ret, wt2, wt3);
		if (len1 < len2) wt2 = wt3;
		else wt1 = wt3;
		return;
	}
	bool GJK(Shape ts1, Shape ts2) {//判断是否碰撞以及找到单纯形
		long time = clock();
		while (1)
		{
			wt3 = Support(ts1, ts2, Q_ori(wt1, wt2));
			if (check())
			{
				return true;
			}
			if (check2(Q_ori(wt1, wt2), wt3))
			{
				return false;
			}
			usep();
			if (clock() - time > 5)return false;
		}
	}
	node EPA(Shape ts1, Shape ts2) {
		re_line nw_line;
		node fstd, nw_nd, re;
		re.x = 0, re.y = 0;
		long time = clock();
		while (1)
		{
			nw_line = rep.top();
			rep.pop();
			fstd = Q_ori(nw_line.nd1, nw_line.nd2);
			fstd.x = -fstd.x;
			fstd.y = -fstd.y;
			nw_nd = Support(ts1, ts2, fstd);
			if (cmp(nw_nd, nw_line.nd1) || cmp(nw_nd, nw_line.nd2))
			{
				return fstd;
			}
			rep.push({ nw_line.nd1,nw_nd,Q_len(re,nw_line.nd1,nw_nd) });
			rep.push({ nw_line.nd2,nw_nd,Q_len(re,nw_line.nd2,nw_nd) });
			if (clock() - time > 5) {
				re.x = rand() % 10, re.y = rand() % 10;
				return re;
			}
		}
	}
	collapse_result Q_Cross_Array(node st1[], int lent1, node st2[], int lent2) {
		rep = {};
		node core1, core2;
		Shape tst1(st1, lent1);
		Shape tst2(st2, lent2);
		core1 = Q_core(tst1);
		core2 = Q_core(tst2);
		if(cmp(core1,core2))
		{
			core2 = Q_core_sec(tst2);
		}
		core1.x -= core2.x;
		core1.y -= core2.y;//core1成为初始方向向量
		wt1 = Support(tst1, tst2, core1);
		core1.x = -core1.x;
		core1.y = -core1.y;
		wt2 = Support(tst1, tst2, core1);
		node re;
		re.x = 0;
		re.y = 0;
		collapse_result anst;
		anst.isCollapse = GJK(tst1, tst2);
		if (anst.isCollapse)
		{
			rep.push({ wt1,wt2,Q_len(re,wt1,wt2) });
			rep.push({ wt1,wt3,Q_len(re,wt1,wt3) });
			rep.push({ wt3,wt2,Q_len(re,wt3,wt2) });
			re = EPA(tst1, tst2);
			anst.dx = re.x;
			anst.dy = re.y;
		}
		//while (!rep.empty())rep.pop();
		return anst;
	}
}
