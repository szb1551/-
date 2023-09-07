#include "tank.h"
#include "map.h"

TANK::TANK(int x, int y, Direction dir)
{
	maprow = x;
	mapcol = y;
	direction = dir;
	xlength = (double)WindowWidth / rows;
	ylength = (double)WindowHeight / (cols + 1);
	this->x = mapcol * xlength;
	this->y = maprow * ylength;
	hBlt = (HBITMAP)LoadImage(NULL, L"image/mytank_66.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void TANK::Update(double xlength, double ylength)
{
	this->xlength = xlength;
	this->ylength = ylength;
}

void TANK::Update()
{
	if (change_dir == false)
		this->MOVE();
	this->x = mapcol * xlength;
	this->y = maprow * ylength;
}

void TANK::DRAWONE(HDC& hdc) {
	HDC hmemdc = CreateCompatibleDC(hdc);
	SelectObject(hmemdc, hBlt);
	Update();
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
	//StretchBlt(hdc, (tank1->x) - xlength, (tank1->y) - ylength, xlength * 2, ylength * 2, hmemdc, 0 + (tank1->direction), 198, 150, 145, SRCCOPY);
	DeleteObject(hmemdc);
}


void TANK::MOVE()
{
	switch (direction)
	{
	case up:
		this->maprow -= 1./step;
		break;
	case down:
		this->maprow += 1. / step;
		break;
	case Direction::left:
		this->mapcol -= 1. / step;
		break;
	case Direction::right:
		this->mapcol += 1. / step;
		break;
	}
}