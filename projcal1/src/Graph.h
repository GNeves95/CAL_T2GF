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
#include <cstdlib>
#include "graphviewer.h"
#include "Address.h"
#include "MinHeap.h"

constexpr int height { 400 };
constexpr int width { 200 };

constexpr float maxLatitude = 42.5;
constexpr float minLatitude = 36.8;

constexpr float maxLongitude = -6.1;
constexpr float minLongitude = -10.3;

float lon2coord(float x){
	return (x-minLongitude)/(maxLongitude-minLongitude);
}

float lat2coord(float x){
	return (x-maxLatitude)/(minLatitude-maxLatitude);
}

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
	void addEdge(Vertex<T> * dest, double wght, bool clsd, unsigned int i);

	bool operator < (const Vertex<T> &v2) const;
	friend class Graph<T>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in), previous(0){visited = false; dist = 0; path = 0; processing = false; linked = false; indegree = -1;}


template <class T>
class Edge {
	static unsigned int id;
	unsigned int thisId;
	Vertex<T> * dest;
	double weight;
	Vertex<T> * origem;
	bool closed;
public:
	Edge(Vertex<T> *d, double w);
	Edge(Vertex<T> *d, double w, bool c, unsigned int i);
	double getWeight();
	bool getClosed();
	void openRoad(GraphViewer *gv);
	void closeRoad(GraphViewer *gv);
	Vertex<T> * getDest();
	Vertex<T> * getOrigem();
	void setOrigem(Vertex<T> * neworig);
	void setDest(Vertex<T> * newdest);
	friend class Graph<T>;
	friend class Vertex<T>;
	unsigned int getId();
};

template <class T>
unsigned int Edge<T>::id { 0 };

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d){weight = w; closed = false; origem = 0; thisId = id; id++;}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, bool c, unsigned int i): dest(d){weight = w; closed = c; origem = 0; thisId = i; if(id <= i) id=i+1;}

template <class T>
class Graph {
	std::vector<Vertex<T> *> vertexSet;
public:
	std::vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;
	bool addEdge(const T &sourc, const T &dest, double w, bool c, unsigned int i);
	bool addEdge(const T &sourc, const T &dest, double w, bool c);
	bool addVertex(const T &in);
	double getEstruturaLength();
	void dijkstra(Vertex<T> * source);
	void createGraph(GraphViewer *gv);
	void saveGraph();
	Vertex<T> * findVertex(unsigned int id);
	Vertex<T> * findVertex(std::string name);
	void createVertex(GraphViewer *gv);
	void createEdge(GraphViewer *gv);
	void deleteEdge(GraphViewer *gv);
	void closeRoad(GraphViewer *gv);
	void openRoad(GraphViewer *gv);
	void deleteVertex(GraphViewer *gv);
	void showPaths(int posVertice, int posDest, GraphViewer *gv);
	void setShortestPaths(int posVertice);
	Graph<T> clone();
};

//Graph

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
	std::ofstream file1 { };
	std::ofstream file2 { };

	file1.open("Vertexs.csv");
	if(file1.is_open()){
		for (unsigned int i = 0; i < vertexSet.size(); i++){
			file1 << vertexSet[i]->getInfo().fileFormat() << std::endl;
		}
		file1.close();
	}

	file2.open("links.csv");
	if(file2.is_open()){
		for (unsigned int i = 0; i < vertexSet.size(); i++){
			for (unsigned int j = 0; j < vertexSet[i]->getAdj().size(); j++){
				//if (!vertexSet[i]->getAdj()[j].getDest()->getVisited()){
				file2 << vertexSet[i]->getInfo().getId() << ";";
				file2 << vertexSet[i]->getAdj()[j].getDest()->getInfo().getId() << ";";
				file2 << vertexSet[i]->getAdj()[j].getWeight() << ";";
				if(vertexSet[i]->getAdj()[j].getClosed())file2 << 1 << ";";
				else file2 << 0 << ";";
				//file2 << ((vertexSet[i]->getAdj()[j].getClosed())?'1':'0') << ";";
				file2 << vertexSet[i]->getAdj()[j].getId() << ";" << std::endl;
				//}
			}
			vertexSet[i]->setVisited(true);
		}
		file2.close();
	}

}

template<class T>
void Graph<T>::setShortestPaths(int posVertice) {

	Vertex<T> * vert1 = vertexSet[posVertice];
	dijkstra(vert1);
}

template<class T>
void Graph<T>::deleteEdge(GraphViewer *gv){
	int a { };
	int b { };
	while (true){
		for (unsigned int i = 0; i < vertexSet.size(); i++){

			std::cout << "Number: " << i << " - Vertex: " << vertexSet[i]->getInfo() << std::endl;
		}
		std::cout << "Choose Vertex Number: ";
		std::cin >> a;
		if (a >= 0 && a < vertexSet.size())
			break;
	}
	while (true){
		if (vertexSet[a]->getAdj().size() <= 0){
			std::cout << "There are no Vertexs linked to the selected one!" << std::endl;
			return ;
		}
		unsigned int i { };
		for (i = 0; i < vertexSet[a]->getAdj().size(); i++){
			std::cout << "Number: " << i << " - Vertex: " << vertexSet[a]->getAdj()[i].getDest()->getInfo() << std::endl;
		}
		std::cout << "Choose Vertex Number: ";
		std::cin >> b;
		if (b >= 0 && b < vertexSet[a]->getAdj().size()){
			gv->removeEdge(vertexSet[a]->getAdj()[b].getId());
			vertexSet[a]->removeAdj(b);
			return ;
		}
	}
}

template<class T>
void Graph<T>::closeRoad(GraphViewer *gv){
	int a { };
	int b { };
	while (true){
		for (unsigned int i = 0; i < vertexSet.size(); i++){

			std::cout << "Number: " << i << " - Vertex: " << vertexSet[i]->getInfo() << std::endl;
		}
		std::cout << "Choose Vertex Number: ";
		std::cin >> a;
		if (a >= 0 && a < vertexSet.size())
			break;
	}
	while (true){
		if (vertexSet[a]->getAdj().size() <= 0){
			std::cout << "There are no Vertices linked to the selected one!" << std::endl;
			return ;
		}
		unsigned int i { };
		for (i = 0; i < vertexSet[a]->getAdj().size(); i++){
			std::cout << "Number: " << i << " - Vertex: " << vertexSet[a]->getAdj()[i].getDest()->getInfo() << std::endl;
		}
		std::cout << "Choose Vertex Number: ";
		std::cin >> b;
		if (b >= 0 && b < vertexSet[a]->getAdj().size()){
			vertexSet[a]->getAdj()[b].closeRoad(gv);

			//vertexSet[a]->removeAdj(b);
			return ;
		}
	}
}

template<class T>
void Graph<T>::openRoad(GraphViewer *gv){
	int a { };
	int b { };
	while (true){
		for (unsigned int i = 0; i < vertexSet.size(); i++){

			std::cout << "Number: " << i << " - Vertex: " << vertexSet[i]->getInfo() << std::endl;
		}
		std::cout << "Choose Vertex Number: ";
		std::cin >> a;
		if (a >= 0 && a < vertexSet.size())
			break;
	}
	while (true){
		if (vertexSet[a]->getAdj().size() <= 0){
			std::cout << "There are no Vertexs linked to the selected one!" << std::endl;
			return ;
		}
		unsigned int i { };
		for (i = 0; i < vertexSet[a]->getAdj().size(); i++){
			std::cout << "Number: " << i << " - Vertex: " << vertexSet[a]->getAdj()[i].getDest()->getInfo() << std::endl;
		}
		std::cout << "Choose Vertex Number: ";
		std::cin >> b;
		if (b >= 0 && b < vertexSet[a]->getAdj().size()){
			vertexSet[a]->getAdj()[b].openRoad(gv);

			//vertexSet[a]->removeAdj(b);
			return ;
		}
	}
}

template<class T>
void Graph<T>::createEdge(GraphViewer *gv){
	int a { }, b { };
	double weight { };


	while (true){
		for (unsigned int i = 0; i < vertexSet.size(); i++){

			std::cout << "Number: " << i << " - Vertex: " << vertexSet[i]->getInfo() << std::endl;
		}
		std::cout << "Choose Vertex Number: ";
		std::cin >> a;
		if (a >= 0 && a < vertexSet.size())
			break;
	}
	while (true){
		for (unsigned int i = 0; i < vertexSet.size(); i++){
			if (i != a)
				std::cout << "Number: " << i << " - Vertex: "<< vertexSet[i]->getInfo() << std::endl;
		}
		std::cout << "Choose Vertex Number: ";
		std::cin >> b;
		if (b >= 0 && b < vertexSet.size())
			break;
	}

	for (unsigned int i = 0; i < vertexSet[a]->getAdj().size(); i++){

		if (vertexSet[a]->getAdj()[i].getDest()->getInfo() == vertexSet[b]->getInfo()){
			std::cout << "The Vertexs are already related, therefore it is impossible to establish a new Link. " << std::endl;
			return ;
		}
	}
	/*for (unsigned int i = 0; i < vertexSet[b]->getAdj().size(); i++){
		if (vertexSet[b]->getAdj()[i].getDest()->getInfo() == vertexSet[a]->getInfo()){
			std::cout << "The Vertexs are already related, therefore it is impossible to establish a new Link. " << std::endl;
			return false;
		}
	}*/
	std::cout << "The Vertexs are not related in any way. Please specify the Weight for the new Link: ";
	std::cin >> weight;
	Vertex<T> *n1 = new Vertex<T> { vertexSet[b]->getInfo() };
	Edge<T> *l1 = new Edge<T> { n1, weight };
	gv->addEdge(l1->getId(),vertexSet[a]->getInfo().getId(), vertexSet[b]->getInfo().getId(),EdgeType::DIRECTED);
	vertexSet[a]->setAdj(*l1);
}

template<class T>
void Graph<T>::createVertex(GraphViewer *gv){

	float lo { }, la { };
	std::string info { };

	std::cout << "New Vertex Name: ";
	std::cin >> info;
	//info = "Porto";
	std::cout << "Vertex Longitude: ";
	std::cin >> lo;
	//lo = -8.607;
	std::cout << "Vertex Latitude: ";
	std::cin >> la;
	//la = 41.178;
	Address a1(lo, la, info);
	this->addVertex(a1);
	gv->addNode(a1.getId(),lon2coord(lo)*width,lat2coord(la)*height);
	gv->setVertexLabel(a1.getId(), info);
	gv->setVertexColor(a1.getId(),CYAN);
}

template<class T>
Vertex<T> * Graph<T>::findVertex(unsigned int id) {
	Vertex<Address> *vert { };
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->getInfo().getId() == id) {
			vert = vertexSet[i];
			return vert;
		}
	}
	return NULL;
}

template<class T>
Vertex<T> * Graph<T>::findVertex(std::string name) {
	Vertex<Address> *vert { };
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->getInfo().getNome() == name) {
			vert = vertexSet[i];
			return vert;
		}
	}
	return NULL;
}

template<class T>
void Graph<T>::createGraph(GraphViewer *gv){

	std::ifstream file { };


	file.open("Vertexs.csv");
	int id { };
	std::string line { };
	std::string name { };
	float longitude { };
	float latitude { };
	if(file.is_open()){
		while(getline(file,line)){
			//file >> line;
			std::string aux { };
			unsigned int ctrl { 0 };
			for(unsigned int i=0; i < line.size(); i++){
				if(line.at(i) == ';'){
					switch(ctrl){
					case 0:
						id = std::atoi(aux.c_str());
						break;
					case 1:
						longitude = std::atof(aux.c_str());
						break;
					case 2:
						latitude = std::atof(aux.c_str());
						break;
					case 3:
						name = aux;
						break;
					default:
						break;
					}
					ctrl++;
					aux = std::string();
				}
				else aux += line.at(i);
			}
			Address a1(id, longitude, latitude, name);
			gv->addNode(a1.getId(),lon2coord(longitude)*width,lat2coord(latitude)*height);
			gv->setVertexLabel(a1.getId(), a1.getNome());
			gv->setVertexColor(a1.getId(),CYAN);
			addVertex(a1);
		}

		file.close();
	}

	file.open("links.csv");
	int sourceId { }, destId { }, vertId { };
	double weight { };
	bool closed { };
	if(file.is_open()){
		while(getline(file,line)){
			//file >> line;
			std::string aux { };
			unsigned int ctrl { 0 };

			for(unsigned int i=0; i < line.size(); i++){
				if(line.at(i) == ';'){
					switch(ctrl){
					case 0:
						sourceId = std::atoi(aux.c_str());
						break;
					case 1:
						destId = std::atoi(aux.c_str());
						break;
					case 2:
						weight = std::strtod(aux.c_str(), 0);
						break;
					case 3:
						closed = std::atoi(aux.c_str());;
						break;
					case 4:
						vertId = std::atoi(aux.c_str());;
						break;
					default:
						break;
					}
					ctrl++;
					aux = std::string();
				}
				else aux += line.at(i);
			}

			Address asource = findVertex(sourceId)->getInfo();
			Address adest = findVertex(destId)->getInfo();
			gv->addEdge(vertId,asource.getId(), adest.getId(),EdgeType::DIRECTED);
			if(closed) gv->setEdgeColor(vertId,RED);
			else gv->setEdgeColor(vertId,BLACK);
			addEdge(asource, adest, weight, closed, vertId);  //Adiciona um para um  //Bidirecional. [1]->[2] [1]<-[2]
			//addEdge(adest, asource, weight, closed);
		}

		file.close();
	}
}

template <class T>
struct vertex_greater_than {
	bool operator()(Vertex<T> * a, Vertex<T> * b) const {
		return a->getInfo().getDistMin() > b->getInfo().getDistMin();
	}
};

template<class T>
void Graph<T>::showPaths(int posVertice, int posDest, GraphViewer *gv) {
	Vertex<Address> * vert = vertexSet[posDest];
	std::cout << "Caminho mais curto ate " << vert->getInfo() << " dist("
			<< vert->getInfo().getMinDist() << ")";
	while (vert != vertexSet.at(posVertice)) {
		Vertex<Address> * aux = vert->getPrevious();
		if(!aux){
			std::cout << "No Path Found!" << std::endl;
			return ;
		}
		//std::cout << "vert name: " << vert->getInfo() << std::endl;
		std::cout << " <-- " << vert->getPrevious()->getInfo() << " dist("
				<< vert->getPrevious()->getInfo().getMinDist() << ")";

		for(unsigned int i=0; i < aux->getAdj().size(); i++){
			if(aux->getAdj()[i].getDest()->getInfo().getNome() == vert->getInfo().getNome()){
				unsigned int auxid { 9999};
				//std::cerr << aux->getAdj()[i].getId() << std::endl;
				for(unsigned int j=0; j < vertexSet.size(); j++){
					if(vertexSet[j]->getInfo().getNome() == aux->getInfo().getNome()){
						for(unsigned int k = 0; k < vertexSet[j]->getAdj().size(); k++){
							if(vertexSet[j]->getAdj()[k].getDest()->getInfo().getNome() == vert->getInfo().getNome()){
								auxid = vertexSet[j]->getAdj()[k].getId();
								break;
							}
						}
						break;
					}
				}
				//std::cerr << auxid << std::endl;
				gv->setEdgeColor(auxid,GREEN);
				break;
			}
		}

		vert = vert->getPrevious();
	}
	std::cout << std::endl;

}

template <class T>
Graph<T> Graph<T>::clone()
{
	Graph<T> ret { };
	for (unsigned int i = 0; i < this->vertexSet.size(); i++)
		ret.addVertex(this->vertexSet[i]->getInfo());

	for (unsigned int i = 0; i < this->vertexSet.size(); i++)
	{
		std::vector<Edge<T> > edges = this->vertexSet[i]->getAdj();
		for (unsigned int a = 0; a < edges.size(); a++)
			ret.addEdge(this->vertexSet[i]->getInfo(), edges[a].getDest()->getInfo(), edges[a].getWeight(), edges[a].getClosed());
	}

	return ret;
}

template <class T>
void Graph<T>::deleteVertex(GraphViewer *gv) {
	int a { };
	while (true){
		for (unsigned int i = 0; i < vertexSet.size(); i++){
			std::cout << "Number: " << i << " - Vertex: " << vertexSet[i]->getInfo() << std::endl;
		}
		std::cout << "Choose Vertex Number: ";
		std::cin >> a;
		if (a >= 0 && a < vertexSet.size())
			break;
	}

	//gv->removeEdge();

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
	//return true;
}

template <class T>
void Graph<T>::dijkstra(Vertex<T> * source){
	double maxdist = 99999;
	for(unsigned int i=0; i < vertexSet.size(); i++){
		this->vertexSet[i]->setPrevious(0);
		T aux = this->vertexSet[i]->getInfo();
		aux.setMinDist(maxdist);
		this->vertexSet[i]->setInfo(aux);
	}

	T sourceAdd = source->getInfo();
	sourceAdd.setMinDist(0);
	source->setInfo(sourceAdd);
	std::vector<Vertex<T> *> heap { };
	heap.push_back(source);
	//source->setVisited();
	bool searching { true };
	do{
		std::vector<Vertex<T> *> aux_heap { };
		while(heap.size() != 0){
			heap.at(0)->setVisited(true);
			for(unsigned int i = 0; i < heap.at(0)->getAdj().size(); i++){
				if(!(heap.at(0)->getAdj()[i].getClosed())){
					double dist { };
					dist = heap.at(0)->getInfo().getMinDist() + heap.at(0)->getAdj()[i].getWeight();
					if(dist < heap.at(0)->getAdj()[i].getDest()->getInfo().getMinDist()){
						heap.at(0)->getAdj()[i].getDest()->setPrevious(heap.at(0));

						T aux = heap.at(0)->getAdj()[i].getDest()->getInfo();
						aux.setMinDist(dist);
						heap.at(0)->getAdj()[i].getDest()->setInfo(aux);
					}
					if(!(heap.at(0)->getAdj()[i].getDest()->getVisited())) aux_heap.push_back(heap.at(0)->getAdj()[i].getDest());

				}
			}
			heap.erase(heap.begin());
		}
		if(aux_heap.size() != 0) heap = aux_heap;
		else searching = false;
	}
	while(searching);

	/*
	for (unsigned int i = 0; i < this->vertexSet.size(); i++) {
		this->vertexSet[i]->setPath(NULL);
		for (unsigned int j = 0; j < vertexSet[i]->getAdj().size(); j++){
			this->vertexSet[i]->getAdj()[j].getDest()->getInfo().setMinDist(maxdist);
		}
		this->vertexSet[i]->getInfo().setMinDist(maxdist);
		this->vertexSet[i]->setDist(maxdist);
		this->vertexSet[i]->setProcessing(false);
	}

	T sourceAddress = source->getInfo();
	sourceAddress.setMinDist(0);
	source->setInfo(sourceAddress);
	std::vector<Vertex<T> *> vertHeap { };
	Push(vertHeap, source);

	for(unsigned int i=0; i < vertexSet.size(); i++) Push(vertHeap,vertexSet[i]);

	std::sort_heap(vertHeap.begin(), vertHeap.end(), greater1());

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
				T Address = v->getInfo();
				Address.setMinDist(distanceThroughU);
				v->setInfo(Address);
				v->setPrevious(u);
				Push(vertHeap, v);

			}
		}
	}*/
}

template <class T>
bool Graph<T>::addVertex(const T &in){
	typename std::vector<Vertex<T>*>::iterator it { };
	it = vertexSet.begin();
	typename std::vector<Vertex<T>*>::iterator ite { };
	ite = vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;

	Vertex<T> *v1 = new Vertex<T> { in };
	vertexSet.push_back(v1);
	return true;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, bool c, unsigned int i) {
	typename std::vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename std::vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found { 0 };
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
	vS->addEdge(vD, w, c, i);

	return true;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, bool c) {
	typename std::vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename std::vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found { 0 };
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
inline bool Edge<T>::getClosed() {
	return closed;
}

template<class T>
inline void Edge<T>::openRoad(GraphViewer *gv) {
	gv->setEdgeColor(thisId,BLACK);
	closed = false;
}

template<class T>
inline void Edge<T>::closeRoad(GraphViewer *gv) {
	gv->setEdgeColor(thisId,RED);
	closed = true;
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
void Vertex<T>::addEdge(Vertex<T> *dest, double wght, bool clsd, unsigned int i) {
	Edge<T> edgeD(dest,wght, clsd, i);
	edgeD.setOrigem(this);
	adj.push_back(edgeD);
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double wght) {
	Edge<T> edgeD(dest,wght);
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

template<class T>
inline unsigned int Edge<T>::getId() {
	return thisId;
}

template<class T>
inline bool Vertex<T>::operator <(const Vertex<T>& v2) const {
	return info.getMinDist() > v2->getInfo().getMinDist();;
}

#endif /* GRAPH_H_ */
