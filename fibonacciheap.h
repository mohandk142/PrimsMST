#ifndef FHEAP_H
#define FHEAP_H

#include <vector>
#include "fheapNode.h"
#include <cstdlib>
#include <stdio.h>
#include <string.h>

using namespace std;

class fibonacciheap {

	FHEAPNODE min; //min
	int nodesInHeap; //number of nodes in heap

	std::vector<FHEAPNODE> nodes;
	void link(FHEAPNODE, FHEAPNODE);
	void cascadingCut(FHEAPNODE);
	void cut(FHEAPNODE, FHEAPNODE);
	void consolidate();


public:
	fibonacciheap() :
			min(NULL), nodesInHeap(0) {
	}

	bool isEmpty() {
			return NULL == min;
		}

	int removeMin();

	FHEAPNODE insertNode(int, int);

	~fibonacciheap() {
			if (min)
				delete min;
		}

};

#endif // FHEAP_H
