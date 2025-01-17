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
#include <ctime>
#include "Address.h"
#include "Graph.h"
#include "graphviewer.h"
using namespace std;



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

int main() {

	Graph<Address> g { };
	Graph<Address> g1 { };
	//Graph<Address> g2 { };
	//clock_t begin { }, end { };
	time_t timev { time(0) };
	tm * t { localtime( &timev)};



	times << " _______________________" << endl;
	times << "|" << 1900 + t->tm_year << "/" << t->tm_mon << "/" << t->tm_mday << " " << t->tm_hour << ":" << t->tm_min << "\t|" <<endl;
	times << "|_______________________|" << endl;

	//vector<Edge<Address> *> primresult { };
	bool running { true };
	int posVertice { }, posDest { };
	Vertex<Address> * posVerSearch { };

	GraphViewer *gv = new GraphViewer { width, height, false };
	gv->createWindow(width,height);

	//g.createGraph(gv);
	g.createGraph(gv);
	do{
		char a { };
		gv->rearrange();
		cout << "\t\tMenu: " << endl;
		cout << "\n\t1.Create Node" << endl;
		cout << "\t2.Create Link" << endl;
		cout << "\t3.Delete Node" << endl;
		cout << "\t4.Delete Link" << endl;
		cout << "\t5.Close Road" << endl; //<--
		cout << "\t6.Open Road" << endl;
		cout << "\t7.Use Dijkstra" << endl;
		cout << "\t8.Search Exact Road" << endl;
		cout << "\t9.Search Approximate Road" << endl;
		cout << "\tq.Exit" << endl;
		//running = false;
		cin >> a;
		//system("CLS");
		//a = '7';

		for(unsigned int i = 0; i < g.getVertexSet().size(); i++){
			for(unsigned int j = 0; j < g.getVertexSet()[i]->getAdj().size(); j++){
				if(g.getVertexSet()[i]->getAdj()[j].getClosed() == false){
					gv->setEdgeColor(g.getVertexSet()[i]->getAdj()[j].getId(), BLACK);
				}
				else{
					gv->setEdgeColor(g.getVertexSet()[i]->getAdj()[j].getId(), RED);
				}
			}
		}
		string road { };

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
			g1 = g.clone();
			cout << "Choose source: ";
			posVertice = numberPicker(g1);
			//posVertice = 1;
			cout << "Choose destiny: ";
			posDest = numberPicker(g1);
			//posDest = 2;
			g1.setShortestPaths(g1.getVertexSet()[posDest]);
			g1.showPaths(g1.getVertexSet()[posVertice], g1.getVertexSet()[posDest], gv);
			//g.setShortestPaths(posVertice);
			//g.showPaths(posVertice, posDest, gv);
			break;
		case '8':
			cout << "Road to search for: ";
			cin >> road;
			g1 = g.clone();
			posVerSearch = g1.searchExactRoadDest(road);
			if(posVerSearch != 0){
				cout << "Choose destiny: ";
				posDest = numberPicker(g1);
				g1.setShortestPaths(g1.getVertexSet()[posDest]);
				g1.showPaths(posVerSearch, g1.getVertexSet()[posDest], gv);
			}
			break;
		case '9':
			cout << "Road to search for: ";
			cin >> road;
			g1 = g.clone();
			posVertice = g1.searchAproxRoadDest(road);
			if(posVertice != -1){
				cout << "Choose destiny: ";
				posDest = numberPicker(g1);
				g1.setShortestPaths(g1.getVertexSet()[posDest]);
				g1.showPaths(g1.getVertexSet()[posVertice], g1.getVertexSet()[posDest], gv);
			}
			//break;
			break;
		case 'q':
			g.saveGraph();
			running = false;
			break;
		default:
			break;
		}

		//cerr << times.str();
	} while(running);

	std::ofstream outfile { };

	outfile.open("records.log", std::ios_base::app);
	outfile << times.str();
	outfile.close();

	gv->closeWindow();
	return 0;
}
