/*
 * Carro.h
 *
 *  Created on: 03/04/2017
 *      Author: up201306485
 */


#ifndef CARRO_H_
#define CARRO_H_


#include <vector>
#include "Address.h"
#include "Graph.h"

class Address;

class Carro {
	Address *dest;
	std::vector<Vertex<Address> *> path;
public:
	Carro();
	virtual ~Carro();
	void setDest(Address *d);
};

#endif /* CARRO_H_ */
