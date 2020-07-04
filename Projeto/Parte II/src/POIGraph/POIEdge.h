#ifndef TOURMATEAPP_POIEDGE_H
#define TOURMATEAPP_POIEDGE_H

#include <queue>
#include "../Graph/Graph.h"

using namespace std;

class POIEdge {
    int destID;      // destination vertex
    double dist;         // edge weight
    queue<Vertex<coord>*> path;

public:
    POIEdge(int destID, double dist, queue<Vertex<coord>*> path) {
        this->destID = destID;
        this->dist = dist;
        this->path = path;
    }
    int getDest() {
        return destID;
    }
    double getDist() {
        return dist;
    }
    queue<Vertex<coord>*> getPath()  {
        return path;
    }

    friend class POIGraph;
    friend class POIVertex;
};

#endif //TOURMATEAPP_POIEDGE_H
