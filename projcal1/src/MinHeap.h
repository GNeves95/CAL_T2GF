/*
 * MinHeap.h
 *
 *  Created on: Apr 7, 2017
 *      Author: Utilizador
 */

#ifndef MINHEAP_H_
#define MINHEAP_H_

#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>
#include "Address.h"
#include "Graph.h"


//using namespace std;
template <class T> class Vertex;

template <class T>
void Push(std::vector<Vertex<T> *>& heap, Vertex<T> * val);

template <class T>
Vertex<T> * Pop(std::vector<Vertex<T> *>& heap);

template <class T>
void Remove(std::vector<Vertex<T> *>& heap, Vertex<T> * val);



struct greater1 {
	template<class T>
	bool operator()(Vertex<T> *& a, Vertex<T> *& b) {

		return a->getInfo().getMinDist() > b->getInfo().getMinDist();
	}
};
/*
* adiciona um node à heap
*/
template<class T>
void Push(std::vector<Vertex<T> *>& heap, Vertex<T> * val) {
	heap.push_back(val);
	std::push_heap(heap.begin(), heap.end(), greater1());
}

/*
* faz pop do node com a menor minDist
*/
template<class T>
Vertex<T> * Pop(std::vector<Vertex<T> *>& heap) {
	Vertex<Address> * val = heap.front();

	//move o elemento com a menor minDisd para o final do vector
	std::pop_heap(heap.begin(), heap.end(), greater1());

	//remove o ultimo elemento do vector que é o que tem a menor minDist
	heap.pop_back();
	return val;
}

/*
* remove da heap o node val
*/
template<class T>
void Remove(std::vector<Vertex<T> *>& heap, Vertex<T> * val) {
	heap.erase(std::remove(heap.begin(), heap.end(), val), heap.end());

}

#endif /* MINHEAP_H_ */
