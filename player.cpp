#include "bin/player.h"
#include "bin/collide.h"
#include "bin/enemy.h"

extern AllObjects All_Ob;
extern int mapIndex[rows][cols];
extern CollideObject Collides;
extern vector<TANK*> EM;

bool Player::Collide(vector<TANK*> EM)
{
	for (int i = 0; i < EM.size(); i++)
	{
		/*if(TANK::Collide())*/
	}
	return false;
}

void Player::CanRun(bool& can_run)
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
	for (int i = 0; i < EM.size()&&can_run; i++)
	{
		Enemy* temp = dynamic_cast<Enemy*>(EM[i]);
		if (temp->show == true)
		{
			Rect rect = temp->Get_Rect();
			if(Collides.Collide(rect, rect1))
				can_run = false;
		}
	}
}


