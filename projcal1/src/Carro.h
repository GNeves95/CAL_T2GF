/*
 * Carro.h
 *
 *  Created on: 03/04/2017
 *      Author: up201306485
 */

#include "Address.h"
#include "Links.h"

#ifndef CARRO_H_
#define CARRO_H_

class Carro {
	Address *dest;
	std::vector<Links *> path;
public:
	Carro();
	virtual ~Carro();
	void setDest(Address *d);
};

#endif /* CARRO_H_ */
