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
	ylength = (double)WindowHeight / (cols+1);
	this->x = (int)mapcol * xlength;
	this->y = (int)maprow * ylength;
	cout <<"坦克初始化坐标"<<this->x <<' '<<this->y << endl;
	hBlt = (HBITMAP)LoadImage(NULL, L"image/mytank_66.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void TANK::SetBlt(HBITMAP hBit)
{
	hBlt = hBit;
}

void TANK::Update(double xlength, double ylength)
{
	this->xlength = xlength;
	this->ylength = ylength;
}

void TANK::Initial_Bullet()
{
	bullet.dir = direction;
	switch (direction)
	{
	case up:
		bullet.point.Set(x + xlength / 2 - bullet.width/2, y);
		break;
	case down:
		bullet.point.Set(x + xlength/2 - bullet.width/2, y+ ylength);
		break;
	case Direction::left:
		bullet.point.Set(x-bullet.width/2, y + ylength / 2 - bullet.height/2);
		break;
	case Direction::right:
		bullet.point.Set(x + xlength-bullet.width/2, y+ylength/2-bullet.height/2);
		break;
	}
	bullet.status = 1;
	//button_fire = false;
}

bool TANK::Can_Fire()
{
	if (bullet.status == 0 && button_fire==true)
		return true;
	return false;
}

void TANK::CanRun(bool& can_run, int xflag1, int xflag2, int yflag1, int yflag2)
{
	double temp_x = {}, temp_y = {};
	int abscol = mapcol;
	int absrow = maprow;
	cout.precision(4);
	cout << "当前实际坐标" << absrow << ' ' << abscol << "当前虚拟坐标"<< fixed << maprow << ' ' << mapcol << endl;
	cout << defaultfloat;
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

void TANK::CanRun(bool& can_run)
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
		cout << (1. / step * (int)xlength) << endl;
		cout << x << endl;
		temp_x = x + int(1. / step * (int)xlength);
		cout << temp_x << round(temp_x) << endl;
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
}

void TANK::Update()
{
	if (change_dir == false)
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
			//CanRun(can_run, -1, -1, 0, 1);
			break;
		case down:
			if (maprow >= rows - 1)
			{
				can_run = false;
				maprow = rows - 1;
			}
			//CanRun(can_run, 1, 1, 0, 1);
			break;
		case Direction::left:
			if (mapcol <= 0) {
				can_run = false;
				mapcol = 0;
			}
			//CanRun(can_run, 0, 1, -1, -1);
			break;
		case Direction::right:
			if (mapcol >= cols - 1 - 3) {
				can_run = false;
				mapcol = cols-1-3;
			}
			//CanRun(can_run, 0, 1, 1, 1);
			break;
		}
		CanRun(can_run);
		if(can_run)
			this->MOVE();
	}
	this->x = mapcol * xlength;
	this->y = maprow * ylength;
	show();
}

void TANK::show()
{
	cout << "当前坦克坐标" << endl;
	cout << x << ' ' << y << ' ' << xlength << ' ' << ylength << endl;
	cout << "当前虚拟坐标" << maprow <<' '<< mapcol << endl;
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

void TANK::DRAWONE() {
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
	//StretchBlt(hdc, (tank1->x) - xlength, (tank1->y) - ylength, xlength * 2, ylength * 2, hmemdc, 0 + (tank1->direction), 198, 150, 145, SRCCOPY);
	DeleteObject(hmemdc);
}

void TANK::DRAWBULLET()
{
	HDC hmemdc = CreateCompatibleDC(hdc);
	HBRUSH hBlackBrush = CreateSolidBrush(RGB(255, 0, 0));
	RECT rect = { bullet.point.x, bullet.point.y, bullet.point.x+10, bullet.point.y+10 };
	FillRect(hdc, &rect, hBlackBrush);
	DeleteDC(hmemdc);
}

void TANK::Fire()
{
	if (Can_Fire())
	{
		Initial_Bullet();
		DRAWBULLET();
	}
	else if (bullet.status == 1)
	{
		cout << "进入子弹移动" << endl;
		bullet.Update();
		cout << bullet.point << endl;
		DRAWBULLET();
	}
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