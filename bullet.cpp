#include "bullet.h"
#include "map.h"

extern AllObjects All_Ob;
extern int mapIndex[rows][cols];

void Bullet::Move()
{
	switch (dir)
	{
	case Direction::up:
		point.y -= speed;
		if (point.y <= 0) status = 0;
		break;
	case Direction::down:
		point.y += speed;
		if (point.y >= WindowHeight) status = 0;
		break;
	case Direction::left:
		point.x -= speed;
		if (point.x <=0 ) status = 0;
		break;	
	case Direction::right:
		point.x += speed;
		if (point.x >= WindowWidth) status = 0;
		break;
	}
}

bool Bullet::Collide(Rect& rect)
{
	if (!(point.x >= rect.x + rect.width || point.y >= rect.y + rect.height || point.x + width <= rect.x || point.y + height <= rect.y))
	{
		return true;
	}
	return false;
}

void Bullet::Update()
{
	for (int j = 0; j < All_Ob.object_num && status; j++)
	{
		int temp_row = All_Ob.Objects[j].point.maprow;
		int temp_col = All_Ob.Objects[j].point.mapcol;
		if (mapIndex[temp_row][temp_col] != 2)
		{
			if (Collide(All_Ob.Objects[j].rect))
			{
				status = 0;
				All_Ob.Objects[j].life--;
				if(All_Ob.Objects[j].life<=0)
					All_Ob.Delete(j);
			}
		}
	}
	if (status == 1)
		Move();
}