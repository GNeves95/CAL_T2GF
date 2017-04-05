//============================================================================
// Name        : projcal1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Graph.h"
#include "graphviewer.h"
using namespace std;

int main() {
	GraphViewer *gv = new GraphViewer(200,400,false);
	gv->createWindow(175,375);
	gv->addNode(0, 7, 7);
	gv->setVertexColor(0,"Red");
	getchar();
	gv->closeWindow();
	return 0;
}
