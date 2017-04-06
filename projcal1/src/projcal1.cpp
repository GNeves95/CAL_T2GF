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
#include "Address.h"
#include "Graph.h"
#include "graphviewer.h"
using namespace std;

constexpr int height { 400 };
constexpr int width { 200 };

constexpr float maxLatitude = 42.5;
constexpr float minLatitude = 36.8;

constexpr float maxLongitude = -6.1;
constexpr float minLongitude = -10.3;

float lon2coord(float x){
	return (x-minLongitude)/(maxLatitude-minLongitude);
}

float lat2coord(float x){
	return (x-maxLongitude)/(minLatitude-maxLongitude);
}

int main() {

	Graph<Address> g { };

	g.createGraph();
	vector<Edge<Address> *> primresult { };
	bool running { true };

	GraphViewer *gv = new GraphViewer { width, height, false };
	gv->createWindow(width,height);

	do{
		cout << "\t\tMenu: " << endl;
		cout << "\n\t1.Create Node" << endl;
		cout << "\t2.Create Link" << endl;
		cout << "\t3.Delete Node" << endl;
		cout << "\t4.Delete Link" << endl;
		cout << "\t5.Load Graph" << endl;
		cout << "\t6.Save Graph" << endl;
		cout << "\t7.Use Dijkstra" << endl;
		running = false;
	} while(running);

	gv->addNode(0, 25, 25);
	stringstream ss { };
	ss << "" << ": " << "";
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
