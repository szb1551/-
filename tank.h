#pragma once
#include"include.h"


enum Direction{up, down,left,right};

class TANK {
private:
	//int count4;
	double xverb;
	double yverb;
public:
	double x;
	double y;
	int maprow;
	int mapcol;
	Direction direction;
	int life;
	TANK(int x1, int y1, Direction dir);
	void Update(double xlength, double ylength);
};