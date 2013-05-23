#pragma once

#include "vec2D.h"

#define G_ACC -1.0

class PhyObject
{
public:
	PhyObject();
	~PhyObject();

	void update();

	inline void accelerate(vec2D acc) { mAcc += acc; }
	inline void speedup(vec2D vel) { mVel += vel; }
	inline void move(vec2D pos) { mPos += pos; }

protected:
	vec2D mPos;
	vec2D mVel;
	vec2D mAcc;
};

