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
		node* t = new node(i, target, cur); //�����ڵ㣬ͬʱ��ýڵ�ĸ��ڵ�Ϊ��ǰ�ڵ�
		node* t1 = nodeln(t, openlist); //�����ڵ��Ƿ���openlist����
		node* t2 = nodeln(t, closelist); //��ǰ�ڵ��Ƿ���closelist��
		if (*(tarmap + rows*tx + ty) == 1 || *(tarmap + rows * tx + ty) == 3 || t2) continue; //�����ǰ�ڵ����ϰ������
		if (t1 && t1->gval > t->gval) {
			/*�����ǰ�ڵ��gval��openlist�еĸýڵ�С
			��˵��֮ǰ��·���ߵ��Ĵ˽ڵ㲻�統ǰ·���ߵ��˽ڵ�Ĵ���С
			��ô�͸��µ�ǰ�Ľڵ� ���Ĳ���*/
			for (int i = 0; i < openlist.size(); i++) {
				node* &temp = openlist[i];
				if (temp->x == t1->x && temp->y == t1->y) {
					temp = t1;
					break;
				}
			}
		}
		if (!t1) {
			//�����ǰ�ڵ㲻��openlist�У���ֱ�Ӽ��뵽openlist��
			openlist.push_back(t);
		}
	}
}

void getres(node* res) {
	//��ӡ·��
	//�����յĽڵ����ҵ���㣬�����¼·���������ӡ����
	//���ǵ�����father��nullptr���������б����յ��
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
	//��ӡopenlist����closelist���ڵ���
	for (auto i : list) {
		printf("(%d, %d):F:%d\n", i->x, i->y, i->fval);
	}
}