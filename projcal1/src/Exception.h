/*
 * Exception
 *
 *  Created on: Mar 28, 2017
 *      Author: Utilizador
 */

#include <exception>

#ifndef EXCEPTION_
#define EXCEPTION_



class NegativeNumberCarsException: public std::exception{
	virtual const char* what()  const throw(){
		return "Negative number of cars in node!\n";
	}
};



#endif /* EXCEPTION_ */
