/*
 * Robot.h
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include "../Utils/Utils.h"
#include <vector>

using namespace std;
using namespace PlayerCc;



class Robot {

	PlayerClient* _playerClient;
	Position2dProxy* _positionProxy;
	LaserProxy* _laserProxy;
	int X;
	int Y;
	int Yaw;
	double startYaw;


public:
	Robot(char* ip, int port);
	void init(bool bMotors);
	double getX() const;
	double getY() const;
	double getYaw() const;
	double robotStartX;
	double robotStartY;
	double robotStartYaw;
	double robotGoalX;
	double robotGoalY;
	double robotWidth;
	double robotHeight;

	// void getObstacles(vector<Point>& obstacles) const;

	bool canRotate() const;
	bool canMoveForward() const;

	void refresh();
	void setSpeed(double speed, double angularSpeed);
	void Read();
	float getLaserScan(int index);
    void setOdometry();
    void setOdometry(int x, int y, double yaw);
	double getX();
	double getY();
	double getYaw();
	LaserProxy* getLaserProxy();

	virtual ~Robot();
};

#endif /* ROBOT_H_ */
