#include "tank.h"
#include "map.h"
#include "collide.h"

extern AllObjects All_Ob; //�ⲿ���÷���
extern int mapIndex[rows][cols];
CollideObject Collides;

TANK::TANK(int x, int y, Direction dir)
{
	maprow = x;
	mapcol = y;
	direction = dir;
	xlength = (double)WindowWidth / rows;
	ylength = (double)WindowHeight / (cols+1);
	this->x = (int)mapcol * xlength;
	this->y = (int)maprow * ylength;
	cout <<"̹�˳�ʼ������"<<this->x <<' '<<this->y << endl;
	hBlt = (HBITMAP)LoadImage(NULL, L"image/mytank_66.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void TANK::Update(double xlength, double ylength)
{
	this->xlength = xlength;
	this->ylength = ylength;
}

void TANK::CanRun(bool& can_run, int xflag1, int xflag2, int yflag1, int yflag2)
{
	int abscol = mapcol;
	int absrow = maprow;
	cout << "��ǰʵ������" << absrow << ' ' << abscol << "��ǰ��������" << maprow << ' ' << mapcol << endl;
	double temp_x={}, temp_y={};
	switch (direction)
	{
	case up:
		temp_y = y - int(1./step * (int)ylength);
		temp_x = x;
		break;
	case down:
		temp_y = y + int(1./step * (int)ylength);
		temp_x = x;
		break;
	case Direction::left:
		temp_y = y;
		temp_x = x - int(1./step * (int)xlength);
		break;
	case Direction::right:
		temp_y = y;
		cout << (1. / step * (int)xlength) << endl;
		cout << x << endl;
		temp_x = x + int(1./step * (int)xlength);
		cout << temp_x <<round(temp_x)<<endl;
		break;
	}
	Rect rect1(temp_x, temp_y, xlength, ylength);
	Point p(absrow+xflag1, abscol+yflag1);
	Point p2(absrow+xflag2, abscol+yflag2);
	for (int j = 0; j < All_Ob.object_num && can_run; j++)
	{
		int temp_row = All_Ob.Objects[j].point.maprow;
		int temp_col = All_Ob.Objects[j].point.mapcol;
		if ((All_Ob.Objects[j].point == p || All_Ob.Objects[j].point == p2) && mapIndex[temp_row][temp_col] != 2)
		{
			if (Collides.Collide(All_Ob.Objects[j].rect, rect1))
			{
				can_run = false;
			}
		}
	}
}

void TANK::Update()
{
	if (change_dir == false)
	{
		bool can_run = true;
		switch (direction)
		{
		case up:
			if (maprow <= 0) can_run = false;
			CanRun(can_run, -1, -1, 0, 1);
			break;
		case down:
			if (maprow >= rows-1) can_run = false;
			CanRun(can_run, 1, 1, 0, 1);
			break;
		case Direction::left:
			if (mapcol <= 0) can_run = false;
			CanRun(can_run, 0, -1, -1, -1);
			break;
		case Direction::right:
			if (mapcol >= cols - 1) can_run = false;
			CanRun(can_run, 0, 1, 1, 1);
			break;
		}
		if(can_run)
			this->MOVE();
	}
	this->x = mapcol * xlength;
	this->y = maprow * ylength;
	show();
}

void TANK::show()
{
	cout << "��ǰ̹������" << endl;
	cout << x << ' ' << y << ' ' << xlength << ' ' << ylength << endl;
	cout << "��ǰ��������" << maprow <<' '<< mapcol << endl;
}

bool TANK::Collide(Rect&rect)
{
	if (!(x > rect.x + (int)rect.width || y > rect.y + (int)rect.height || x + (int)xlength < rect.x || y + (int)ylength < rect.y))
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
		if (this->maprow <= 0) this->maprow = 0;
		break;
	case down:
		this->maprow += 1. / step;
		if (this->maprow >= rows - 1) this->maprow = rows - 1;
		break;
	case Direction::left:
		this->mapcol -= 1. / step;
		if (this->mapcol <= 0) this->mapcol = 0;
		break;
	case Direction::right:
		this->mapcol += 1. / step;
		if (this->mapcol >= cols - 1) this->mapcol = cols - 1;
		break;
	}
}