//============================================================================
// Name        : projcal1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include "Graph.h"
#include "graphviewer.h"
using namespace std;

int main() {
	int id { 0 };
	string nome = "Caminha";
	GraphViewer *gv = new GraphViewer { 225, 425, false };
	gv->createWindow(225,425);
	gv->addNode(0, 25, 25);
	stringstream ss { };
	ss << id << ": " << nome;
	gv->setVertexLabel(0, ss.str());
	gv->setVertexColor(0,"red");
	getchar();

	gv->addNode(1, 125, 325);
	ss.str(string());
	ss << "1: Vila Real de Santo António";
	gv->setVertexLabel(1,ss.str());
	gv->setVertexColor(1, "BLACK");
	gv->addEdge(0,0,1,EdgeType::DIRECTED);
	gv->setEdgeColor(0,"red");
	gv->setEdgeLabel(0,"A1");
	gv->rearrange();
	getchar();

	gv->closeWindow();
	return 0;
}
