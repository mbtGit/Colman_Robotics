#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "../Framework/Robot.h"
#include "../Utils/Utils.h"
#include <vector> 

using namespace std;

class Behavior {
private:
    vector<Behavior *> _nextBehaviors;

protected:
    Robot* _robot;

public:
    Behavior(Robot* robot);
    virtual bool startCond() = 0;
    virtual bool stopCond() = 0;
    virtual void action() = 0;

    Behavior *addNext(Behavior *beh);
    Behavior *selectNext();

	bool checkObstacleInFront(int nCheckDirectionIndicator);
	int nSideIndexShouldTernNow;
	string strBehaviorName;
};

#endif /* BEHAVIOR_H_ */
