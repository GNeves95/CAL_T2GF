/*
 * Address.h
 *
 *  Created on: 27/03/2017
 *      Author: up201306485
 */




//using namespace std;

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>
#include <vector>
//#include "Carro.h"

class Carro;

class Address {
	static unsigned int id;
	unsigned int thisId;
	float longitude, latitude;
	std::string addr;
	std::vector<int> cars;
	//std::vector<Carro* > cars;
	//unsigned int cars;
public:
	Address(unsigned int i, float lo, float la, std::string s);
	Address(float lo, float la, std::string s);
	virtual ~Address();
	void resetId();
	//std::vector<Carro*> getCars();
	unsigned int getNumCars();
	void moveCars(int qt, Address *dest);
	void resetCars();
	std::string getMinDist();
	friend std::ostream & operator << (std::ostream &os, Address p);
};

#endif /* ADDRESS_H_ */
