#include "bin/node.h"

node::node(std::pair<int, int> point, std::pair<int, int> target, node* parent) {
	x = point.first;
	y = point.second;
	father = parent;
	if (parent == NULL) //没有父节点时
	{
		gval = -1;
		fval = -1;
		hval = -1;
	}
	else {
		//计算g,h,f
		//本次计算方式位 |x| + |y|
		if (abs(father->x - x) + abs(father->y - y) == 1)
			gval = 10;
		else gval = 14; //如果有斜边的话的代价
		hval = abs(target.first - x) * 10 + abs(target.second - y) * 10;
		fval = gval + hval;
	}
}

void node::show() {
	printf("Location:(%d,%d);Gval:%d;Hval:%d;Fval:%d.\n", x, y, gval, hval, fval);
}

node::~node() {
}