#pragma once
#include "node.h"
#include <vector>
#include <stack>
#include <queue>
#include "bin/map.h"
using namespace std;

node* findMinF(vector<node*> openlist); //�ҵ�f��С�Ľڵ�
node* nodeln(node* cur, vector<node*> list); //�ж�cur�ڵ��Ƿ���list��
void listAppend(node* cur, pair<int,int>target,  vector<node*>& openlist, vector<node*>& closelist, int *tarmap);// ������Χ�Ľڵ�, �����ά���飬����һά����
void getres(node* res); //��ӡ·��
void showList(vector<node*> list); //��ӡopenlist����closelist�����ڵ���