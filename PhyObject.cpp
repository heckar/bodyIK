#include "PhyObject.h"

PhyObject::PhyObject()
{
}

PhyObject::~PhyObject()
{
}

void PhyObject::update()
{
	mPos += mVel;
	mVel += mAcc;
	mRot += mRotVel;
}