#pragma once

#include "IKchain.h"

class Body
{
public:
	Body();
	~Body();

	void drawGL();
	void update();
private:
	vec2D *mOrigin;

	IKchain *mSpine;
	IKchain *mLeftArm;
	IKchain *mRightArm;
	IKchain *mLeftLeg;
	IKchain *mRightLeg;
};

