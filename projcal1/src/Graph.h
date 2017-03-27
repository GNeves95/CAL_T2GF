#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include "nodes.h"
#include "Utilitarios.h"
#include "MinHeap.h"

using namespace std;

template <class T> class Links;
template <class T> class Graph;

#define INT_INFINITY 999999

template <class T>
class Graph {
	vector<Nodes<T> *> vertexSet;
	
public:
	vector<Nodes<T> * > getVertexSet();
	vector<Nodes<T>* > calculatePrim();
	int getNumVertex();
	bool addEdge(const T &sourc, const T &dest, double w);
	bool addNode(const T &in);
	double getEstruturaLength();
	void dijkstra(Nodes<T> * source);
	void createGraph();
	void saveGraph();
	Nodes<T> * findNode(string name);
	bool createNode();
	bool createLink();
	bool deleteLink();
	bool deleteNode();
	void showPaths(int posVertice);
	void setShortestPaths(int posVertice);
	double leastUsageOfCable(vector<Nodes<T> *> vec, int last);
	Graph<T> clone();
};


template<class T>
void Graph<T>::saveGraph(){

	for (unsigned int i = 0; i < vertexSet.size(); i++){
		vertexSet[i]->setVisited(false);
	}
	ofstream file1;
	ofstream file2;

	file1.open("nodes.txt");
	for (unsigned int i = 0; i < vertexSet.size(); i++){
		file1 << vertexSet[i]->getInfo().getNome() << endl;
	}
	file1.close();
	
	file2.open("links.txt");
	for (unsigned int i = 0; i < vertexSet.size(); i++){
		for (unsigned int j = 0; j < vertexSet[i]->getAdj().size(); j++){
			if (!vertexSet[i]->getAdj()[j].getDest()->getVisited()){
				file2 << vertexSet[i]->getInfo().getNome() << endl;
				file2 << vertexSet[i]->getAdj()[j].getDest()->getInfo().getNome() << endl;
				file2 << vertexSet[i]->getAdj()[j].getWeight() << endl;
			}
		}
		vertexSet[i]->setVisited(true);
	}
	file2.close();

}

template<class T>
double Graph<T>::leastUsageOfCable(vector<Nodes<T> *> vec, int last){
	cout << "It will be needed: " << vec[last]->getInfo().getMinDist() << " units of cable"<<endl;
	return (vec[last]->getInfo().getMinDist());
}

template<class T>
void Graph<T>::setShortestPaths(int posVertice) {

	Nodes<T> * vert1 = vertexSet[posVertice];
	dijkstra(vert1);
}


template<class T>
bool Graph<T>::deleteLink(){
	int a, b;
	while (true){
		for (unsigned int i = 0; i < vertexSet.size(); i++){

			cout << "Number: " << i << " - Node: " << vertexSet[i]->getInfo() << endl;
		}
		cout << "Choose Node Number: ";
		cin >> a;
		if (a >= 0 && a < vertexSet.size())
			break;
	}
	while (true){
		if (vertexSet[a]->getAdj().size() <= 0){
			cout << "There are no nodes linked to the selected one!" << endl;
			return false;
		}
		unsigned int i;
		for (i = 0; i < vertexSet[a]->getAdj().size(); i++){
			cout << "Number: " << i << " - Node: " << vertexSet[a]->getAdj()[i].getDest()->getInfo() << endl;
		}
		cout << "Choose Node Number: ";
		cin >> b;
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
			
			cout << "Number: " << i << " - Node: " << vertexSet[i]->getInfo() << endl;
		}
		cout << "Choose Node Number: ";
		cin >> a;
		if (a >= 0 && a < vertexSet.size())
			break;
	}
	while (true){
		for (unsigned int i = 0; i < vertexSet.size(); i++){
			if (i != a)
				cout << "Number: " << i << " - Node: "<< vertexSet[i]->getInfo() << endl;
		}
		cout << "Choose Node Number: ";
		cin >> b;
		if (b >= 0 && b < vertexSet.size())
			break;
	}
	
	for (unsigned int i = 0; i < vertexSet[a]->getAdj().size(); i++){
		
		if (vertexSet[a]->getAdj()[i].getDest()->getInfo() == vertexSet[b]->getInfo()){
			cout << "The Nodes are already related, therefore it is impossible to establish a new Link. " << endl;
			return false;
		}
	}
	for (unsigned int i = 0; i < vertexSet[b]->getAdj().size(); i++){
		if (vertexSet[b]->getAdj()[i].getDest()->getInfo() == vertexSet[a]->getInfo()){
			cout << "The Nodes are already related, therefore it is impossible to establish a new Link. " << endl;
			return false;
		}
	}
	cout << "The Nodes are not related in any way. Please specify the Weight for the new Link: ";
	cin >> weight;
	Nodes<T> *n1 = new Nodes<T>(vertexSet[b]->getInfo());
	Links<T> *l1 = new Links<T>(n1, weight);
	vertexSet[a]->setAdj(*l1);

	return true;

}

template<class T>
bool Graph<T>::createNode(){

	int a;
	double weight;
	string info;
	while (true){
		for (unsigned int i = 0; i < vertexSet.size(); i++){
			cout << "Node: " << i << endl;
		}
		cout << "Choose Node Number: ";
		cin >> a;
		if (a >= 0 &&(unsigned int) a < vertexSet.size())
			break;
	}
	Nodes<T> * v1 = vertexSet[a];

	cout << "New Node Name: ";
	cin >> info;
	Hotspot h1(info,-1,-1);
	addNode(h1);
	cout << "Weight for the new Connection :";
	cin >> weight;

	if (addEdge(vertexSet[a]->getInfo(), h1, weight))
		if (addEdge(h1, vertexSet[a]->getInfo(), weight))
			return true;
	return false;
}



template<class T>
Nodes<T> * Graph<T>::findNode(string name) {
	Nodes<Hotspot> * vert;
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

	ifstream file;


	file.open("nodes.txt");
	string name;
	while (!file.eof()){
		file >> name;
		Hotspot h1(name, 0, 0);
		addNode(h1);
	}

	file.close();

	file.open("links.txt");
	string sourceName, destName, weightStr;
	while (!file.eof()){
		file >> sourceName;
		file >> destName;
		file >> weightStr;

		Hotspot hsource = findNode(sourceName)->getInfo();
		Hotspot hdest = findNode(destName)->getInfo();
		double weight = stod(weightStr);
		addEdge(hsource, hdest, weight);  //Adiciona um para um  //Bidirecional. [1]->[2] [1]<-[2]
		addEdge(hdest, hsource, weight);
	}

	file.close();
}


template <class T>
struct vertex_greater_than {
	bool operator()(Nodes<T> * a, Nodes<T> * b) const {
		return a->getInfo().getDistMin() > b->getInfo().getDistMin();
	}
};

template<class T>
void Graph<T>::showPaths(int posVertice) {
	for (int i = 0; i < vertexSet.size(); i++) {
		Nodes<Hotspot> * vert = vertexSet[i];
		cout << "Caminho mais curto ate " << vert->getInfo() << " dist("
			<< vert->getInfo().getMinDist() << ")";
		while (vert != vertexSet.at(posVertice)) {
			//cout << "vert name: " << vert->getInfo() << endl;
			cout << " <-- " << vert->getPrevious()->getInfo() << " dist("
				<< vert->getPrevious()->getInfo().getMinDist() << ")";

			vert = vert->getPrevious();
		}
		cout << endl;
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
		vector<Links<T> > edges = this->vertexSet[i]->getAdj();
		for (unsigned int a = 0; a < edges.size(); a++)
			ret.addEdge(this->vertexSet[i]->getInfo(), edges[a].getDest()->getInfo(), edges[a].getWeight());
	}

	return ret;
}

template <class T>
vector<Nodes<T>* > Graph<T>::calculatePrim(){
	
	double maxdist = 999999;
	for (unsigned int i = 0; i < this->vertexSet.size(); i++) {
		this->vertexSet[i]->setPath(NULL);
		this->vertexSet[i]->setDist(maxdist);
		this->vertexSet[i]->setVisited(false);
	}

	T sourceHotspot = vertexSet[0]->getInfo();
	sourceHotspot.setMinDist(0);
	vertexSet[0]->setInfo(sourceHotspot);
	vector<Nodes<T> *> vertHeap;
	Push(vertHeap, vertexSet[0]);
	
	

	while (!vertHeap.empty()) {

		Nodes<T> * v = Pop(vertHeap);
		
		if (!v->getVisited())
		{
			v->setVisited(true);
			for (unsigned int i = 0; i < v->getAdj().size(); i++) {

				Nodes<T>* w = v->getAdj()[i].getDest(); 

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

			cout << "Number: " << i << " - Node: " << vertexSet[i]->getInfo() << endl;
		}
		cout << "Choose Node Number: ";
		cin >> a;
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
void Graph<T>::dijkstra(Nodes<T> * source){

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
	vector<Nodes<T> *> vertHeap;
	Push(vertHeap, source);

	while (vertHeap.size() != 0) {
		Nodes<T> * u = Pop(vertHeap);
		u->setVisited(true);
		string nome = u->getInfo().getNome();
		for (int i = 0; i < u->getAdj().size(); i++) {
			Nodes<T> * v = u->getAdj()[i].getDest();
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
	Nodes<T>  *vertice = new Nodes<T>(in);
	vertexSet.push_back(vertice);
	return true;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	typename vector<Nodes<T>*>::iterator it = vertexSet.begin();
	typename vector<Nodes<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Nodes<T> *vS = NULL, *vD = NULL;
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
int Graph<T>::getNumVertex() {
	return vertexSet.size();
}

template <class T>
vector<Nodes<T> * > Graph<T>::getVertexSet() {
	return vertexSet;
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


#endif