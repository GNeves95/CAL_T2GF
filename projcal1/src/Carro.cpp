/*
 * Carro.cpp
 *
 *  Created on: 03/04/2017
 *      Author: up201306485
 */

#include "Carro.h"

using namespace std;

Carro::Carro() {
	// TODO Auto-generated constructor stub
	dest = 0;

}

Carro::~Carro() {
	// TODO Auto-generated destructor stub
}

void Carro::setDest(Address* d) {
	dest = d;
}
