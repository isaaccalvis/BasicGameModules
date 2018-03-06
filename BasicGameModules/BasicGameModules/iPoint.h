#ifndef __IPOINT_H__
#define __IPOINT_H__

class iPoint {
public:
	iPoint();
	iPoint(int nx, int ny);

	bool operator == (iPoint objComp);
public:
	int x;
	int y;
};

class fPoint {
public:
	fPoint();
	fPoint(float nx, float ny);

public:
	float x;
	float y;
};

#endif