#include "ReadFiles.h"


Graph<coord> readMap(bool bidir){
    //lê todos os ficheiros e guarda toda a informaçao necessária
    Graph<coord> graph;

    readNodesFile(graph, "../resources/porto_strong_nodes_xy.txt");
    readEdgesFile(graph, bidir, "../resources/porto_strong_edges.txt");
    vector<int> tags = readTags(graph);
    readMetroFile(graph);
    graph.initializeRealPOIs();

    return graph;
}

void readNodesFile(Graph<coord> &graph, string nodesfile){
    //ler o ficheiros de nodes 
    ifstream nodes;
    string line;
    int numNodes;

    nodes.open(nodesfile);

    getline(nodes, line);
    numNodes = stoi(line);

    for (int i = 0; i < numNodes; i++) {
        getline(nodes, line);
        int id;
        double x, y;
        size_t pos = line.find(',');
        id = stoi(line.substr(1, pos));
        line.erase(0, pos + 1);
        pos = line.find(',');
        x = stof(line.substr(0, pos));
        line.erase(0, pos + 1);
        pos = line.find(')');
        y = stof(line.substr(0, pos));
        graph.addVertex(id, make_pair(x, y));
    }
    nodes.close();
}

void readEdgesFile(Graph<coord> &graph, bool bidir, string edgesfile){
    //ler o ficheiro de edges
    ifstream edges;
    string line;

    edges.open(edgesfile);

    getline(edges, line);
    int numEdges = stoi(line);
    for (int i = 0; i < numEdges; i++) {
        getline(edges, line);
        int n1, n2;
        size_t pos = line.find(',');
        n1 = stoi(line.substr(1, pos));
        line.erase(0, pos + 1);
        pos = line.find(')');
        n2 = stoi(line.substr(0, pos));

        Vertex<coord>* v1 = graph.findVertex(n1);
        Vertex<coord>* v2 = graph.findVertex(n2);
        double weight = graph.euclideanDistance(v1, v2);
        if(bidir)
            graph.addBiDirEdge(v1->getId(), v2->getId(), weight);
        else
            graph.addEdge(v1->getId(), v2->getId(), weight);
    }
    edges.close();

}

vector<int> readTags(Graph<coord> &g) {
    string tagfile = "../resources/tags.txt";

    vector<int> res;
    ifstream file;
    string line;
    int numTypes;

    file.open(tagfile);

    getline(file, line);
    numTypes = stoi(line);
    for (int i = 0; i < numTypes; i++) {
        string type;
        getline(file, type);
        type.erase(0, 8);
        int numNodes;
        getline(file, line);
        numNodes = stoi(line);
        for(int j = 0; j < numNodes; j++) {
            getline(file, line);
            Vertex<coord>* v = g.findVertex(stoi(line));
            v->setType(type);
            int dur = generateRandomTime(v);
            v->setDuration(dur);
            res.push_back(stoi(line));
        }
    }
    return res;
}

void readMetroFile(Graph<coord> &g) {
    ifstream file;
    string line;
    int numStations;

    file.open("../resources/metro_routes.txt");
    
    getline(file, line);
    numStations = stoi(line);

    for(int i = 0; i < numStations; i++){
        getline(file, line);
        size_t pos = line.find(',');

        int ID = stoi(line.substr(1, pos));

        line.erase(0, pos + 2);

        pos = line.find(',');
        string stationName = line.substr(0, pos);
        line.erase(0, pos + 2);

        int numStop = stoi(line.substr(0, pos));
       
        MetroStation ms(ID, stationName, numStop);
        g.addMetroStation(ms);
    }
}


int generateRandomTime(Vertex<coord>* v) {
    //if we want we can make this random

    int value = checkRealPoi(v->getId());
    if(value != 0) return value;

    if(v->getType() == "information") return 15;

    else if(v->getType() == "hotel") return 45;

    else if(v->getType() == "attraction") return 20;

    else if(v->getType() == "viewpoint") return 30;

    else if(v->getType() == "guest_house") return 45;

    else if(v->getType() == "picnic_site") return 30;

    else if(v->getType() == "artwork") return 20;

    else if(v->getType() == "camp_site") return 45;

    else if(v->getType() == "museum") return 90;

    return 10;
}

int checkRealPoi(int id){
    if(id == 1144) return 30;
    if(id == 41230) return 30;
    if(id == 28445) return 45;
    if(id == 14820) return 30;
    if(id == 24107) return 15;
    if(id == 18083) return 30;
    if(id == 41920) return 60;
    if(id == 3295) return 30;
    if(id == 35225) return 15;
    if(id == 17238) return 45;
    if(id == 36869) return 45;
    if(id == 30413) return 15;
    if(id == 17001) return 15;
    return 0;
}