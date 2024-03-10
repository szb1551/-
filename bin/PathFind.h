#pragma once
#include "node.h"
#include <vector>
#include <stack>
#include <queue>
#include "bin/map.h"
using namespace std;

node* findMinF(vector<node*> openlist); //找到f最小的节点
node* nodeln(node* cur, vector<node*> list); //判断cur节点是否在list中
void listAppend(node* cur, pair<int,int>target,  vector<node*>& openlist, vector<node*>& closelist, int *tarmap);// 处理周围的节点, 传入二维数组，当作一维看待
void getres(node* res); //打印路径
void showList(vector<node*> list); //打印openlist或者closelist，用于调试