/*
 * Address.h
 *
 *  Created on: 27/03/2017
 *      Author: up201306485
 */

using namespace std;

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>

class Address {
	string addr;
	static int id;
	const int thisId;
	float longitude, latitude;
public:
	Address(int i, float lo, float la, string s);
	Address(float lo, float la, string s);
	virtual ~Address();
};

#endif /* ADDRESS_H_ */
