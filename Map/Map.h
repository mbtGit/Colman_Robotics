/*
 * Map.h
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_
#include "../Utils/lodepng.h"
#include "../Framework/Robot.h"
#include <iostream>
#include <cmath>
#include <string>

class Map {
private:


	const int PIXELS_PER_CELL = 4;
	double MapResolution;
	double GridResolution;

public:
	std::vector<unsigned char> navImage;
	std::vector<unsigned char> tempImageAfterBlow;

	Map();
	~Map();

	enum CELL_TYPE 							{FREE, OCCUPIED};
	std::vector< std::vector<CELL_TYPE> > 	MapMatrix;
	unsigned int							width, height;
	string 									mapName;

	void 						LoadMapFromPng();
	void 						InsertMapToMatrix();
	std::vector<unsigned char> 	GetUnsignedCharMatrix();
	void 						MapWeighting(Robot* myRobot, double Scale);
	double 						GetMapResolution();
	double 						GetGridResolution();
	void						SetGridResolution(double gridResolution);
	void 						SetMapResolution(double mapResolution);
	bool 						IsCellFree(int x, int y);
	double						GetGridMapFinalResolution();
	void						WeightCell(int nRow, int nCol, double Scale);
	int 						CheckIfCellOccupiedInPng(int nRow, int nCol);
	int 						ConvertArrPosToMatrixPos(int nRow, int nCol);
};

#endif /* MAP_H_ */
