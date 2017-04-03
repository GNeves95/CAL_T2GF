/*
 * Address.h
 *
 *  Created on: 27/03/2017
 *      Author: up201306485
 */


#include <string>

//using namespace std;

#ifndef ADDRESS_H_
#define ADDRESS_H_

class Address {
	static unsigned int id;
	unsigned int thisId;
	float longitude, latitude;
	std::string addr;
	std::vector<Carro*> cars;
	//unsigned int cars;
public:
	Address(unsigned int i, float lo, float la, std::string s);
	Address(float lo, float la, std::string s);
	virtual ~Address();
	void resetId();
	std::vector<Carro*> getCars();
	unsigned int getNumCars();
	void moveCars(int qt, Address *dest);
};

#endif /* ADDRESS_H_ */
