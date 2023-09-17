#include "enemy.h"
#include "player.h"
#include "collide.h"

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