#ifndef TOURMATEAPP_GRAPHVIEW_H
#define TOURMATEAPP_GRAPHVIEW_H


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <queue>
#include "graphviewer.h"
#include "../UserInteraction/ClientInfo.h"


GraphViewer* createMapViewer(const Graph<coord> &g, bool showPoi);

void showRealPOIPath(GraphViewer* gv, const Graph<coord> &g, queue<Vertex<coord>*> path, vector<int> visitedPoi);

void showPath(GraphViewer* gv, queue<Vertex<coord>*> path, vector<int> visitedPoi);

void showTestPath(GraphViewer* gv, queue<Vertex<coord>*> path);

void showPOI(GraphViewer* gv, const vector<Vertex<coord>*> &points, const int &orig);

void showMetroLine(GraphViewer* gv, Graph<coord> g);

void showPathWithMetro(GraphViewer* gv, Graph<coord> g, queue<Vertex<coord>*> path1, queue<Vertex<coord>*> path2, vector<int> visitedPoi,  MetroStation origStop, MetroStation endStop);




#endif //TOURMATEAPP_GRAPHVIEW_H
