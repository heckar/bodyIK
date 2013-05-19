#pragma once

#include "vec2D.h"

class PhyObject
{
public:
	PhyObject();
	~PhyObject();

	void update();

private:
	vec2D mPos;
	vec2D mVel;
	vec2D mAcc;
};

