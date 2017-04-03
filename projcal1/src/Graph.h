/*
 * Graph.h
 *
 *  Created on: 03/04/2017
 *      Author: up201306485
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

template <class T> class Edge;
template <class T> class Graph;

template <class T>
class Vertex {
	T info;
	std::vector<Edge<T>  > adj;
	bool visited;
public:
	Vertex(T in);
	friend class Graph<T>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in){visited = false;}


template <class T>
class Edge {
	Vertex<T> * dest;
	double weight;
public:
	Edge(Vertex<T> *d, double w);
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
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
std::vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

#endif /* GRAPH_H_ */
