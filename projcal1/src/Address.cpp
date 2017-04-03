/*
 * Address.cpp
 *
 *  Created on: 27/03/2017
 *      Author: up201306485
 */

#include "Address.h"
#include "Exception.h"
#include "Carro.h"

using namespace std;

unsigned int Address::id = 0;

Address::Address(unsigned int i, float lo, float la, string s){
	// TODO Auto-generated constructor stub
	if(i >= id) id = i;
	thisId = i;
	longitude = lo;
	latitude = la;
	addr = s;
}

Address::Address(float lo, float la, string s) {
	thisId = ++id;
	longitude = lo;
	latitude = la;
	addr = s;
}

Address::~Address() {
	// TODO Auto-generated destructor stub
}

void Address::resetId() {
	id = 0;
}

vector<Carro*> Address::getCars() {
	return cars;
}

void Address::moveCars(int qt, Address *dest) {
	if((cars.size() - qt) >= 0){
		for(unsigned int i = 0; i < qt; i++){
			cars.at(i)->setDest(dest);
		}
	}
	else throw NegativeNumberCarsException();
}

unsigned int Address::getNumCars() {
	return cars.size();
}
