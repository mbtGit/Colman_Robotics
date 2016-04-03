#include "../Way/AStar.h"
#include <iostream>

using namespace std;


AStar::AStar() {
	// TODO Auto-generated constructor stub

}

std::list<Node*> AStar::AStarPath (int nXSourceGrid, int nYSourceGrid, int nXDestnGrid, int nYDestGrid, Map *map)
{
	std::list<Node*> openList;
	std::list<Node*> closedList;
	std::map<Node*, Node*> nSourceNodes;

	bool bStuck	    = map->IsCellFree(nXSourceGrid,nYSourceGrid);
	bool bStuck2    = map->IsCellFree(nXDestnGrid,nYDestGrid);

	Node *nStart 	= new Node(nXSourceGrid, nYSourceGrid, NULL);
	Node *nEnd 		= new Node(nXDestnGrid, nYDestGrid, NULL);
	Node *nCurrnt 	= new Node(-1, -1, NULL);

	nStart->calculateNode(nEnd);

	openList.push_back(nStart);
	int n = openList.size();
	while (!nCurrnt->isEqual(nEnd))
	{
		// Search for point with the smallest F score in the open list
		for (std::list<Node*>::iterator listIterator = openList.begin(); listIterator != openList.end() ;listIterator++)
		{
			if ((listIterator == openList.begin()) || (*listIterator)->getFValue() < nCurrnt->getFValue())
			{
				nCurrnt = *listIterator;
			}
		}

		// Stop if we reached the end
		if (nCurrnt->isEqual(nEnd))
		{
			break;
		}

		// Remove the current point from the open list
		openList.remove(nCurrnt);

		// Add the current point to the closed list
		closedList.push_back(nCurrnt);

		// Scan all the adjacent points of the current point
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				// If its the current point - then pass
				if (i == 0 && j == 0)
					continue;

				// If we are in a corner - then pass (we don't move in diagonal)
				//if (i != 0 && j != 0)
				//	continue;

				// calculate x & adjacentY of adjacent point
				int adjacentX = nCurrnt->x + j;
				int adjacentY = nCurrnt->y + i;

				// Check if this point is in the closed list
				bool isPointInClosedList = false;
				for (std::list<Node*>::iterator listIterator = closedList.begin(); listIterator != closedList.end(); listIterator++)
				{
					if ((*listIterator)->x == adjacentX && (*listIterator)->y == adjacentY)
					{
						isPointInClosedList = true;
						break;
					}
				}

				// If this point is in the closed list - continue
				if (!isPointInClosedList)
				{
					// Check if this point is in the open list
					bool isPointInOpenedList = false;
					for (std::list<Node*>::iterator listIterator = openList.begin(); listIterator != openList.end(); listIterator++)
					{
						if ((*listIterator)->x == adjacentX && (*listIterator)->y == adjacentY)
						{
							isPointInOpenedList = true;
							break;
						}
					}

					// Check if cell is free and not in open list for the robot
					if ((!isPointInOpenedList) && (map->IsCellFree(adjacentX, adjacentY)))
					{
						Node *thisPoint = new Node(adjacentX, adjacentY, nCurrnt);
						thisPoint->calculateNode(nEnd);
						openList.push_back(thisPoint);

						nSourceNodes[thisPoint] = nCurrnt;
					}
				}
			}
		}
	}

	std::list<Node*> lstPath;
	Node *pathCurrent = nCurrnt;
	lstPath.push_back(nCurrnt);

	while (!pathCurrent->isEqual(nStart))
	{
		pathCurrent = nSourceNodes[pathCurrent];
		lstPath.push_back(pathCurrent);
	}

	return lstPath;
}

AStar::~AStar() {
	// TODO Auto-generated destructor stub
}
