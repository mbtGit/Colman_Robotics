/*
 * TurnRight.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: colman
 */

#include "TurnRight.h"
#define RIGHT_SPEED 0.1

TurnRight::TurnRight(Robot* robot) : Behavior(robot)
{
	strBehaviorName = "TurnRight";
}

TurnRight::~TurnRight() {
	// TODO Auto-generated destructor stub
}

void TurnRight::action()
{
	while (this->startCond())
	{
		_robot->setSpeed(0.0, RIGHT_SPEED);
		_robot->Read();
	}
}

bool TurnRight::startCond()
{
	return (checkObstacleInFront(1));
}
bool TurnRight::stopCond()
{
	return (!checkObstacleInFront(1));
}
