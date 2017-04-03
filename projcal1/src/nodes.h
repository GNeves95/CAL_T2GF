#include <string>
#include <vector>
#include "Links.h"

//using namespace std;

#ifndef _NODES_H_
#define _NODES_H_


template <class T> class Links;

template <class T>
class Nodes {
	T info;
	std::vector<Links<T>  > adj;
	Nodes<T> * previous;
	bool visited, linked, processing;
	double dist;
	int indegree;
public:
	Nodes(T in);
	T getInfo();
	void setInfo(T info);
	bool getLinked();

	bool getProcessing();
	void setProcessing(bool t);

	std::vector<Links<T>	> getAdj();
	void clearAdj();
	bool getVisited();
	void setVisited(bool t);
	void setAdj(Links<T> &arg);

	void setPrevious(Nodes<T> * previous);
	Nodes<T> * getPrevious();

	void setLinked(bool f);
	int getIndegree() const;
	void removeAdj(int index);
	void removeOneAdj(Nodes<T> * dest);

	double getDist() const;
	void setDist(double newValue);

	Nodes* path;
	void setPath(Nodes* value);
	Nodes<T>* getPath() const;

	void addEdge(Nodes<T> * dest, double wght);

};

template <class T>
bool Nodes<T>::getProcessing(){
	return this->processing;
}
template <class T>
void Nodes<T>::setProcessing(bool t){
	this->processing = t;
}


template <class T>
void Nodes<T>::addEdge(Nodes<T> *dest, double wght) {
	Links<T> edgeD(dest, wght);
	edgeD.setOrigem(this);
	adj.push_back(edgeD);
}

template<class T>
void Nodes<T>::setDist(double newValue){
	this->dist = newValue;
}

template<class T>
void Nodes<T>::setPath(Nodes* value){
	this->path = value;
}

template<class T>
bool Nodes<T>::getVisited(){
	return this->visited;
}

template<class T>
void Nodes<T>::setPrevious(Nodes<T> * previous){
	this->previous = previous;
}

template<class T>
Nodes<T>* Nodes<T>::getPath() const{
	return this->path;
}

template <class T>
double Nodes<T>::getDist() const {
	return this->dist;
}

template <class T>
void Nodes<T>::setInfo(T info){
	this->info = info;
}

template <class T>
void Nodes<T>::setVisited(bool t){
	this->visited = t;
}

template <class T>
void Nodes<T>::removeOneAdj(Nodes<T> * dest){
	for (unsigned int i = 0; i < adj.size(); i++){
		if (dest->getInfo() == adj[i].getDest()->getInfo())
			adj.erase(adj.begin() + i);
	}
}

template <class T>
void Nodes<T>::clearAdj(){
	adj.clear();
}

template<class T>
void Nodes<T>::removeAdj(int index){
	adj.erase(adj.begin() + index);

}

template <class T>
int Nodes<T>::getIndegree() const {
	return this->indegree;
}
template<class T>
std::vector<Links<T>> Nodes<T>::getAdj(){
	return adj;
}

template <class T>
Nodes<T>::Nodes(T in) : info(in){
	visited = false;
	linked = false;
	dist = 0;
	path = 0;
	previous = 0;
	processing = false;
	indegree = -1;
}

template <class T>
T Nodes<T>::getInfo(){
	return this->info;
}

template<class T>
bool Nodes<T>::getLinked(){
	return this->linked;
}

template<class T>
void Nodes<T>::setAdj(Links<T> &arg){
	adj.push_back(arg);
}

template<class T>
void Nodes<T>::setLinked(bool t){
	this->linked = t;
}



template<class T>
Nodes<T> * Nodes<T>::getPrevious(){
	return this->previous;
}

#endif
