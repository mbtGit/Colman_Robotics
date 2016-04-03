/*
 * Utils.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: colman
 */

#include "Utils.h"


int Utils::DegreesToIndex(int degrees)
{
	int index = degrees * Utils::DEGREES_INDEX_RATIO;
	return Utils::MIDDLE_INDEX + index;
}

int Utils::IndexToDegrees(int index)
{
	int realIndex = index - Utils::MIDDLE_INDEX;
	return realIndex / Utils::DEGREES_INDEX_RATIO;
}

double Utils::IndexToRadians(int index)
{
	int degrees = IndexToDegrees(index);
	return degrees * PI / 180;
}

int Utils::RadiansToIndex(double radians)
{
	int degrees = radians * 180 / PI;
	return DegreesToIndex(degrees);
}

double Utils::DegreeToRadian(double degree){
	 return ((degree) * (M_PI / 180.0));
}

double Utils::RadianToDegree(double radian){
	 return ((radian) * (180.0 / M_PI));
}

double Utils::MeterToPixel(double meter){
	 return (0);
}

double Utils::PixelToMeter(double pixel){
	 return (0);
}
