#include "bin/node.h"

node::node(std::pair<int, int> point, std::pair<int, int> target, node* parent) {
	x = point.first;
	y = point.second;
	father = parent;
	if (parent == NULL) //û�и��ڵ�ʱ
	{
		gval = -1;
		fval = -1;
		hval = -1;
	}
	else {
		//����g,h,f
		//���μ��㷽ʽλ |x| + |y|
		if (abs(father->x - x) + abs(father->y - y) == 1)
			gval = 10;
		else gval = 14; //�����б�ߵĻ��Ĵ���
		hval = abs(target.first - x) * 10 + abs(target.second - y) * 10;
		fval = gval + hval;
	}
}

void node::show() {
	printf("Location:(%d,%d);Gval:%d;Hval:%d;Fval:%d.\n", x, y, gval, hval, fval);
}

node::~node() {
}