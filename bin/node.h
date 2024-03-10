#pragma once
#include <iostream>
#include <algorithm>
#include <utility>
#include <ctime>
#include <vector>
class node
{
public:
	node* father; //父节点
	int x, y, gval, hval, fval;
	//g 该节点到父节点的移动代价
	//h 该节点到终端的距离
	//f 启发式代价 f=g+h
	node(std::pair<int, int>point, std::pair<int, int> target, node* father = nullptr);
	void show(); //显示找到的路径
	~node();
};

