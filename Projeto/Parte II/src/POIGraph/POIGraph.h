#ifndef TOURMATEAPP_POIGRAPH_H
#define TOURMATEAPP_POIGRAPH_H

#include <unordered_map>
#include <iostream>
#include "POIVertex.h"

using namespace std;

class POIGraph {
    vector<POIVertex*> vertexSet;    // vertex set
    unordered_map<int, int> vertexMap; //<id, index>

public:
    POIVertex *findVertex(const int &id) const {
        auto it = vertexMap.find(id);
        if(it == vertexMap.end())
            return nullptr;
        return vertexSet.at(it->second);
    }
    bool addVertex(const int &id) {
        if ( findVertex(id) != nullptr)
            return false;
        vertexSet.push_back(new POIVertex(id));
        vertexMap.insert(make_pair(id, vertexSet.size() - 1));

        return true;
    }
    bool addEdge(const int &sourc, const int &dest, double w, queue<Vertex<coord>*> path) {
        auto v1 = findVertex(sourc);
        auto v2 = findVertex(dest);
        if (v1 == nullptr || v2 == nullptr)
            return false;
        for(POIEdge e: v1->adj){
            if(e.getDest() == dest)
                return false;
        }
        v1->addEdge(dest,w, path);
        return true;
    }
    double getDist(Graph<coord> &g, const int &source, const int &dest, bool biDir) {
        POIVertex* v1 = findVertex(source);
        if(v1 == nullptr)
            return -1;
        for(POIEdge edge: v1->adj) {
            if(edge.destID == dest)
                return edge.dist;
        }

        if(!g.bfs(source, dest).empty()) {
            queue<Vertex<coord>*> path;
            if(biDir) path = g.biDirAStarShortestPath(source, dest);
            else path = g.aStarShortestPath(source, dest);

            double dist = g.distancePath(path);

            v1->addEdge(dest, dist, path);
            return dist;
        }
        return -1;
    }
    queue<Vertex<coord>*> getPath(Graph<coord> &g, const int &source, const int &dest, bool biDir) {

        POIVertex* v1 = findVertex(source);
        if(v1 == nullptr)
            return queue<Vertex<coord>*>();
        for(const POIEdge& edge: v1->adj) {
            if(edge.destID == dest)
                return edge.path;
        }

        if(!g.bfs(source, dest).empty()) {

            queue<Vertex<coord>*> path;
            if(biDir) path = g.biDirAStarShortestPath(source, dest);
            else path = g.aStarShortestPath(source, dest);

            double dist = g.distancePath(path);

            v1->addEdge(dest, dist, path);
            return path;
        }
        return queue<Vertex<coord>*>();
    }
};

#endif //TOURMATEAPP_POIGRAPH_H
