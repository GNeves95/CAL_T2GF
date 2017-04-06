/*
 * Address.cpp
 *
 *  Created on: 27/03/2017
 *      Author: up201306485
 */
#include <vector>
#include <string>
#include <sstream>
#include "Address.h"
#include "Exception.h"
//#include "Carro.h"

using namespace std;

unsigned int Address::id { 0 };

Address::Address(unsigned int i, float lo, float la, string s){
	// TODO Auto-generated constructor stub
	if(i >= id) id = i;
	thisId = i;
	longitude = lo;
	latitude = la;
	addr = s;
	minDist = 0;
}

Address::Address(float lo, float la, string s) {
	thisId = ++id;
	longitude = lo;
	latitude = la;
	addr = s;
	minDist = 0;
}


Address::~Address() {
	// TODO Auto-generated destructor stub
}

void Address::resetId() {
	id = 0;
}

/*vector<Carro*> Address::getCars() {
	return cars;
}*/

void Address::moveCars(int qt, Address *dest) {
	if((cars.size() - qt) >= 0){
		for(int i = 0; i < qt; i++){
			//cars.at(i)->setDest(dest);
		}
	}
	else throw NegativeNumberCarsException();
}

unsigned int Address::getNumCars() {
	return cars.size();
}

void Address::resetCars() {
	for(unsigned int i=0; i < cars.size(); i++){
		//cars.at(i)->setDest(this);
	}
}

unsigned int Address::getId() {
	return thisId;
}

float Address::getLongitude() {
	return longitude;
}

float Address::getLatitude() {
	return latitude;
}

std::string Address::getNome() {
	return addr;
}

void Address::setLongitude(float lo) {
	longitude = lo;
}

void Address::setLatitude(float la) {
	latitude = la;
}

void Address::setNome(std::string n) {
	addr = n;
}

bool Address::operator ==(const Address& a2) const {
	if(this->addr == a2.addr && this->latitude == a2.latitude && this->longitude == a2.longitude) return true;
	return false;
}

std::string Address::fileFormat() {
	stringstream ss { } ;
	ss << thisId << ";" << longitude << ";" << latitude << ";" << addr;
	return ss.str();
}

double Address::getMinDist(){
	return this->minDist;
}

void Address::setMinDist(double minDist){
	this->minDist = minDist;
}

ostream & operator << (ostream &os, Address n){
	os << n.getNome();
	return os;
}
