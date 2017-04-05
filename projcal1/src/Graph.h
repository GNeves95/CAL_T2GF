/*
 * Graph.h
 *
 *  Created on: 03/04/2017
 *      Author: up201306485
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Address.h"

template <class T> class Edge;
template <class T> class Graph;

template <class T>
class Vertex {
	T info;
	std::vector<Edge<T>  > adj;
	Vertex<T> * previous;
	bool visited, linked, processing;
	double dist;
	int indegree;
public:
	Vertex(T in);
	T getInfo();
	void setInfo(T info);
	bool getLinked();

	bool getProcessing();
	void setProcessing(bool t);

	std::vector<Edge<T>	> getAdj();
	void clearAdj();
	bool getVisited();
	void setVisited(bool t);
	void setAdj(Edge<T> &arg);

	void setPrevious(Vertex<T> * previous);
	Vertex<T> * getPrevious();

	void setLinked(bool f);
	int getIndegree() const;
	void removeAdj(int index);
	void removeOneAdj(Vertex<T> * dest);

	double getDist() const;
	void setDist(double newValue);

	Vertex* path;
	void setPath(Vertex* value);
	Vertex<T>* getPath() const;

	void addEdge(Vertex<T> * dest, double wght);
	friend class Graph<T>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in), previous(0){visited = false; dist = 0; path = 0; processing = false; linked = false; indegree = -1;}


template <class T>
class Edge {
	Vertex<T> * dest;
	double weight;
	Vertex<T> * origem;
public:
	Edge(Vertex<T> *d, double w);
	double getWeight();
	Vertex<T> * getDest();
	Vertex<T> * getOrigem();
	void setOrigem(Vertex<T> * neworig);
	void setDest(Vertex<T> * newdest);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d){weight = w;}

template <class T>
class Graph {
	std::vector<Vertex<T> *> vertexSet;
public:
	std::vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;
	std::vector<Vertex<T>* > calculatePrim();
	bool addEdge(const T &sourc, const T &dest, double w);
	bool addNode(const T &in);
	double getEstruturaLength();
	void dijkstra(Vertex<T> * source);
	void createGraph();
	void saveGraph();
	Vertex<T> * findNode(std::string name);
	bool createNode();
	bool createLink();
	bool deleteLink();
	bool deleteNode();
	void showPaths(int posVertice);
	void setShortestPaths(int posVertice);
	double leastUsageOfCable(std::vector<Vertex<T> *> vec, int last);
	Graph<T> clone();
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
std::vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template<class T>
void Graph<T>::saveGraph(){

	for (unsigned int i = 0; i < vertexSet.size(); i++){
		vertexSet[i]->setVisited(false);
	}
	std::ofstream file1;
	std::ofstream file2;

	file1.open("nodes.txt");
	for (unsigned int i = 0; i < vertexSet.size(); i++){
		file1 << vertexSet[i]->getInfo().getNome() << std::endl;
	}
	file1.close();

	file2.open("links.txt");
	for (unsigned int i = 0; i < vertexSet.size(); i++){
		for (unsigned int j = 0; j < vertexSet[i]->getAdj().size(); j++){
			if (!vertexSet[i]->getAdj()[j].getDest()->getVisited()){
				file2 << vertexSet[i]->getInfo().getNome() << std::endl;
				file2 << vertexSet[i]->getAdj()[j].getDest()->getInfo().getNome() << std::endl;
				file2 << vertexSet[i]->getAdj()[j].getWeight() << std::endl;
			}
		}
		vertexSet[i]->setVisited(true);
	}
	file2.close();

}

template<class T>
void Graph<T>::setShortestPaths(int posVertice) {

	Vertex<T> * vert1 = vertexSet[posVertice];
	dijkstra(vert1);
}

template<class T>
bool Graph<T>::deleteLink(){
	int a, b;
	while (true){
		for (unsigned int i = 0; i < vertexSet.size(); i++){

			std::cout << "Number: " << i << " - Node: " << vertexSet[i]->getInfo() << std::endl;
		}
		std::cout << "Choose Node Number: ";
		std::cin >> a;
		if (a >= 0 && a < vertexSet.size())
			break;
	}
	while (true){
		if (vertexSet[a]->getAdj().size() <= 0){
			std::cout << "There are no nodes linked to the selected one!" << std::endl;
			return false;
		}
		unsigned int i;
		for (i = 0; i < vertexSet[a]->getAdj().size(); i++){
			std::cout << "Number: " << i << " - Node: " << vertexSet[a]->getAdj()[i].getDest()->getInfo() << std::endl;
		}
		std::cout << "Choose Node Number: ";
		std::cin >> b;
		if (b >= 0 && b < vertexSet[a]->getAdj().size()){
			vertexSet[a]->removeAdj(b);
			return true;
		}
	}
	return false;
}

template<class T>
bool Graph<T>::createLink(){
	int a, b;
	double weight;


	while (true){
		for (unsigned int i = 0; i < vertexSet.size(); i++){

			std::cout << "Number: " << i << " - Node: " << vertexSet[i]->getInfo() << std::endl;
		}
		std::cout << "Choose Node Number: ";
		std::cin >> a;
		if (a >= 0 && a < vertexSet.size())
			break;
	}
	while (true){
		for (unsigned int i = 0; i < vertexSet.size(); i++){
			if (i != a)
				std::cout << "Number: " << i << " - Node: "<< vertexSet[i]->getInfo() << std::endl;
		}
		std::cout << "Choose Node Number: ";
		std::cin >> b;
		if (b >= 0 && b < vertexSet.size())
			break;
	}

	for (unsigned int i = 0; i < vertexSet[a]->getAdj().size(); i++){

		if (vertexSet[a]->getAdj()[i].getDest()->getInfo() == vertexSet[b]->getInfo()){
			std::cout << "The Nodes are already related, therefore it is impossible to establish a new Link. " << std::endl;
			return false;
		}
	}
	for (unsigned int i = 0; i < vertexSet[b]->getAdj().size(); i++){
		if (vertexSet[b]->getAdj()[i].getDest()->getInfo() == vertexSet[a]->getInfo()){
			std::cout << "The Nodes are already related, therefore it is impossible to establish a new Link. " << std::endl;
			return false;
		}
	}
	std::cout << "The Nodes are not related in any way. Please specify the Weight for the new Link: ";
	std::cin >> weight;
	Vertex<T> *n1 = new Vertex<T>(vertexSet[b]->getInfo());
	Edge<T> *l1 = new Edge<T>(n1, weight);
	vertexSet[a]->setAdj(*l1);

	return true;
}

template<class T>
bool Graph<T>::createNode(){

	int a;
	double weight;
	float lo, la;
	std::string info;
	while (true){
		for (unsigned int i = 0; i < vertexSet.size(); i++){
			std::cout << "Node: " << i << std::endl;
		}
		std::cout << "Choose Node Number: ";
		std::cin >> a;
		if (a >= 0 &&(unsigned int) a < vertexSet.size())
			break;
	}
	Vertex<T> * v1 = vertexSet[a];

	std::cout << "New Node Name: ";
	std::cin >> info;
	std::cout << "Node Longitude: ";
	std::cin >> lo;
	std::cout << "Node Latitude: ";
	std::cin >> la;
	Address a1(lo, la, info);
	addNode(a1);
	std::cout << "Weight for the new Connection :";
	std::cin >> weight;

	if (addEdge(vertexSet[a]->getInfo(), a1, weight))
		if (addEdge(a1, vertexSet[a]->getInfo(), weight))
			return true;
	return false;
}

template<class T>
Vertex<T> * Graph<T>::findNode(std::string name) {
	Vertex<Address> *vert;
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->getInfo().getNome() == name) {
			vert = vertexSet[i];
			return vert;
		}
	}
	return NULL;
}

template<class T>
void Graph<T>::createGraph(){

	std::ifstream file;


	file.open("nodes.txt");
	std::string name;
	while (!file.eof()){
		file >> name;
		Address a1(0, 0, 0, name);
		addNode(a1);
	}

	file.close();

	file.open("links.txt");
	std::string sourceName, destName, weightStr;
	while (!file.eof()){
		file >> sourceName;
		file >> destName;
		file >> weightStr;

		Address asource = findNode(sourceName)->getInfo();
		Address adest = findNode(destName)->getInfo();
		double weight = std::strtod(weightStr.c_str(), 0);
		addEdge(asource, adest, weight);  //Adiciona um para um  //Bidirecional. [1]->[2] [1]<-[2]
		addEdge(adest, asource, weight);
	}

	file.close();
}

template <class T>
struct vertex_greater_than {
	bool operator()(Vertex<T> * a, Vertex<T> * b) const {
		return a->getInfo().getDistMin() > b->getInfo().getDistMin();
	}
};

template<class T>
void Graph<T>::showPaths(int posVertice) {
	for (int i = 0; i < vertexSet.size(); i++) {
		Vertex<Address> * vert = vertexSet[i];
		std::cout << "Caminho mais curto ate " << vert->getInfo() << " dist("
			<< vert->getInfo().getMinDist() << ")";
		while (vert != vertexSet.at(posVertice)) {
			//std::cout << "vert name: " << vert->getInfo() << std::endl;
			std::cout << " <-- " << vert->getPrevious()->getInfo() << " dist("
				<< vert->getPrevious()->getInfo().getMinDist() << ")";

			vert = vert->getPrevious();
		}
		std::cout << std::endl;
	}
}

template <class T>
Graph<T> Graph<T>::clone()
{
	Graph<T> ret;
	for (unsigned int i = 0; i < this->vertexSet.size(); i++)
		ret.addNode(this->vertexSet[i]->getInfo());

	for (unsigned int i = 0; i < this->vertexSet.size(); i++)
	{
		std::vector<Edge<T> > edges = this->vertexSet[i]->getAdj();
		for (unsigned int a = 0; a < edges.size(); a++)
			ret.addEdge(this->vertexSet[i]->getInfo(), edges[a].getDest()->getInfo(), edges[a].getWeight());
	}

	return ret;
}

template <class T>
std::vector<Vertex<T>* > Graph<T>::calculatePrim(){

	double maxdist = 999999;
	for (unsigned int i = 0; i < this->vertexSet.size(); i++) {
		this->vertexSet[i]->setPath(NULL);
		this->vertexSet[i]->setDist(maxdist);
		this->vertexSet[i]->setVisited(false);
	}

	T sourceHotspot = vertexSet[0]->getInfo();
	sourceHotspot.setMinDist(0);
	vertexSet[0]->setInfo(sourceHotspot);
	std::vector<Vertex<T> *> vertHeap;
	Push(vertHeap, vertexSet[0]);



	while (!vertHeap.empty()) {

		Vertex<T> * v = Pop(vertHeap);

		if (!v->getVisited())
		{
			v->setVisited(true);
			for (unsigned int i = 0; i < v->getAdj().size(); i++) {

				Vertex<T>* w = v->getAdj()[i].getDest();

				if (!w->getVisited())
				{
					if (v->getAdj()[i].getWeight() < w->getDist()) {
						T hotspot = w->getInfo();
						hotspot.setMinDist(v->getInfo().getMinDist() + v->getAdj()[i].getWeight());
						w->setInfo(hotspot);
						w->setDist(v->getAdj()[i].getWeight());
						w->setPath(v);
						Push(vertHeap, w);
					}
				}
			}
		}

	}
	return this->vertexSet;
}

template <class T>
bool Graph<T>::deleteNode() {
	int a;
	while (true){
		for (unsigned int i = 0; i < vertexSet.size(); i++){

			std::cout << "Number: " << i << " - Node: " << vertexSet[i]->getInfo() << std::endl;
		}
		std::cout << "Choose Node Number: ";
		std::cin >> a;
		if (a >= 0 && a < vertexSet.size())
			break;
	}
	vertexSet[a]->clearAdj();

	for (unsigned int i = 0; i < vertexSet.size(); i++){
		if (i != a){
			for (unsigned int j = 0; j < vertexSet[i]->getAdj().size(); j++){
				if (vertexSet[a]->getInfo() == vertexSet[i]->getAdj()[j].getDest()->getInfo()){
					vertexSet[i]->removeOneAdj(vertexSet[a]);
				}
			}
		}
	}
	vertexSet.erase(vertexSet.begin() + a);
	return true;
}

template <class T>
void Graph<T>::dijkstra(Vertex<T> * source){

	double maxdist = 999999;
	for (unsigned int i = 0; i < this->vertexSet.size(); i++) {
		this->vertexSet[i]->setPath(NULL);
		for (unsigned int j = 0; j < vertexSet[i]->getAdj().size(); j++){
			this->vertexSet[i]->getAdj()[j].getDest()->getInfo().setMinDist(maxdist);
		}
		this->vertexSet[i]->getInfo().setMinDist(maxdist);
		this->vertexSet[i]->setDist(maxdist);
		this->vertexSet[i]->setProcessing(false);
	}

	T sourceHotspot = source->getInfo();
	sourceHotspot.setMinDist(0);
	source->setInfo(sourceHotspot);
	std::vector<Vertex<T> *> vertHeap;
	Push(vertHeap, source);

	while (vertHeap.size() != 0) {
		Vertex<T> * u = Pop(vertHeap);
		u->setVisited(true);
		std::string nome = u->getInfo().getNome();
		for (int i = 0; i < u->getAdj().size(); i++) {
			Vertex<T> * v = u->getAdj()[i].getDest();
			double weight = u->getAdj()[i].getWeight();
			double distanceThroughU = u->getInfo().getMinDist() + weight;

			if (distanceThroughU < v->getInfo().getMinDist()) {

				Remove(vertHeap, v);
				T hotspot = v->getInfo();
				hotspot.setMinDist(distanceThroughU);
				v->setInfo(hotspot);
				v->setPrevious(u);
				Push(vertHeap, v);

			}
		}
	}
}

template <class T>
bool Graph<T>::addNode(const T &in){

	for (unsigned int i = 0; i < vertexSet.size(); i++){
		if ((vertexSet.at(i)->getInfo()) == in)
			return false;
	}
	Vertex<T>  *vertice = new Vertex<T>(in);
	vertexSet.push_back(vertice);
	return true;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	typename std::vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename std::vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS = NULL, *vD = NULL;
	while (found != 2 && it != ite) {
		if ((*it)->getInfo() == sourc)
		{
			vS = *it; found++;
		}
		if ((*it)->getInfo() == dest)
		{
			vD = *it; found++;
		}
		it++;
	}
		if (found != 2)
			return false;
	vS->addEdge(vD, w);

	return true;
}

template <class T>
double Graph<T>::getEstruturaLength(){
	double ret = 0;
	for (unsigned int i = 0; i < vertexSet.size(); i++){
		for (unsigned int j = 0; j < vertexSet.at(i)->getAdj().size(); j++){
			ret += vertexSet.at(i)->getAdj()[j].getWeight();
		}

	}

	return ret;
}

//Edges

template<class T>
Vertex<T> * Edge<T>::getDest(){
	return this->dest;
}

template<class T>
void Edge<T>::setDest(Vertex<T> * newdest){
	this->dest = newdest;
}

template<class T>
Vertex<T> * Edge<T>::getOrigem(){
	return this->origem;
}

template<class T>
void Edge<T>::setOrigem(Vertex<T> * neworigem){

	this->origem = neworigem;
}

template <class T>
double Edge<T>::getWeight(){
	return weight;
}

//Vertex

template <class T>
bool Vertex<T>::getProcessing(){
	return this->processing;
}
template <class T>
void Vertex<T>::setProcessing(bool t){
	this->processing = t;
}


template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double wght) {
	Edge<T> edgeD(dest, wght);
	edgeD.setOrigem(this);
	adj.push_back(edgeD);
}

template<class T>
void Vertex<T>::setDist(double newValue){
	this->dist = newValue;
}

template<class T>
void Vertex<T>::setPath(Vertex* value){
	this->path = value;
}

template<class T>
bool Vertex<T>::getVisited(){
	return this->visited;
}

template<class T>
void Vertex<T>::setPrevious(Vertex<T> * previous){
	this->previous = previous;
}

template<class T>
Vertex<T>* Vertex<T>::getPath() const{
	return this->path;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
void Vertex<T>::setInfo(T info){
	this->info = info;
}

template <class T>
void Vertex<T>::setVisited(bool t){
	this->visited = t;
}

template <class T>
void Vertex<T>::removeOneAdj(Vertex<T> * dest){
	for (unsigned int i = 0; i < adj.size(); i++){
		if (dest->getInfo() == adj[i].getDest()->getInfo())
			adj.erase(adj.begin() + i);
	}
}

template <class T>
void Vertex<T>::clearAdj(){
	adj.clear();
}

template<class T>
void Vertex<T>::removeAdj(int index){
	adj.erase(adj.begin() + index);

}

template <class T>
int Vertex<T>::getIndegree() const {
	return this->indegree;
}
template<class T>
std::vector<Edge<T>> Vertex<T>::getAdj(){
	return adj;
}

template <class T>
T Vertex<T>::getInfo(){
	return this->info;
}

template<class T>
bool Vertex<T>::getLinked(){
	return this->linked;
}

template<class T>
void Vertex<T>::setAdj(Edge<T> &arg){
	adj.push_back(arg);
}

template<class T>
void Vertex<T>::setLinked(bool t){
	this->linked = t;
}



template<class T>
Vertex<T> * Vertex<T>::getPrevious(){
	return this->previous;
}

#endif /* GRAPH_H_ */
