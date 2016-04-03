/*
 * Manager.h
 *
 *  Created on: Jun 19, 2015
 *      Author: colman
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "../Behaviors/MoveToWaypoint.h"
#include "../Behaviors/Behavior.h"
#include "../Behaviors/MoveForward.h"
#include "../Behaviors/TurnLeft.h"
#include "../Behaviors/TurnRight.h"
#include "../Utils/ConfigurationManager.h"
#include "../Map/Map.h"
#include "../Way/AStar.h"
class Manager {
private:
    Robot *robot;
    Behavior *currBehavior;
    std::list<Node*> lstWaypointsToDestination;
    Map* mLabMap;

public:

    Manager(Robot *robot);
    ~Manager();
    void UpdateRobot();
    bool isInWaypointRange(Node* nWaypoint);
    void PrintToConsole(int nStartX,int nStartY,int nWantedLocationX,int nWantedLocationY);
    void PrintToPng(int nStartX,int nStartY,int nWantedLocationX,int nWantedLocationY);
    void Run();
};

#endif /* MANAGER_H_ */
