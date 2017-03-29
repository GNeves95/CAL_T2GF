/*
 * Address.cpp
 *
 *  Created on: 27/03/2017
 *      Author: up201306485
 */

#include "Address.h"
#include "Exception.h"

using namespace std;

unsigned int Address::id = 0;

Address::Address(unsigned int i, float lo, float la, string s, unsigned int c){
	// TODO Auto-generated constructor stub
	if(i >= id) id = i;
	thisId = i;
	longitude = lo;
	latitude = la;
	addr = s;
	cars = c;
}

Address::Address(float lo, float la, string s, unsigned int c) {
	thisId = ++id;
	longitude = lo;
	latitude = la;
	addr = s;
	cars = c;
}

Address::~Address() {
	// TODO Auto-generated destructor stub
}

void Address::resetId() {
	id = 0;
}

unsigned int Address::getCars() {
	return cars;
}

void Address::moveCars(int qt) {
	if((cars + qt) >= 0)	cars += qt;
	else throw NegativeNumberCarsException();
}
