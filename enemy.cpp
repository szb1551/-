#include "enemy.h"



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

void Enemy::DRAWONE()
{
	HDC hmemdc = CreateCompatibleDC(hdc);
	SelectObject(hmemdc, hBlt);
	//Update();
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