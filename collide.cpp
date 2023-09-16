#include "collide.h"


void AllObjects::Insert(Object ob)
{
	Objects.push_back(ob);
	object_num++;
}

void AllObjects::Delete(Object ob)
{
	for (int i = 0; i < object_num; i++)
	{
		if (Objects[i] == ob)
		{
			object_num--;
			Objects.erase(Objects.begin() + i);
			break;
		}
	}
}

void AllObjects::Delete(int i)
{
	object_num--;
	Objects.erase(Objects.begin() + i);
}

void AllObjects::show()
{
	for (int i = 0; i < object_num; i++)
	{
		cout << Objects[i].rect << endl;
	}
}

bool CollideObject::Collide(Rect& rect1, Rect& rect2)
{
	
	if (!(rect1.x >= rect2.x + rect2.width || rect1.y >= rect2.y + rect2.height || rect1.x + rect1.width <= rect2.x || rect1.y + rect1.height <= rect2.y))
	{
		cout << 1 << endl;
		cout << "RECT1" << ' ' << rect1.x << ' ' << rect1.y << endl;
		cout << "RECT2" << ' ' << rect2.x << ' ' << rect2.y << endl;
		return true;
	}
	return false;
}