/*
 * Address.cpp
 *
 *  Created on: 27/03/2017
 *      Author: up201306485
 */

#include "Address.h"

Address::Address(int i, float lo, float la, string s): id(i), longitude(lo), latitude(la), addr(s) {
	// TODO Auto-generated constructor stub

}

Address::Address(float lo, float la, string s): longitude(lo), latitude(la), addr(s) {
	thisId = ++id;
}

Address::~Address() {
	// TODO Auto-generated destructor stub
}

