/*
* MinHeap.h
*
*  Created on: 19/04/2015
*      Author: Ricardo
*/

#ifndef MINHEAP_H_
#define MINHEAP_H_

#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>
#include "Hotspot.h"
#include "nodes.h"


using namespace std;

void Push(vector<Nodes<Hotspot> *>& heap, Nodes<Hotspot> * val);
Nodes<Hotspot> * Pop(vector<Nodes<Hotspot> *>& heap);
void Remove(vector<Nodes<Hotspot> *>& heap, Nodes<Hotspot> * val);

#endif /* MINHEAP_H_ */