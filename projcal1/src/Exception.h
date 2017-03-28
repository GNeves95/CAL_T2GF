/*
 * Exception
 *
 *  Created on: Mar 28, 2017
 *      Author: Utilizador
 */

using namespace std;

#ifndef EXCEPTION_
#define EXCEPTION_

#include <exception>


class NegativeNumberCarsException: public exception{
	virtual const char* what()  const throw(){
		return "Negative number of cars in node!\n";
	}
};



#endif /* EXCEPTION_ */
