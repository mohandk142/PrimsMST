#include "fheapNode.h"
#include <cstdlib>
#ifndef NULL
#define NULL   ((void *) 0)
#endif
using namespace std;

void nodeSwap(FHEAPNODE& a, FHEAPNODE& b) {
	FHEAPNODE c = a;
	a = b;
	b = c;
}

fheapNode::fheapNode(int dstVertex, int k) :
		dstVertex(dstVertex), edgeCost(k), parent(NULL), child(NULL), leftSibling(
				this), rightSibling(this), checkNode(false), degree(0) {
}

void fheapNode::removefheapNode() {
	if (parent)
		parent->child = parent->child->rightSibling;
	this->leftSibling->rightSibling = this->rightSibling;
	this->rightSibling->leftSibling = this->leftSibling;
	this->leftSibling = this->rightSibling = this;
}

void fheapNode::mergefheapNodes(fheapNode *f) {
	nodeSwap(f->rightSibling->leftSibling, this->rightSibling->leftSibling);
	nodeSwap(f->rightSibling, this->rightSibling);
}


void fheapNode::insertfheapNode(fheapNode *f) {
	f->leftSibling = this->leftSibling;
	f->rightSibling = this;
	this->leftSibling->rightSibling = f;
	this->leftSibling = f;
}

void fheapNode::insertChild(fheapNode *f) {
	if (child)
		child->insertfheapNode(f);
	else
		child = f;
	f->parent = this;
	f->checkNode = false;
	degree++;
}

fheapNode::~fheapNode() {
	if (parent)
		parent->child = NULL;
	if (rightSibling)
		this->rightSibling->leftSibling = NULL;
	if (leftSibling && leftSibling != this)
		delete leftSibling;
	if (child)
		delete child;
}

