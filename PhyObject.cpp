#include "PhyObject.h"

PhyObject::PhyObject()
{
}

PhyObject::~PhyObject()
{
}

void PhyObject::update()
{
	if(moveable)
	{
		mPos += mVel;
		mVel += mAcc;
		mRot += mRotVel;
	}

}