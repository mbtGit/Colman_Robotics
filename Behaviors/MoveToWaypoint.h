/*
 * MoveToWaypoint.h
 *
 *  Created on: Aug 5, 2015
 *      Author: colman
 */

#ifndef MOVETOWAYPOINT_H_
#define MOVETOWAYPOINT_H_

#include "Behavior.h"

#include "../Way/Node.h"

class MoveToWaypoint : public Behavior {
public:
	Node* pNextWaypoint;
	void setNextWaypoint(Node* pPoint);
	MoveToWaypoint(Robot *robot);
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
	virtual ~MoveToWaypoint();
};

#endif /* MOVETOWAYPOINT_H_ */
