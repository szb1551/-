#pragma once
#include "map.h"

struct AllObjects
{
	vector<Object> Objects;
	int object_num = 0;
	void Insert(Object ob);
	void Delete(Object ob);
	void show();
};

class CollideObject
{
public:
	bool Collide(Rect& rect1, Rect& rect2);
};