#pragma once
#include "include.h"

enum Direction { up, down, right, left };

struct Point
{
	int maprow;
	int mapcol;
	Point(int row, int col) :maprow(row), mapcol(col) {};
	Point() {};
	bool operator ==(Point& p)
	{
		if (this->maprow == p.maprow && this->mapcol == p.mapcol)
			return true;
		return false;
	}
	void Set(int row, int col)
	{
		maprow = row;
		mapcol = col;
	};
};

struct Point_Image
{
	int x;
	int y;
	Point_Image(int row, int col) :x(row), y(col) {};
	Point_Image() {};
	bool operator ==(Point_Image& p)
	{
		if (this->x == p.x && this->y == p.y)
			return true;
		return false;
	}
	void Set(int row, int col)
	{
		x = row;
		y = col;
	};
	friend ostream& operator<<(ostream& os, const Point_Image& point)
	{
		os << point.x << ' ' << point.y;
		return os;
	}
};

struct Rect
{
	int x;
	int y;
	double width;
	double height;
	template<typename T1, typename T2>Rect(T1 x, T1 y, T2 width, T2 height) :x(round(x)), y(round(y)), width(width), height(height) {};
	Rect() {};
	friend ostream& operator<<(ostream& os, const Rect& rect)
	{
		os << rect.x << ' ' << rect.y << ' ' << rect.width << ' ' << rect.height;
		return os;
	}
};

struct Object {
	Rect rect;
	Point point;
	int life;
	bool operator ==(Object& ob)
	{
		if (this->point == ob.point)
			return true;
		return false;
	}
	friend ostream& operator <<(ostream& os, const Object& ob)
	{
		os << ob.rect;
		return os;
	}
};

struct AllObjects
{
	vector<Object> Objects;
	int object_num = 0;
	void Insert(Object ob);
	void Delete(Object ob);
	void Delete(int i);
	void show();
};
