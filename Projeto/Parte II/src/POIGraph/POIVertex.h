#ifndef TOURMATEAPP_POIVERTEX_H
#define TOURMATEAPP_POIVERTEX_H

#include <vector>
#include <queue>
#include "POIEdge.h"

using namespace std;

class POIVertex {
    int id;
    vector<POIEdge> adj;		// outgoing edges

    void addEdge(const int &dest, double dist, queue<Vertex<coord>*> path) {
        adj.push_back(POIEdge(dest, dist, path));
    }

public:
    POIVertex(int id)  {
        this->id = id;
    }

    friend class POIGraph;
};


#endif //TOURMATEAPP_POIVERTEX_H
