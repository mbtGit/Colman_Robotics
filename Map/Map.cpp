/*
 * Map.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#include "Map.h"
#include "../Framework/Robot.h"
Map::Map(){

}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

void Map::LoadMapFromPng()
{
  std::vector<unsigned char> png;
  int x,y;
   //the raw pixels

  // Load the Map from the png
  lodepng::load_file(png, "Simulation/roboticLabMap.png");//this->mapName);

  // Decode it and check if there are errors
  unsigned error = lodepng::decode(navImage, width, height, png);

  // Print the error message if exists
  if(error)
	  std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

int Map::CheckIfCellOccupiedInPng(int nRow, int nCol)
{
	int nCellsInGrid = GetGridMapFinalResolution();
	nRow *= nCellsInGrid;
	nCol *= nCellsInGrid;
	int nFreeCounter = 0;

	for (int nRowOffset = 0; nRowOffset < nCellsInGrid; nRowOffset++)
	{
		for (int nColOffset = 0; nColOffset < nCellsInGrid; nColOffset++)
		{
			if (ConvertArrPosToMatrixPos(nRow + nRowOffset, nCol + nColOffset) == 255)
			{
				nFreeCounter++;
			}
			else
			{
				nFreeCounter = nFreeCounter + 0;
			}
		}
	}

	// If we found less then two
	if (nFreeCounter < 16){
		return OCCUPIED;
	}
	else
	{
		return FREE;
	}
}

int Map::ConvertArrPosToMatrixPos(int nRow, int nCol)
{
	return (tempImageAfterBlow[nRow * width * 4 + nCol * 4]);
}

void Map::InsertMapToMatrix()
{
	// Callculate how many cells in the first array is one cell in the final grid
	int nPixelInGridRatio = GetGridMapFinalResolution();

	// Finds the size of the grid
	int nGridHeight = height / nPixelInGridRatio;
	int nGridWidth = width / nPixelInGridRatio;

	// Resizing the grid vector
	MapMatrix.resize(nGridHeight);

	for (int i=0; i < nGridHeight; i++)
	{
	  // Because we are using 2 dimensional vector, We need to resize all of the cells
	  MapMatrix[i].resize(nGridWidth);
	}

	int x,y;
	CELL_TYPE myCell;

	for (x = 0; x < nGridHeight; x++)
	{
		for (y = 0; y < nGridWidth; y++)
		{
			// shtut
			myCell = (CELL_TYPE)CheckIfCellOccupiedInPng(x, y);
			MapMatrix[x][y] = myCell;
		}
	}
}

std::vector<unsigned char> Map::GetUnsignedCharMatrix()
{
	std::vector<unsigned char> mUnsignedMapMatrix;

	for (int nIndex = 0; nIndex < height * width; nIndex++)
	{
	  int myRowIndexer = floor(nIndex / width);
	  int myColIndexer = (nIndex) % width;

	  switch (MapMatrix[myRowIndexer][myColIndexer])
	  {
	  	  case OCCUPIED:
	  	  {
	  		  mUnsignedMapMatrix[nIndex] = '#';
		  	  break;
	  	  }
	  	  case FREE:
	  	  {
	  		  mUnsignedMapMatrix[nIndex] = ' ';
	  		  break;
	  	  }
	  }
	}

	return (mUnsignedMapMatrix);
}

void Map::MapWeighting(Robot* myRobot, double Scale)
{
	tempImageAfterBlow.resize(navImage.size());

	for (int i = 0; i < navImage.size(); i++){
		tempImageAfterBlow[i] = navImage[i];
	}

	// Go through the navImage and expand each black pixel found
	for (int nRow=0; nRow < height; nRow++)
	{
		for (int nCol=0; nCol < width; nCol++){
			// If the cell is black we need to weight it.
			if ((navImage[nRow * width * 4 + nCol * 4] == 0) &
					(navImage[nRow * width * 4 + nCol * 4 + 1] == 0) &
					(navImage[nRow *  width * 4 + nCol * 4 + 2] == 0))
			{
//				int startIndicator = i - (width * myRobot->robotWidth * 4) - (myRobot->robotWidth * 4);
//				int endIndicator = i + (width * myRobot->robotWidth * 4) + (myRobot->robotWidth * 4);
				WeightCell(nRow, nCol, Scale);
			}
		}
	}
}
void Map::WeightCell(int nRow, int nCol, double Scale)
{
	for (int nRowWeighter = nRow - Scale; nRowWeighter < nRow + Scale; nRowWeighter++ ){
		for (int nColWeighter = nCol - Scale; nColWeighter < nCol + Scale; nColWeighter++){
			// Check to see that we are not exceeding the size of the image.
			if (nRowWeighter >= 0 &
					nColWeighter >= 0 &
					nRowWeighter <= height * 4 &
					nColWeighter <= width * 4){
				tempImageAfterBlow[nRowWeighter * width * 4 + nColWeighter * 4] = 0;
				tempImageAfterBlow[nRowWeighter * width * 4 + nColWeighter * 4 + 1] = 0;
				tempImageAfterBlow[nRowWeighter * width * 4 + nColWeighter * 4 + 2] = 0;
				tempImageAfterBlow[nRowWeighter * width * 4 + nColWeighter * 4 + 3] = 255;
			}
		}
	}
}

double Map::GetMapResolution()
{
	return this->MapResolution;
}
double Map::GetGridResolution()
{
	return this->GridResolution;
}
void Map::SetGridResolution(double gridResolution)
{
	this->GridResolution = gridResolution;
}
void Map::SetMapResolution(double mapResolution)
{
	this->MapResolution = mapResolution;
}
bool Map::IsCellFree(int x, int y)
{
	if (MapMatrix[y][x] == OCCUPIED)
	{
		return false;
	}

	return true;
}

double Map::GetGridMapFinalResolution(){
	return (GetGridResolution() / GetMapResolution());
}

