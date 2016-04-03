/*
 * Manager.cpp
 *
 *  Created on: Jun 19, 2015
 *      Author: colman
 */
#define WAYPOINT_IN_RANGE_DISTANCE 0.1

#include "Manager.h"

Manager::Manager(Robot *robot){
	this->robot = robot;
}

Manager::~Manager()
{
	// TODO Auto-generated destructor stub
}

bool Manager::isInWaypointRange(Node* nWaypoint)
{
	return ((abs((this->robot->getX() / mLabMap->GetGridMapFinalResolution()) - nWaypoint->x) < WAYPOINT_IN_RANGE_DISTANCE) &&
			(abs((this->robot->getY() / mLabMap->GetGridMapFinalResolution()) - nWaypoint->y) < WAYPOINT_IN_RANGE_DISTANCE));
}

void Manager::Run()
{
	bool bEnableRobotMotors = false;

	// initiailze stuff
	mLabMap = new Map();
	GetConfig(robot, mLabMap);
	this->robot->init(bEnableRobotMotors);

	// init map staff
	mLabMap->LoadMapFromPng();
	mLabMap->MapWeighting(robot, robot->robotHeight/2);
	mLabMap->InsertMapToMatrix();

	// Get the goal and start points for the path planning
	int nWantedLocationX = robot->robotGoalX / (mLabMap->GetGridMapFinalResolution());
	int nWantedLocationY = robot->robotGoalY / (mLabMap->GetGridMapFinalResolution());
	int nStartX = robot->robotStartX / (mLabMap->GetGridMapFinalResolution());
	int nStartY = robot->robotStartY / (mLabMap->GetGridMapFinalResolution());

	// Calculate the a star
	AStar* aAStarInstance = new AStar();
	lstWaypointsToDestination = aAStarInstance->AStarPath(nStartX,nStartY,nWantedLocationX,nWantedLocationY, mLabMap);
	PrintToPng(nStartX, nStartY, nWantedLocationX, nWantedLocationY);

	// initialize behaviors
	Behavior *turnToWayPoint;

    // Creating behaviors
    Behavior** behaviors = new Behavior*[4];
    behaviors[0] = new MoveToWaypoint(this->robot);
    behaviors[1] = new MoveForward(this->robot);
    behaviors[2] = new TurnRight(this->robot);
    behaviors[3] = new TurnLeft(this->robot);

    // Connecting behaviors
    behaviors[0]->addNext(behaviors[2]);
    behaviors[0]->addNext(behaviors[3]);
    behaviors[1]->addNext(behaviors[2]);
    behaviors[1]->addNext(behaviors[3]);
    behaviors[2]->addNext(behaviors[0]);
    behaviors[3]->addNext(behaviors[0]);

    currBehavior = behaviors[0];

	this->UpdateRobot();

    for (std::list<Node*>::iterator iCurrWaypoint = lstWaypointsToDestination.begin(); iCurrWaypoint != lstWaypointsToDestination.end(); iCurrWaypoint++)
    {
    	PrintToConsole(nStartX,nStartY,nWantedLocationX,nWantedLocationY);
    	((MoveToWaypoint*)behaviors[0])->setNextWaypoint(*iCurrWaypoint);

    	this->UpdateRobot();

    	// while waypoint is not in range
    	while (!this->isInWaypointRange(*iCurrWaypoint))
    	{
    		// If curr behavior can be activated
    		if (currBehavior->startCond())
    		{
    			currBehavior->action();
    		}
    		else
    		{
    			currBehavior = currBehavior->selectNext();
    			cout << "   ...change behavior to " << currBehavior->strBehaviorName;
    		}

        	this->UpdateRobot();
    	}


    }

    std::cout << "Manager Finished!!!" << std::endl;
}


void Manager::UpdateRobot()
{
	robot->Read();
	// TODO: bro' i didn't know wich parameters to enter this method...
	robot->setOdometry();
}
void Manager::PrintToConsole(int nStartX,int nStartY,int nWantedLocationX,int nWantedLocationY)
{
	double robotGridX = robot->getX() / mLabMap->GetGridMapFinalResolution();
	double robotGridY = robot->getY() / mLabMap->GetGridMapFinalResolution();
	system("cls");

	for (int i = 0; i < mLabMap->MapMatrix.size(); i++)
	{
		for (int j = 0; j < mLabMap->MapMatrix[0].size(); j++)
		{
			bool bAStarPoint = false;
			for (std::list<Node*>::iterator listIterator = lstWaypointsToDestination.begin(); listIterator != lstWaypointsToDestination.end(); listIterator++)
			{
				if ((j == (*listIterator)->x) && (i == (*listIterator)->y))
				{
					bAStarPoint = true;
					break;
				}
			}

			if (bAStarPoint)
			{
				cout << ".";
			}
			else if ((j == nWantedLocationX) && (i == nWantedLocationY))
			{
				cout << 'F';
			}
			else if ((j == nStartX) && (i== nStartY))
			{
				cout << 'S';
			}
			else if ((j == robotGridX) && (i == robotGridY))
			{
				cout << '#';
			}
			else
			{
				if (mLabMap->IsCellFree(j,i))
					cout << ' ';
				else
					cout << '0';
			}
		}
		cout << endl;
	}
}
void Manager::PrintToPng(int nStartX,int nStartY,int nWantedLocationX,int nWantedLocationY)
{
	// Start location
	mLabMap->tempImageAfterBlow[(robot->robotStartX * 4 + robot->robotStartY * mLabMap->width * 4) + 0] = 255;
	mLabMap->tempImageAfterBlow[(robot->robotStartX * 4 + robot->robotStartY * mLabMap->width * 4) + 1] = 0;
	mLabMap->tempImageAfterBlow[(robot->robotStartX * 4 + robot->robotStartY * mLabMap->width * 4) + 2] = 0;
	mLabMap->tempImageAfterBlow[(robot->robotStartX * 4 + robot->robotStartY * mLabMap->width * 4) + 3] = 0.1;

	// Goal location
	mLabMap->tempImageAfterBlow[(robot->robotGoalX * 4 + robot->robotGoalY * mLabMap->width * 4) + 0] = 0;
	mLabMap->tempImageAfterBlow[(robot->robotGoalX * 4 + robot->robotGoalY * mLabMap->width * 4) + 1] = 255;
	mLabMap->tempImageAfterBlow[(robot->robotGoalX * 4 + robot->robotGoalY * mLabMap->width * 4) + 2] = 0;
	mLabMap->tempImageAfterBlow[(robot->robotGoalX * 4 + robot->robotGoalY * mLabMap->width * 4) + 3] = 0.1;

	// AStar
	for (std::list<Node*>::iterator listIterator = lstWaypointsToDestination.begin(); listIterator != lstWaypointsToDestination.end(); listIterator++)
	{
		int nX = (*listIterator)->x * mLabMap->GetGridMapFinalResolution();
		int nY = (*listIterator)->y * mLabMap->GetGridMapFinalResolution();
		mLabMap->tempImageAfterBlow[(nX * 4 + nY * mLabMap->width * 4) + 0] = 0;
		mLabMap->tempImageAfterBlow[(nX * 4 + nY * mLabMap->width * 4) + 1] = 255;
		mLabMap->tempImageAfterBlow[(nX * 4 + nY * mLabMap->width * 4) + 2] = 0;
		mLabMap->tempImageAfterBlow[(nX * 4 + nY * mLabMap->width * 4) + 3] = 0.1;
	}

	lodepng::encode("AStar.png", mLabMap->tempImageAfterBlow, mLabMap->width, mLabMap->height);
}
