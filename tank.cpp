#include "tank.h"
#include "map.h"
#include "collide.h"

extern AllObjects All_Ob; //外部引用范例
extern int mapIndex[rows][cols];
CollideObject Collides;

TANK::TANK(int x, int y, Direction dir)
{
	maprow = x;
	mapcol = y;
	direction = dir;
	xlength = (double)WindowWidth / rows;
	ylength = (double)WindowHeight / (cols + 1);
	this->x = (int)mapcol * xlength;
	this->y = (int)maprow * ylength;
	cout <<"坦克初始化坐标"<<this->x <<' '<<this->y << endl;
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
	{
		int abscol = mapcol;
		int absrow = maprow;
		cout << "当前实际坐标" << absrow << ' ' << abscol << "当前虚拟坐标" << maprow << ' ' << mapcol << endl;
		bool can_run = true;
		switch (direction)
		{
		case up:
		{
			double temp_y = (maprow - 1. / step) * ylength;
			double temp_x = mapcol * xlength;
			Rect rect1(temp_x, temp_y, xlength, ylength);
			Point p(absrow - 1, abscol);
			Point p2(absrow - 1, abscol + 1);
			for (int j = 0; j < All_Ob.object_num; j++)
			{
				int temp_row = All_Ob.Objects[j].point.maprow;
				int temp_col = All_Ob.Objects[j].point.mapcol;
				if ((All_Ob.Objects[j].point == p|| All_Ob.Objects[j].point == p2) &&mapIndex[temp_row][temp_col]!=2)
				{
					if (Collides.Collide(All_Ob.Objects[j].rect, rect1))
					{
						can_run = false;
						break;
					}
				}
			}
		}
			break;
		case down:
			break;
		case Direction::left:
			break;
		case Direction::right:
			break;
		}
		if(can_run)
			this->MOVE();
	}
	this->x = mapcol * xlength;
	this->y = maprow * ylength;
}

bool TANK::Collide(Rect&rect)
{
	if (!(x > rect.x + rect.width || y > rect.y + rect.height || x + xlength < rect.x || y + ylength < rect.y))
	{
		cout << true << endl;
		return true;
	}	
	return false;
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