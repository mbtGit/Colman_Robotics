/*
 * HandleConfig.h
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#ifndef HANDLECONFIG_H_
#define HANDLECONFIG_H_

#include "../Map/Map.h"

class ConfigurationManager{
public:
	ConfigurationManager();
};

void GetConfig(Robot* myRobot, Map* myMap);
std::vector<std::string> Split(std::string s, char delimiter);
std::string RemoveSurroundingSpaceCharacters(std::string s);




#endif /* HANDLECONFIG_H_ */
