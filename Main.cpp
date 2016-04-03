#include <libplayerc++/playerc++.h>
#include <iostream>
#include "Framework/Robot.h"
#include "Map/Map.h"
#include "Way/AStar.h"
#include "Framework/Manager.h"
#include "Utils/ConfigurationManager.h"


using namespace PlayerCc;
using namespace std;


#define LASER_SAMPLES 666
#define MIN_ANGLE_FOR_AVOIDANCE -45
#define MAX_ANGLE_FOR_AVOIDANCE 45
#define MAX_DIST_TO_OBSTACLE 0.6
#define MAX_DIST_OF_LASER_SENSOR 4


int main()
{
	// Robotic project
	Robot* myRobot = new Robot("localhost", 6665);
	Manager* mManager = new Manager(myRobot);
	mManager->Run();
}





