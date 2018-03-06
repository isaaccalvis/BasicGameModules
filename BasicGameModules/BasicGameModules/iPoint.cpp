#include "iPoint.h"

iPoint::iPoint()
{
	x = 0;
	y = 0;
}

iPoint::iPoint(int nx, int ny)
{
	x = nx;
	y = ny;
}

bool iPoint::operator == (iPoint objComp) {
	if (this->x == objComp.x && this->y == objComp.y)
		return true;
	return false;
}

fPoint::fPoint()
{
	x = 0.0f;
	y = 0.0f;
}

fPoint::fPoint(float nx, float ny)
{
	x = nx;
	y = ny;
}