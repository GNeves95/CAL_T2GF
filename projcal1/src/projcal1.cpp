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

//constexpr int height { 400 };
//constexpr int width { 200 };

/*constexpr float maxLatitude = 42.5;
constexpr float minLatitude = 36.8;

constexpr float maxLongitude = -6.1;
constexpr float minLongitude = -10.3;

float lon2coord(float x){
	return (x-minLongitude)/(maxLatitude-minLongitude);
}

float lat2coord(float x){
	return (x-maxLongitude)/(minLatitude-maxLongitude);
}
 */

unsigned int numberPicker(Graph<Address> graf){

	unsigned int a { };
	while (true){
		for (unsigned int i = 1; i <= graf.getVertexSet().size(); i++){
			cout << "Index: " << i << " " << graf.getVertexSet()[i-1]->getInfo().getNome() << endl;
		}
		cin >> a;
		if (a > 0 && a <= graf.getVertexSet().size())
			return a - 1;
	}
	return -1;
}

void printGraph(GraphViewer *gv, Graph<Address> g){
	gv->rearrange();
}

int main() {

	Graph<Address> g { };
	Graph<Address> g1 { };
	Graph<Address> g2 { };

	vector<Edge<Address> *> primresult { };
	bool running { true };
	unsigned int posVertice { }, posDest { };

	GraphViewer *gv = new GraphViewer { width, height, false };
	gv->createWindow(width,height);

	g.createGraph(gv);
	do{
		char a { };
		printGraph(gv,g);
		cout << "\t\tMenu: " << endl;
		cout << "\n\t1.Create Node" << endl;
		cout << "\t2.Create Link" << endl;
		cout << "\t3.Delete Node" << endl;
		cout << "\t4.Delete Link" << endl;
		cout << "\t5.Close Road" << endl; //<--
		cout << "\t6.Open Road" << endl;
		cout << "\t7.Use Dijkstra" << endl;
		//running = false;
		//cin >> a;
		//system("CLS");
		a = '7';
		switch (a){
		case '1':
			g.createVertex(gv);
			break;
		case '2':
			g.createEdge(gv);
			break;
		case '3':
			g.deleteVertex(gv);
			break;
		case '4':
			g.deleteEdge(gv);
			break;
		case '5':
			g.closeRoad(gv);
			break;
		case '6':
			g.openRoad(gv);
			break;
		case '7':
			//posVertice = numberPicker(g);
			cout << "Choose source: ";
			posVertice = 0;//numberPicker(g);
			cout << "Choose destiny: ";
			posDest = 1;//numberPicker(g);
			g1 = g.clone();
			g1.setShortestPaths(posVertice);
			g1.showPaths(posVertice, posDest, gv);
			break;
		case '8':
			//primresult = g.calculatePrim();
			break;
		case '9':
			posVertice = numberPicker(g);
			//g.leastUsageOfCable(primresult, posVertice);
			break;
		case 'q':
			g.saveGraph();
			running = false;
			break;
		default:
			break;
		}
	} while(running);



	gv->closeWindow();
	return 0;
}
