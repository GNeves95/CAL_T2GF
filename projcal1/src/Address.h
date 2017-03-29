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
	unsigned int cars;
public:
	Address(unsigned int i, float lo, float la, std::string s, unsigned int c);
	Address(float lo, float la, std::string s, unsigned int c);
	virtual ~Address();
	void resetId();
	unsigned int getCars();
	void moveCars(int qt);
};

#endif /* ADDRESS_H_ */
