#include "Body.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define FOR_ALL_LIMBS(f) { \
	mSpine->f;    \
	mLeftArm->f;  \
	mRightArm->f; \
	mLeftLeg->f;  \
	mRightLeg->f; \
}

Body::Body()
{
	// Initialize at 0,0
	mPos = vec2D(0,0);
	mVel = vec2D(0,0);
	mAcc = vec2D(0,0);

	// Create skeleton!
	mSpine = new IKchain(&mPos);
	mSpine->addSegment(20.0,M_PI/2.0,10.0);
	mSpine->addSegment(20.0,0,10.0);
	mSpine->addSegment(20.0,0,10.0);
	mSpine->addSegment(30.0,0,10.0);
	mSpine->resetIK();

	//// Arms are children of the 3rd spine link
	mLeftArm = new IKchain(&mSpine->mPositions[3]);
	mLeftArm->addSegment(40.0,-M_PI,10.0);
	mLeftArm->addSegment(70.0,M_PI/2.0,10.0);
	mLeftArm->addSegment(70.0,-M_PI/6.0,10.0);
	mLeftArm->addSegment(10.0,-M_PI/6.0,10.0);
	mLeftArm->resetIK();

	mRightArm = new IKchain(&mSpine->mPositions[3]);
	mRightArm->addSegment(40.0,0.0,10.0);
	mRightArm->addSegment(70.0,-M_PI/2.0,10.0);
	mRightArm->addSegment(70.0,M_PI/6.0,10.0);
	mRightArm->addSegment(10.0,M_PI/6.0,10.0);
	mRightArm->resetIK();

	mLeftLeg = new IKchain(&mPos);
	mLeftLeg->addSegment(20.0,-M_PI/4.0,10.0);
	mLeftLeg->addSegment(70.0,-M_PI/4.0,10.0);
	mLeftLeg->addSegment(70.0,0.0,10.0);
	mLeftLeg->addSegment(10.0,M_PI/4.0,10.0);
	mLeftLeg->resetIK();

	mRightLeg = new IKchain(&mPos);
	mRightLeg->addSegment(20.0,-M_PI/2.0 - M_PI/4.0,10.0);
	mRightLeg->addSegment(70.0,M_PI/4.0,10.0);
	mRightLeg->addSegment(70.0,0.0,10.0);
	mRightLeg->addSegment(10.0,-M_PI/4.0,10.0);
	mRightLeg->resetIK();

}

Body::~Body()
{
	delete mSpine;
	delete mLeftArm;
	delete mRightArm;
	delete mLeftLeg;
	delete mRightLeg;
}

void Body::drawGL()
{
	FOR_ALL_LIMBS(drawGL());
}

void Body::update()
{
	// Move
	translate(mVel);
	mVel += mAcc;

	// Calculate IK controls
	FOR_ALL_LIMBS(calcIK());
	
	for(int x=0;x<mRightLeg->mBodyParts.size();x++)
		mRightLeg->mBodyParts[x].speedupTo(mVel);

	for(int x=0;x<mLeftLeg->mBodyParts.size();x++)
		mLeftLeg->mBodyParts[x].speedupTo(mVel);

	for(int x=0;x<mLeftArm->mBodyParts.size();x++)
		mLeftArm->mBodyParts[x].speedupTo(mVel);
}

void Body::collide(EllipseObject *obj)
{
	vec2D results[6];
	results[0] = mRightLeg->collide(obj); 
	results[1] = mRightArm->collide(obj); 
	results[3] = mLeftArm->collide(obj); 
	results[4] = mSpine->collide(obj);
	results[5] = mLeftLeg->collide(obj);

	

	for(int x=0;x<5;x++)
	if(results[x].x() !=  0 || results[x].y() != 0)
	{
		this->speedupTo(results[x]);
		for(int x=0;x<mRightLeg->mBodyParts.size();x++)
		mRightLeg->mBodyParts[x].speedupTo(mVel);

	for(int x=0;x<mLeftLeg->mBodyParts.size();x++)
		mLeftLeg->mBodyParts[x].speedupTo(mVel);

	for(int x=0;x<mLeftArm->mBodyParts.size();x++)
		mLeftArm->mBodyParts[x].speedupTo(mVel);
	}

}

void Body::translate(vec2D v)
{
	// Move origin
	mPos += v;

	// Move all IK controllers to match
	FOR_ALL_LIMBS(mGoal += v);

	// Calculate IK
	FOR_ALL_LIMBS(calcFK());
	FOR_ALL_LIMBS(moveBodyParts());
}