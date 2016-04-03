/*
 * HandleConfig.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "ConfigurationManager.h"

void GetConfig(Robot* myRobot, Map* myMap)
{
	std::ifstream infile("parameters.txt");
	string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		if (line.find("map", 0) != string::npos){
			 myMap->mapName = Split(line, ':')[1];
		}
		else if (line.find("startLocation", 0) != string::npos){
			string StartLocation = Split(line, ':')[1];
			vector<string> XYZLocations = Split(StartLocation, ' ');
			myRobot->robotStartX = atof(XYZLocations[0].c_str());
			myRobot->robotStartY = atof(XYZLocations[1].c_str());
			myRobot->robotStartYaw = atof(XYZLocations[2].c_str());
		}
		else if (line.find("goal", 0) != string::npos){
			string Goal = Split(line, ':')[1];
			vector<string> GoalXY = Split(Goal, ' ');
			myRobot->robotGoalX = atof(GoalXY[0].c_str());
			myRobot->robotGoalY = atof(GoalXY[1].c_str());
		}
		else if (line.find("robotSize", 0) != string::npos){
			string RobotSize = Split(line, ':')[1];
			vector<string> RobotWidthHeight = Split(RobotSize, ' ');
			myRobot->robotWidth = atof(RobotWidthHeight[0].c_str());
			myRobot->robotHeight = atof(RobotWidthHeight[1].c_str());
		}
		else if (line.find("MapResolutionCM", 0) != string::npos){
			string MapResolution = Split(line, ':')[1];
			myMap->SetMapResolution(atof(MapResolution.c_str()));
		}
		else if (line.find("GridResolutionCM", 0) != string::npos){
			string GridResolution = Split(line, ':')[1];
			myMap->SetGridResolution(atof(GridResolution.c_str()));
		}

	}
}

vector<string> Split(string s, char delimiter) {
	vector<string> splittedString;
	size_t pos = 0;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		splittedString.push_back(RemoveSurroundingSpaceCharacters(s.substr(0, pos)));
		s.erase(0, pos + 1);
	}

	splittedString.push_back(RemoveSurroundingSpaceCharacters(s));

	return splittedString;
}

string RemoveSurroundingSpaceCharacters(string s) {
	while (s.find_first_of(" ") == 0) {
		s = s.substr(1, s.length() + 1);
	}

	while (s.find_first_of(" ") == s.length() - 1) {
		s = s.substr(0, s.length());
	}

	return s;
}

ConfigurationManager::ConfigurationManager()
{

}





