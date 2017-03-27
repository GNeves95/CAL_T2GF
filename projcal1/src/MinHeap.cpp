/*
* MinHeap.cpp
*
*  Created on: 19/04/2015
*      Author: Ricardo
*/

#include "MinHeap.h"

struct greater1 {
	bool operator()(Nodes<Hotspot> *& a, Nodes<Hotspot> *& b) {

		return a->getInfo().getMinDist() > b->getInfo().getMinDist();
	}
};

/*
* adiciona um node à heap
*/
void Push(vector<Nodes<Hotspot> *>& heap, Nodes<Hotspot> * val) {
	heap.push_back(val);
	push_heap(heap.begin(), heap.end(), greater1());
}

/*
* faz pop do node com a menor minDist
*/
Nodes<Hotspot> * Pop(vector<Nodes<Hotspot> *>& heap) {
	Nodes<Hotspot> * val = heap.front();

	//move o elemento com a menor minDisd para o final do vector
	pop_heap(heap.begin(), heap.end(), greater1());

	//remove o ultimo elemento do vector que é o que tem a menor minDist
	heap.pop_back();
	return val;
}

/*
* remove da heap o node val
*/
void Remove(vector<Nodes<Hotspot> *>& heap, Nodes<Hotspot> * val) {
	heap.erase(std::remove(heap.begin(), heap.end(), val), heap.end());

}