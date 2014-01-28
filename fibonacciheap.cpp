#include "fibonacciheap.h"
#include <iostream>
#include <cmath>

using namespace std;

void fibonacciheap::link(FHEAPNODE y, FHEAPNODE x) {
	if (!x || !y)
		return;
	y->removefheapNode();
	x->insertChild(y);
}


void fibonacciheap::cut(FHEAPNODE x, FHEAPNODE y) {
	x->removefheapNode();
	y->degree--;
	min->insertfheapNode(x);
	x->parent = NULL;
	x->checkNode = false;
}

void fibonacciheap::cascadingCut(FHEAPNODE y) {
	FHEAPNODE z = y->parent;
	if (z) {
		if (y->checkNode) {
			cut(y, z);
			cascadingCut(z);
		} else {
			y->checkNode = true;
		}
	}
}

/**
 * Consolidates node chain of the root
 */
void fibonacciheap::consolidate() {
	//+1 for ceiling log_2, +1 for null terminated
	const std::size_t sz = log2(this->nodesInHeap) + 2;
	FHEAPNODE A[sz];
	memset(A, 0x0, sz * sizeof(FHEAPNODE));
	FHEAPNODE w = min->rightSibling;
	bool finished = false;
	do {
		if (w == min)
			finished = true;
		FHEAPNODE x = w;
		w = w->rightSibling;
		unsigned d = x->degree;
		while (A[d]) {
			FHEAPNODE y = A[d];
			if (x->edgeCost > y->edgeCost) {
				swap(x, y);
			}
			this->link(y, x);
			A[d] = NULL;
			d++;
		}
		A[d] = x;
	} while (!finished);

	min = NULL;
	for (std::size_t i = 0; i < sz; i++) {
		if (A[i]) {
			if (NULL == min) {
				min = A[i];
				min->leftSibling = min;
				min->rightSibling = min;
			} else {
				min->insertfheapNode(A[i]);
				if (A[i]->edgeCost < min->edgeCost)
					min = A[i];
			}
		}
	}
}

/**
 * Inserts a new node into the heap
 *
 *  int x is the destination vertex
 *  int k is the cost associated with the edge
 *
 */

FHEAPNODE fibonacciheap::insertNode(int x, int k) {
	if (nodes.size() <= k) {
		nodes.resize(k + 1, NULL);
	}
	FHEAPNODE ptr = new fheapNode(x, k);
	if (min) {
		min->insertfheapNode(ptr);
		if (k < min->edgeCost) {
			min = ptr;
		}
	} else {
		min = ptr;
	}
	nodes[k] = ptr;
	nodesInHeap++;
	return ptr;
}

/**
 * Extract the node of minimum edgeCost
 *
 * returns {int} data
 */
int fibonacciheap::removeMin() {
	if (this->isEmpty()) {
		return -1;
	}
	int data = min->dstVertex;
	int edgeCost = min->edgeCost;

	if (min->child) {
		FHEAPNODE ptr = min->child;
		do {
			ptr->parent = NULL;
			ptr = ptr->leftSibling;
		} while (ptr != min->child);
		min->child = NULL;
		min->mergefheapNodes(ptr);
	}

	FHEAPNODE ptr = min;
	nodes[edgeCost] = NULL;

	if (min->rightSibling == min) {
		//If there is only one node left inside the heap
		delete min;
		min = NULL;
	} else {
		//We isolate the (current) fmin, then delete it
		min = min->rightSibling;
		ptr->removefheapNode();
		delete ptr;
		this->consolidate();
	}
	nodesInHeap--;
	return data;
}




