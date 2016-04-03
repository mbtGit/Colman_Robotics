#ifndef NODE_H_
#define NODE_H_

class Node {
public:
	int x;
	int y;
	int GValue;
	int HValue;
	int FValue;


	Node *parentNode;

	Node(int x, int y, Node *parent);
	virtual ~Node();

	int getGValue();
	int calcGValue(Node *parent);
	int getHValue();
	int calcHValue(Node *end);
	int getFValue();
	void calculateNode(Node *end);
	void setParent(Node *nParentNode);
	bool isEqual(Node *nOtherNode);
};

#endif
