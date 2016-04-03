/*
 * MoveToWaypoint.cpp
 *
 *  Created on: Aug 5, 2015
 *      Author: colman
 */

#include "MoveToWaypoint.h"
#define FORWARD_SPEED_DURING_TURN 0.1
#define TURN_SPEED 0.2
#define AFTER_ROTATE_FORWARD_SPEED 0.5

#define TURN_SIDE_INDICATOR -1
#define GOOD_DEGREE_DELTA 2

MoveToWaypoint::MoveToWaypoint(Robot *robot) : Behavior(robot)
{
	strBehaviorName = "MoveToWaypoint";
}

MoveToWaypoint::~MoveToWaypoint() {
	// TODO Auto-generated destructor stub
}

bool MoveToWaypoint::startCond()
{
	return (!checkObstacleInFront(0));
}

bool MoveToWaypoint::stopCond()
{
	return (checkObstacleInFront(0));
}

void MoveToWaypoint::action()
{
	double dDeltaX = pNextWaypoint->x - _robot->getX();
	double dDeltaY = pNextWaypoint->y - _robot->getY();

	double dDegToWaypoint = atan(dDeltaY / dDeltaX);
	double dDegAcoardingToYaw = _robot->getYaw();
	double dDegsDelta = dDegToWaypoint - dDegAcoardingToYaw;


	if ((-GOOD_DEGREE_DELTA < dDegsDelta) && (dDegsDelta < GOOD_DEGREE_DELTA))
	{
		  // FORWARD
		  _robot->setSpeed(AFTER_ROTATE_FORWARD_SPEED, 0);
	}
	// TODO: this Could be a complex condition - depanding if yaw is 360FOrmat or -/+180FOrmat
	else
	{
		if (dDegsDelta < 0)
		{
			// rotate to side of the waypoint according the SIDE_INDICATOR
			_robot->setSpeed(FORWARD_SPEED_DURING_TURN, (0 + TURN_SIDE_INDICATOR) * TURN_SPEED);
		}
		else
		{
			// rotate to side of the waypoint according the SIDE_INDICATOR
			_robot->setSpeed(FORWARD_SPEED_DURING_TURN, (0 - TURN_SIDE_INDICATOR) * TURN_SPEED);
		}
	}
}

void MoveToWaypoint::setNextWaypoint(Node* pPoint)
{
	pNextWaypoint = pPoint;
}
