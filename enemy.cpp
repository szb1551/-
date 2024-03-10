#include "bin/enemy.h"
#include "bin/player.h"
#include "bin/collide.h"
#include "bin/PathFind.h"

extern AllObjects All_Ob;
extern int mapIndex[rows][cols];
extern CollideObject Collides;
extern vector<TANK*> EM;
extern Player* PA;


Direction Enemy::EnemyDirection(Point_Image target)
{
	int r = rand() % 100;
	if (x > target.x)
	{
		if (y > target.y)
		{
			if (r <= 50) return Direction::left;
			return Direction::up;
		}
		else
		{
			if (r <= 50) return Direction::left;
			return Direction::down;
		}
	}
	else
	{
		if (y > target.y)
		{
			if (r <= 50) return Direction::right;
			return Direction::up;
		}
		else
		{
			if (r <= 50) return Direction::right;
			return Direction::down;
		}
	}
}


Direction Enemy::EnemyDirection(Point target)
{
	int r = rand() % 100;
	if (maprow > target.maprow)
	{
		if (mapcol > target.mapcol)
		{
			if (r <= 50) return Direction::left;
			return Direction::up;
		}
		else
		{
			if (r <= 50) return Direction::right;
			return Direction::up;
		}
	}
	else
	{
		if (mapcol > target.mapcol)
		{
			if (r <= 50) return Direction::left;
			return Direction::down;
		}
		else
		{
			if (r <= 50) return Direction::right;
			return Direction::down;
		}
	}
}

Direction Enemy::EnemyDirection2(Point target)
{
	vector<node*> openlist;
	vector<node*> closelist;
	int ta = ConvertDoubleToInt(maprow);
	int tb = ConvertDoubleToInt(mapcol);
	pair<int, int> start = { ta, tb };
	pair<int, int> tar = { target.maprow, target.mapcol };
	openlist.push_back(new node(start, tar));
	clock_t startTime, endTime; //���������յ����������ʱ��
	startTime = clock();
	while (openlist.size() != 0 && nodeln(new node(tar, tar), closelist) == nullptr) {
		//��openlist��Ϊ�գ��һ�û����closelist���ҵ��յ�ڵ��ʱ��һֱѭ��
		node* temp = findMinF(openlist); //�ҵ���ǰopenlist�е���Сֵ
		//temp->show();// ��ӡ��ǰ�Ľڵ���Ϣ
		//��openlist��ɾ����ǰ�ڵ�
		int tsize = openlist.size();
		for (int i = 0; i < tsize; i++) {
			node* t = openlist[i];
			if (t->x == temp->x && t->y == temp->y) {
				openlist.erase(openlist.begin() + i);
				break;
			}
		}
		// �����ǰ�ڵ㲻��closelist�оͼ����ȥ
		if (!nodeln(temp, closelist)) {
			closelist.push_back(temp);
		}
		listAppend(temp, tar, openlist, closelist, (int*)mapIndex); // ������Χ�Ľڵ㣬�����ƶ��������ԣ��ж��Ƕ��ٸ��ڵ�
	}
	endTime = clock();
	//cout << "--------------------------------------" << endl;
	//cout << "��ǰ̹��IDΪ:" << ID << endl;
	//cout << maprow <<" "<< mapcol << endl;
	//cout << "The run time is:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	auto res = nodeln(new node(tar, tar), closelist);
	//����·������ ��Ŀ�걻�ϰ����Χ��������Ҫ�ǵ����ĸ�����������ͣ�Ͳ�ǰ
	if (!res)
	{
		queue<pair<int, int>> q;
		q.push(tar);
		vector<pair<int, int>> temp = { {-1,0},{-1,-1}, {-1,1}, {1,-1}, {1,0},{1,1}, {0,-1},{0,1} };
		vector<vector<bool>> visited(rows, vector<bool>(cols));
		visited[tar.first][tar.second] = true;
		for (int i = 0; i < 2; i++) //·������������㷶Χ
		{
			int sz = q.size();
			while (sz-->0)
			{
				auto p = q.front();
				q.pop();
				for (auto info : temp)
				{
					int dx = info.first + p.first;
					int dy = p.second + info.second;
					if (dx < 0 || dx >= rows || dy < 0 || dy >= cols || visited[dx][dy]) continue;
					visited[dx][dy] = true;
					tar = { dx, dy };
					res = nodeln(new node(tar, tar), closelist);
					if (res) break;
					q.push(tar);
				}
			}
		}
	}
	if (!res) cout << "�޿���·��" << endl;
	//else getres(res); //�õ�A*�㷨�õ���·����Ϣ
	stack<node*> s;
	while (res) {
		s.push(res);
		res = res->father;
	}
	node* t1 = s.top(); //Ŀ��ڵ�λ�ò����ڵ�һ�������ڵڶ���
	s.pop();
	int row_temp = CanConvertDoubleToInt(maprow);
	int col_temp = CanConvertDoubleToInt(mapcol);
	if (s.empty())
	{
		if (t1->x > ta)
			return Direction::down;
		else if (t1->x < ta)
			return Direction::up;
		if (t1->y > tb)
			return Direction::right;
		else if (t1->y < tb)
			return Direction::left;
		return EnemyDirection(target);
	}
	node* t2 = s.top();
	//cout << t2->x << ' ' << t2->y << endl; //�鿴Ŀ������
	//cout << ta << ' ' << tb << endl; //�鿴���ǵ���ʼ����(double תint)
	//cout << row_temp << ' ' << col_temp << endl; //�鿴�����Ƿ��ܹ�תint ��1.4��������ģ���1.000001��û�������
	if (row_temp >= 0 && col_temp>=0) {
		if (t2->x > row_temp)
			return Direction::down;
		if (t2->x < row_temp)
			return Direction::up;
		if (t2->y > col_temp)
			return Direction::right;
		if (t2->y < col_temp)
			return Direction::left;
		return EnemyDirection(target);
	}
	else if (row_temp >= 0)
	{
		if (t2->y > mapcol)
			return Direction::right;
		else if (t2->y < mapcol)
			return Direction::left;
	}
	else if (col_temp >= 0)
	{
		if (t2->x > maprow)
			return Direction::down;
		else if (t2->x < maprow)
		{
			return Direction::up;
		}
	}
	if (t2->x > maprow)
		return Direction::down;
	if (t2->x < maprow)
		return Direction::up;
	if (t2->y > mapcol)
		return Direction::right;
	else if (t2->y < mapcol)
		return Direction::left;
	return EnemyDirection(target);
	
}

void Enemy::Update()
{
	bool can_run = true;
	switch (direction)
	{
	case up:
		if (maprow <= 0)
		{
			can_run = false;
			maprow = 0;
		}
		break;
	case down:
		if (maprow >= rows - 1)
		{
			can_run = false;
			maprow = rows - 1;
		}
		break;
	case Direction::left:
		if (mapcol <= 0) {
			can_run = false;
			mapcol = 0;
		}
		break;
	case Direction::right:
		if (mapcol >= cols - 1 - 3) {
			can_run = false;
			mapcol = cols - 1 - 3;
		}
		break;
	}
	CanRun(can_run);
	if (can_run)
		this->MOVE();
	UpdatePosition();
}

void Enemy::UpdatePosition()
{
	this->x = mapcol * xlength;
	this->y = maprow * ylength;
}

bool Enemy::Can_Fire()
{
	int r = rand() % 100;
	if (r <= 0) button_fire = true;
	return TANK::Can_Fire();
}

void Enemy::DRAWONE()
{
	HDC hmemdc = CreateCompatibleDC(hdc);
	SelectObject(hmemdc, hBlt);
	switch (direction)
	{
	case up:
		StretchBlt(hdc, x, y, xlength, ylength, hmemdc, 0, 200, 133, 110, SRCCOPY);
		break;
	case down:
		StretchBlt(hdc, x, y, xlength, ylength, hmemdc, 143, 200, 138, 110, SRCCOPY);
		break;
	case Direction::left:
		StretchBlt(hdc, x, y, xlength, ylength, hmemdc, 438, 210, 115, 105, SRCCOPY);
		break;
	case Direction::right:
		StretchBlt(hdc, x, y, xlength, ylength, hmemdc, 290, 209, 122, 110, SRCCOPY);
		break;
	}
	DeleteObject(hmemdc);
}

void Enemy::CanRun(bool& can_run)
{
	double temp_x = {}, temp_y = {};
	switch (direction)
	{
	case up:
		temp_y = y - int(1. / step * (int)ylength);
		temp_x = x;
		break;
	case down:
		temp_y = y + int(1. / step * (int)ylength);
		temp_x = x;
		break;
	case Direction::left:
		temp_y = y;
		temp_x = x - int(1. / step * (int)xlength);
		break;
	case Direction::right:
		temp_y = y;
		temp_x = x + int(1. / step * (int)xlength);
		break;
	}
	Rect rect1(temp_x, temp_y, xlength, ylength);
	for (int j = 0; j < All_Ob.object_num && can_run; j++)
	{
		int temp_row = All_Ob.Objects[j].point.maprow;
		int temp_col = All_Ob.Objects[j].point.mapcol;
		if (mapIndex[temp_row][temp_col] != 2)
		{
			if (Collides.Collide(All_Ob.Objects[j].rect, rect1))
			{
				can_run = false;
			}
		}
	}
	for (int i = 0; i < EM.size() && can_run; i++)
	{
		Enemy* temp = dynamic_cast<Enemy*>(EM[i]);
		if (temp->show == true&&temp->GetID()!=ID)
		{
			Rect rect = temp->Get_Rect();
			if (Collides.Collide(rect, rect1))
				can_run = false;
		}
	}
	if (can_run&&PA)
	{
		Rect rect = PA->Get_Rect();
		if (Collides.Collide(rect, rect1))
			can_run = false;
	}
}