#include "GraphView.h"


GraphViewer* createMapViewer(const Graph<coord> &g, bool showPoi) {
    double height = g.getMaxY() - g.getMinY();
    double width = g.getMaxX() - g.getMinX();

    int graphHeight, graphWidth;
    if(width/height < 2) {
        graphHeight = 600;
        graphWidth = (width * graphHeight) / height;
    }
    else {
        graphWidth = 1000;
        graphHeight = (height * graphWidth) / width;
    }

    auto *gv = new GraphViewer(graphWidth, graphHeight, false);
    gv->createWindow(graphWidth, graphHeight);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");
    gv->defineEdgeCurved(false);

    for(Vertex<coord>* vertex: g.getVertexSet()) {
        double y = (vertex->getInfo().second - g.getMinY()) / height;
        double x = (vertex->getInfo().first - g.getMinX()) / width;

        gv->addNode(vertex->getId(), (int) (x * graphWidth), (int) (y * graphHeight));
        gv->setVertexSize(vertex->getId(), 1);
    }

    if(showPoi) {
        for (auto i: g.getRealPOIs()) {
            Vertex<coord> *vertex = g.findVertex(i.first);
            gv->setVertexColor(i.first, "orange");
            gv->setVertexLabel(i.first, i.second + "-" + to_string(vertex->getDuration()) + "min");
            gv->setVertexSize(i.first, 10);
        }
    }

    gv->rearrange();
    return gv;
}

void showRealPOIPath(GraphViewer* gv, const Graph<coord> &g, queue<Vertex<coord>*> path, vector<int> visitedPoi) {
    int i = 0;
    int idEnd = path.front()->getId(), idStart;
    int counter = 3;

    gv->defineEdgeColor("yellow");
    while (!path.empty()) {
        Vertex<coord> *vertex = path.front();
        path.pop();

        if (!path.empty()) {
            if (counter == 0) {
                gv->addEdge(i, path.front()->getId(), vertex->getId(), EdgeType::DIRECTED);
                gv->setEdgeThickness(i, 5);
                counter = 3;
            } else {
                gv->addEdge(i, path.front()->getId(), vertex->getId(), EdgeType::UNDIRECTED);
                gv->setEdgeThickness(i, 5);
                counter--;
            }
            i++;
        }

        if (path.empty())
            idStart = vertex->getId();
        else if (find(visitedPoi.begin(), visitedPoi.end(), vertex->getId()) != visitedPoi.end()) {
            gv->setVertexColor(vertex->getId(), "red");
            gv->setVertexLabel(vertex->getId(), g.realPOIName(vertex->getId()) + "-" + to_string(vertex->getDuration()) + "min");
            gv->setVertexSize(vertex->getId(), 10);
        }
    }

    gv->setVertexColor(idEnd, "yellow");
    gv->setVertexLabel(idEnd, g.realPOIName(idEnd));
    gv->setVertexSize(idEnd, 10);


    gv->setVertexColor(idStart, "green");
    gv->setVertexLabel(idStart, g.realPOIName(idStart));
    gv->setVertexSize(idStart, 10);


    gv->rearrange();
}



void showPath(GraphViewer* gv, queue<Vertex<coord>*> path, vector<int> visitedPoi) {
    int i = 0;
    int idEnd = path.front()->getId(), idStart;
    int counter = 3;

    gv->defineEdgeColor("yellow");
    while (!path.empty()) {
        Vertex<coord> *vertex = path.front();
        path.pop();

        if (!path.empty()) {
            if (counter == 0) {
                gv->addEdge(i, path.front()->getId(), vertex->getId(), EdgeType::DIRECTED);
                gv->setEdgeThickness(i, 5);
                counter = 3;
            } else {
                gv->addEdge(i, path.front()->getId(), vertex->getId(), EdgeType::UNDIRECTED);
                gv->setEdgeThickness(i, 5);
                counter--;
            }
            i++;
        }

        if (path.empty())
            idStart = vertex->getId();
        else if (find(visitedPoi.begin(), visitedPoi.end(), vertex->getId()) != visitedPoi.end()) {
            gv->setVertexColor(vertex->getId(), "red");
            gv->setVertexLabel(vertex->getId(), vertex->getType() + "-" + to_string(vertex->getDuration()) + "min");
            gv->setVertexSize(vertex->getId(), 10);
        } else if (vertex->getType() != " ") {
            gv->setVertexColor(vertex->getId(), "pink");
            gv->setVertexLabel(vertex->getId(), vertex->getType() + "-" + to_string(vertex->getDuration()) + "min");
            gv->setVertexSize(vertex->getId(), 5);
        }
    }
    gv->setVertexColor(idEnd, "yellow");
    gv->setVertexSize(idEnd, 20);
    gv->setVertexColor(idStart, "green");
    gv->setVertexSize(idStart, 20);


    gv->rearrange();

}

void showTestPath(GraphViewer* gv, queue<Vertex<coord>*> path) {
    int i = 0;
    gv->setVertexColor(path.front()->getId(), "yellow");
    gv->setVertexSize(path.front()->getId(), 20);
    gv->setVertexLabel(path.front()->getId(), "End");
    int s = 3;
    while(!path.empty()) {
        Vertex<coord>* vertex = path.front();
        path.pop();

        if(!path.empty()) {
            if(s == 0) {
                gv->addEdge(i, path.front()->getId(), vertex->getId(), EdgeType::DIRECTED);
                s = 3;
            }
            else {
                gv->addEdge(i, path.front()->getId(), vertex->getId(), EdgeType::UNDIRECTED);
                s--;
            }
            gv->setEdgeColor(i, "yellow");
            gv->setEdgeThickness(i, 10);
            i++;
        }

        if(path.empty()) {
            gv->setVertexColor(vertex->getId(), "green");
            gv->setVertexSize(vertex->getId(), 20);
            gv->setVertexLabel(vertex->getId(), "Start");
        }
    }

    gv->rearrange();
}

void showPOI(GraphViewer* gv, const vector<Vertex<coord>*>& points, const int &orig) {
    for(int i = 1; i < points.size(); i++) {
        gv->setVertexColor(points.at(i)->getId(), "red");
        gv->setVertexLabel(points.at(i)->getId(), points.at(i)->getType() +" - " + to_string(i+1));
        gv->setVertexSize(points.at(i)->getId(), 10);
    }
    if(orig != -1) {
        gv->setVertexColor(orig, "green");
        gv->setVertexSize(orig, 15);
        gv->setVertexLabel(orig, "You're here: " + to_string(1));
    }
    gv->rearrange();
}

void showMetroLine(GraphViewer* gv, Graph<coord> g) {
    for(int i = 1; i < g.getMetroStations().size(); i++){
        gv->addEdge(i, g.findStationID(i), g.findStationID(i+1), EdgeType::UNDIRECTED);
        gv->setEdgeColor(i, "yellow");
        gv->setEdgeThickness(i, 5);
        gv->setVertexLabel(g.findStationID(i), g.getMetroStations().at(i).getStationName());
        gv->setVertexSize(g.findStationID(i), 5);
    }
    gv->setVertexSize(g.findStationID(g.getMetroStations().size()), 5);
}


void showPathWithMetro(GraphViewer* gv, Graph<coord> g, queue<Vertex<coord>*> path1, queue<Vertex<coord>*> path2, vector<int> visitedPoi, MetroStation origStop, MetroStation endStop) {
    int i = 0;
    int idEnd, idStart;
    int counter = 3;

    gv->defineEdgeColor("blue");
    while (!path1.empty()) {
        Vertex<coord> *vertex = path1.front();
        path1.pop();

        if (!path1.empty()) {
            if (counter == 0) {
                gv->addEdge(i, path1.front()->getId(), vertex->getId(), EdgeType::DIRECTED);
                gv->setEdgeThickness(i, 5);
                counter = 3;
            } else {
                gv->addEdge(i, path1.front()->getId(), vertex->getId(), EdgeType::UNDIRECTED);
                gv->setEdgeThickness(i, 5);
                counter--;
            }
            i++;
        }
        else {
            idStart = vertex->getId();
        }

        if (find(visitedPoi.begin(), visitedPoi.end(), vertex->getId()) != visitedPoi.end()) {
            gv->setVertexColor(vertex->getId(), "red");
            gv->setVertexLabel(vertex->getId(), vertex->getType() + "-" + to_string(vertex->getDuration()) + "min");
            gv->setVertexSize(vertex->getId(), 10);
        } else if (vertex->getType() != " ") {
            gv->setVertexColor(vertex->getId(), "pink");
            gv->setVertexLabel(vertex->getId(), vertex->getType() + "-" + to_string(vertex->getDuration()) + "min");
            gv->setVertexSize(vertex->getId(), 5);
        }
    }

    cout << "Stations: " << origStop.getStationName() << " to " << endStop.getStationName() << endl;
    int s = origStop.getStopNum(), increment;
    if (origStop.getStopNum() < endStop.getStopNum())
        increment = 1;
    else
        increment = -1;
    while (s != endStop.getStopNum()) {
        gv->addEdge(i, g.findStationID(s), g.findStationID(s + increment), EdgeType::DIRECTED);
        gv->setEdgeThickness(i, 5);
        gv->setEdgeColor(i, "yellow");
        s += increment;
        i++;
    }

    idEnd = path2.front()->getId();
    while (!path2.empty()) {
        Vertex<coord> *vertex = path2.front();
        path2.pop();

        if (!path2.empty()) {
            if (counter == 0) {
                gv->addEdge(i, path2.front()->getId(), vertex->getId(), EdgeType::DIRECTED);
                gv->setEdgeThickness(i, 5);
                counter = 3;
            } else {
                gv->addEdge(i, path2.front()->getId(), vertex->getId(), EdgeType::UNDIRECTED);
                gv->setEdgeThickness(i, 5);
                counter--;
            }
            i++;
        } else if (find(visitedPoi.begin(), visitedPoi.end(), vertex->getId()) != visitedPoi.end()) {
            gv->setVertexColor(vertex->getId(), "red");
            gv->setVertexLabel(vertex->getId(), vertex->getType() + "-" + to_string(vertex->getDuration()) + "min");
            gv->setVertexSize(vertex->getId(), 10);
        } else if (vertex->getType() != " ") {
            gv->setVertexColor(vertex->getId(), "pink");
            gv->setVertexLabel(vertex->getId(), vertex->getType() + "-" + to_string(vertex->getDuration()) + "min");
            gv->setVertexSize(vertex->getId(), 5);
        }
    }

    gv->setVertexColor(idEnd, "yellow");
    gv->setVertexSize(idEnd, 20);
    gv->setVertexColor(idStart, "green");
    gv->setVertexSize(idStart, 20);

    gv->rearrange();
}
