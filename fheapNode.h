#ifndef FHEAPNODE_H
#define FHEAPNODE_H

struct fheapNode {
	int dstVertex;
	int edgeCost;
	fheapNode *parent, *child, *leftSibling, *rightSibling;
	bool checkNode;
	unsigned degree;

	fheapNode(int dstVertex, int edgeCost);

	void removefheapNode();
	void mergefheapNodes(fheapNode *f);
	void insertfheapNode(fheapNode *f);
	void insertChild(fheapNode *f);

	~fheapNode();
};
typedef fheapNode* FHEAPNODE;
void nodeSwap(FHEAPNODE&, FHEAPNODE&);
#endif
