#include "bin/PathFind.h"

node* findMinF(vector<node*> openlist) {
	int minF = INT_MAX;
	int minIndex = 0;
	for (int i = 0; i < openlist.size(); i++) {
		if (openlist[i]->fval == -1) continue;
		if (openlist[i]->fval < minF) {
			minIndex = i;
			minF = openlist[i]->fval;
		}
	}
	return openlist[minIndex];
}

node* nodeln(node* cur, vector<node*> list) {
	if (list.size() == 0) return nullptr;
	for (auto i : list) {
		if (i->x == cur->x && i->y == cur->y)
			return i;
	}
	return nullptr;
}

void listAppend(node* cur, pair<int,int> target, vector<node*>& openlist, vector<node*>& closelist, int *tarmap) {
	vector<pair<int, int>> points;
	vector<pair<int, int>> temp = { {-1,0},{1,0},{0,-1},{0,1} };
	for (auto i : temp) {
		points.push_back({ cur->x + i.first, cur->y + i.second });
	}
	for (auto i : points) {
		int tx = i.first, ty = i.second;
		if(tx<0||tx>=rows||ty<0||ty>=cols) continue;
		node* t = new node(i, target, cur); //创建节点，同时设该节点的父节点为当前节点
		node* t1 = nodeln(t, openlist); //看看节点是否在openlist里面
		node* t2 = nodeln(t, closelist); //当前节点是否在closelist中
		if (*(tarmap + rows*tx + ty) == 1 || *(tarmap + rows * tx + ty) == 3 || t2) continue; //如果当前节点是障碍物，跳过
		if (t1 && t1->gval > t->gval) {
			/*如果当前节点的gval比openlist中的该节点小
			这说明之前的路径走到的此节点不如当前路径走到此节点的代价小
			那么就更新当前的节点 核心步骤*/
			for (int i = 0; i < openlist.size(); i++) {
				node* &temp = openlist[i];
				if (temp->x == t1->x && temp->y == t1->y) {
					temp = t1;
					break;
				}
			}
		}
		if (!t1) {
			//如果当前节点不在openlist中，就直接加入到openlist中
			openlist.push_back(t);
		}
	}
}

void getres(node* res) {
	//打印路径
	//从最终的节点来找到起点，反向记录路径，正向打印链表
	//我们的起点的father是nullptr，所以是有遍历终点的
	stack<pair<int, int>> reslist;
	auto cur = res;
	while (cur) {
		reslist.push({ cur->x, cur->y });
		cur = cur->father;
	}
	while(!reslist.empty()) {
		auto info = reslist.top();
		reslist.pop();
		cout << info.first << ' ' << info.second << endl;
	}
	cout << "---------------------------------------" << endl;
	return;
}


void showList(vector<node*> list) {
	//打印openlist或者closelist用于调试
	for (auto i : list) {
		printf("(%d, %d):F:%d\n", i->x, i->y, i->fval);
	}
}