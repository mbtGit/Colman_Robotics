/*
 * Robot.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#include "Robot.h"



Robot::Robot(char* ip, int port)
{
	/*_playerClient = new PlayerClient(ip, port);
	_positionProxy = new Position2dProxy(_playerClient);
	_laserProxy = new LaserProxy(_playerClient);
	_laser = new Laser(*_laserProxy, *this);*/
	// _map = new Map(MAP_ROWS, MAP_COLUMNS, MAP_RESOLUTION);

//	init();
}

void Robot::init(bool bMotors)
{
	startYaw = Utils::DegreeToRadian(robotStartYaw);

	// Connect to the emulator
	_playerClient = new PlayerClient("127.0.0.1",6665);

	// Init poistion proxy
	_positionProxy = new Position2dProxy(_playerClient);

	// Init laser proxy
	_laserProxy = new LaserProxy(_playerClient);

	_positionProxy->SetMotorEnable(bMotors);

	for(int read=0; read<15; read++){
		_playerClient->Read();
	}

	// Init robot yaw and odometry
	_positionProxy->SetOdometry(0,0,startYaw);
}

Robot::~Robot()
{
	delete _positionProxy;
	delete _laserProxy;
	delete _playerClient;
}



/* void Robot::getObstacles(vector<Point>& obstacles) const
{
	_laser->getObstacles(LASER_OBSTACLE_DISTANCE, obstacles);
}

bool Robot::canRotate() const
{
	return _laser->canRotate();
}

bool Robot::canMoveForward() const
{
	return _laser->canMoveForward();
}
*/




void Robot::Read()
{
	_playerClient->Read();
}

void Robot::refresh()
{
	// Refresh Sensors buffers
	_playerClient->Read();

	// Handle new Obstacles
	// vector<Point> obstacles;
	// getObstacles(obstacles);

	// map.handleObstacles(*this, obstacles);
	// cout << map << endl;
}

void Robot::setSpeed(double speed, double angularSpeed)
{
	_positionProxy->SetSpeed(speed,angularSpeed);
}

float Robot::getLaserScan(int index){
	return _laserProxy->GetRange(index);
}

void Robot::setOdometry()
{
	_positionProxy->SetOdometry(0,0,startYaw);
}

void Robot::setOdometry(int x, int y, double yaw)
{
	int newX = Utils::PixelToMeter(x - robotStartX);
	int newY = Utils::PixelToMeter(y - robotStartY);


	double radianYaw = Utils::DegreeToRadian(yaw);

	_positionProxy->SetOdometry(newX, newY,radianYaw);
}

double Robot::getX()
{
	return robotStartX + Utils::MeterToPixel(_positionProxy->GetXPos());
}

double Robot::getY()
{
	return robotStartY - Utils::MeterToPixel(_positionProxy->GetYPos());
}

double Robot::getYaw()
{
	double degree = Utils::RadianToDegree(_positionProxy->GetYaw());
	if (degree < 0)
		degree = 360 + degree;

	return degree;
}

LaserProxy* Robot::getLaserProxy()
{
	return _laserProxy;
}
