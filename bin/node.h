#pragma once
#include <iostream>
#include <algorithm>
#include <utility>
#include <ctime>
#include <vector>
class node
{
public:
	node* father; //���ڵ�
	int x, y, gval, hval, fval;
	//g �ýڵ㵽���ڵ���ƶ�����
	//h �ýڵ㵽�ն˵ľ���
	//f ����ʽ���� f=g+h
	node(std::pair<int, int>point, std::pair<int, int> target, node* father = nullptr);
	void show(); //��ʾ�ҵ���·��
	~node();
};

