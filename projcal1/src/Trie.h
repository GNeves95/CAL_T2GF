/*
 * Trie.h
 *
 *  Created on: May 16, 2017
 *      Author: Utilizador
 */

#ifndef TRIE_H_
#define TRIE_H_

#include <iostream>
#include <string>
#include <vector>
#include "Graph.h"

template <class T> class Edge;

template <class T>
class Node{
private:
	char c;
	std::vector<Node<T>*> children;
	bool fim;
	std::vector<Edge<T> *> EdgeSet;
public:
	Node() {c=-1; fim = false;};
	Node(char ch, bool f);
	char getChar(){return c;};
	void setFim(bool f){fim = f;};
	bool getFim();
	Node<T> *getFilho(char ch);
	Node<T> *addFilho(char ch, bool f);
	void addEdge(Edge<T> * edge);
	std::vector<Edge<T> *> getEdges();
};

template <class T>
class Trie{
private:
	Node<T> *root;
public:
	Trie();
	void insertWord(std::string word, Edge<T> *edge);
	std::vector<Edge<T> *> search(std::string word);

};

//NODE

template <class T>
Node<T>::Node(char ch, bool f){
	c = ch;
	fim = f;
}

template <class T>
bool Node<T>::getFim(){
	return fim;
}

template <class T>
Node<T>* Node<T>::addFilho(char ch, bool f){
	for(unsigned int i=0; i < children.size(); i++){
		if(children[i]->getChar() == ch){
			children[i]->setFim(f);
			return children[i];
		}
	}
	Node<T> *aux = new Node { ch, f };
	children.push_back(aux);
	return aux;
}

template <class T>
Node<T>* Node<T>::getFilho(char ch){
	for(unsigned int i = 0; i < children.size(); i++){
		if(children[i]->getChar() == ch)
			return children[i];
	}
	return 0;
}

template<class T>
inline void Node<T>::addEdge(Edge<T>* edge) {
	this->EdgeSet.push_back(edge);
}

template<class T>
inline std::vector<Edge<T> *> Node<T>::getEdges() {
	return this->EdgeSet;
}

//TRIE

template <class T>
Trie<T>::Trie(){
	root = new Node<T> { };
}

template <class T>
void Trie<T>::insertWord(std::string word, Edge<T> *edge){
	Node<T> *aux = root;

	for(unsigned int i=0; i < word.length()-1; i++){
		aux = aux->addFilho(word[i], false);
	}
	aux = aux->addFilho(word[word.length()-1], true);
	aux->addEdge(edge);
}

template <class T>
std::vector<Edge<T> *> Trie<T>::search(std::string word) {
	Node<T> *aux = root;

	std::vector<Edge<T> *> empty { };

	for(unsigned int i = 0; i < word.length()-1; i++){
		aux = aux->getFilho(word[i]);
		if(aux == 0) return empty;
	}
	aux = aux->getFilho(word[word.length()-1]);
	if(aux && aux->getFim())	return aux->getEdges();
	else return empty;
}

#endif /* TRIE_H_ */
