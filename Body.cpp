#include "Body.h"

#define _USE_MATH_DEFINES
#include <math.h>

Body::Body()
{
	// Initialize at 0,0
	mOrigin = new vec2D(0,0);

	// Create skeleton!
	mSpine = new IKchain(mOrigin);
	mSpine->addSegment(20.0,M_PI/2.0);
	mSpine->addSegment(20.0,0);
	mSpine->addSegment(20.0,0);
	mSpine->addSegment(30.0,0);
	mSpine->initIKController();

	mLeftArm = new IKchain(&mSpine->mPositions[3]);
	mLeftArm->addSegment(40.0,-M_PI);
	mLeftArm->addSegment(70.0,M_PI/2.0);
	mLeftArm->addSegment(70.0,-M_PI/6.0);
	mLeftArm->addSegment(10.0,-M_PI/6.0);
	mLeftArm->initIKController();

	mRightArm = new IKchain(&mSpine->mPositions[3]);
	mRightArm->addSegment(40.0,0.0);
	mRightArm->addSegment(70.0,-M_PI/2.0);
	mRightArm->addSegment(70.0,M_PI/6.0);
	mRightArm->addSegment(10.0,M_PI/6.0);
	mRightArm->initIKController();

	mLeftLeg = new IKchain(mOrigin);
	mLeftLeg->addSegment(20.0,-M_PI/4.0);
	mLeftLeg->addSegment(70.0,-M_PI/4.0);
	mLeftLeg->addSegment(70.0,0.0);
	mLeftLeg->addSegment(10.0,M_PI/4.0);
	mLeftLeg->initIKController();

	mRightLeg = new IKchain(mOrigin);
	mRightLeg->addSegment(20.0,-M_PI/2.0 - M_PI/4.0);
	mRightLeg->addSegment(70.0,M_PI/4.0);
	mRightLeg->addSegment(70.0,0.0);
	mRightLeg->addSegment(10.0,-M_PI/4.0);
	mRightLeg->initIKController();

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
	mSpine->drawGL();
	mLeftArm->drawGL();
	mRightArm->drawGL();
	mLeftLeg->drawGL();
	mRightLeg->drawGL();
}

void Body::update()
{
	// Move limbs towards IK controllers
	mSpine->doIKStep();
	mLeftArm->doIKStep();
	mRightArm->doIKStep();
	mLeftLeg->doIKStep();
	mRightLeg->doIKStep();

	// Calculate positions using FK
	mSpine->calcFK();
	mLeftArm->calcFK();
	mRightArm->calcFK();
	mLeftLeg->calcFK();
	mRightLeg->calcFK();
}