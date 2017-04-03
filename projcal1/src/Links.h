

//using namespace std;

#ifndef _LINKS_H_
#define _LINKS_H_

#include <vector>
#include <iostream>
#include <fstream>
#include "nodes.h"

template <class T> class Nodes;

template <class T>
class Links {
	Nodes<T> * dest;
	double weight;
	Nodes<T> * origem;
	unsigned int maxCars;
public:
	Links(Nodes<T> *d, double w, unsigned int mc);
	double getWeight();
	Nodes<T> * getDest();
	Nodes<T> * getOrigem();
	void setOrigem(Nodes<T> * neworig);
	void setDest(Nodes<T> * newdest);
	friend class Nodes<T>;
};

template<class T>
Nodes<T> * Links<T>::getDest(){
	return this->dest;
}

template<class T>
void Links<T>::setDest(Nodes<T> * newdest){
	this->dest = newdest;
}

template<class T>
Nodes<T> * Links<T>::getOrigem(){
	return this->origem;
}

template<class T>
void Links<T>::setOrigem(Nodes<T> * neworigem){

	this->origem = neworigem;
}

template <class T>
Links<T>::Links(Nodes<T> *d, double w, unsigned int mc) : dest(d){
	weight = w;
	origem = 0;
	maxCars = mc;
}

template <class T>
double Links<T>::getWeight(){
	return weight;
}



#endif
