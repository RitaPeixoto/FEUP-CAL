#include "AlgorithmAnalysis.h"

using namespace std::chrono;
void comparePath(Graph<coord> &g, int idStart, int idEnd){
    system("cls");

    cout << "Execution of the algorithms in a small path"<<endl;
    auto t0 = duration_cast<microseconds>(system_clock::now().time_since_epoch());
    queue<Vertex<coord>*> path = g.dijkstraShortestPath(idStart, idEnd);
    auto t1 = duration_cast<microseconds>(system_clock::now().time_since_epoch());
    queue<Vertex<coord>*> path2 = g.aStarShortestPath(idStart, idEnd);
    auto t2 = duration_cast<microseconds>(system_clock::now().time_since_epoch());

    cout << "Dijkstra execution time: "<< t1.count() - t0.count()<< " microseconds."<<endl;
    cout << "AStar execution time: "<< t2.count() - t1.count()<< " microseconds."<<endl;


    GraphViewer* gv = createMapViewer(g, false);
    showTestPath(gv, path);
    GraphViewer* gv1 = createMapViewer(g, false);
    showTestPath(gv1, path2);

    cout << endl << "Insert any key to return to the menu..." << endl;
    char input;
    cin >> input;

    gv->closeWindow();
    gv1->closeWindow();
}

void compareBidirectional(Graph<coord> &g){
    system("cls");

    int idStart = 27772, idEnd = 28445;


    cout << "Execution of the bidirectional algorithms"<<endl;
    auto t0 = duration_cast< microseconds >(system_clock::now().time_since_epoch());
    queue<Vertex<coord>*> path = g.biDirDijkstraShortestPath(idStart, idEnd);
    auto t1 = duration_cast< microseconds >(system_clock::now().time_since_epoch());
    queue<Vertex<coord>*> path2 = g.biDirAStarShortestPath(idStart, idEnd);
    auto t2 = duration_cast< microseconds >(system_clock::now().time_since_epoch());

    cout << "Bidirectional Dijkstra execution time: " << t1.count() - t0.count()<< " microseconds." << endl;
    cout << "Bidirectional AStar execution time: " << t2.count() - t1.count()<< " microseconds." << endl;

    GraphViewer* gv = createMapViewer(g, false);
    showTestPath(gv, path);

    GraphViewer *gv1 = createMapViewer(g, false);
    showTestPath(gv1, path2);

    cout << endl << "Insert any key to return to the menu..." << endl;
    char input;
    cin >> input;

    gv->closeWindow();
    gv1->closeWindow();
}


void compareDFSBFS(Graph<coord> &g){
    system("cls");
    int idStrt = 30413;
    cout << "Execution of the depth first and breath first search algorithms"<<endl;
    auto t0 = duration_cast< microseconds >(system_clock::now().time_since_epoch());
    vector<Vertex<coord>*> bfsPoints = g.bfsAll(idStrt);
    auto t1 = duration_cast< microseconds >(system_clock::now().time_since_epoch());
    vector<Vertex<coord>*> dfsPoints = g.dfs(idStrt);
    auto t2 = duration_cast< microseconds >(system_clock::now().time_since_epoch());

    cout << "BFS found " << bfsPoints.size() << " nodes from source " << idStrt << " in " << t1.count()- t0.count()<< " microseconds."<< endl;
    cout << "DFS found "<< dfsPoints.size() << " nodes from source " << idStrt << " in " << t2.count()- t1.count() << " microseconds."<< endl;
    
    cout << endl << "Insert any key to return to the menu..."<<endl;
    char input;
    cin >> input;

}

void compareAllGrid() {
    system("cls");

    Graph<coord> graph;
    readNodesFile(graph, "../Resources/GridGraphs/16x16/nodes.txt");
    readEdgesFile(graph, false, "../Resources/GridGraphs/16x16/edges.txt");
    graph.floydWarshallShortestPath();

    int idStrt = 0, idEnd = 288;
    cout << "Execution of the algorithms in a small path"<<endl;
    auto t0 = duration_cast<microseconds>(system_clock::now().time_since_epoch());
    queue<Vertex<coord>*> path = graph.dijkstraShortestPath(idStrt, idEnd);
    auto t1 = duration_cast< microseconds >(system_clock::now().time_since_epoch());
    queue<Vertex<coord>*> path2 = graph.aStarShortestPath(idStrt, idEnd);
    auto t2 = duration_cast< microseconds >(system_clock::now().time_since_epoch());
    vector<coord> path3 = graph.getfloydWarshallPath(idStrt, idEnd);
    auto t3 = duration_cast< microseconds >(system_clock::now().time_since_epoch());


    cout << "Dijkstra execution time: "<< t1.count()- t0.count() << " microseconds."<<endl;
    cout << "AStar execution time: "<< t2.count()- t1.count() << " microseconds."<<endl;
    cout << "Floyd-Warshall execution time: "<< t3.count()- t2.count() << " microseconds."<<endl;

    GraphViewer* gv = createMapViewer(graph, false);
    showTestPath(gv, path);

    GraphViewer* gv1 = createMapViewer(graph, false);
    showTestPath(gv1, path2);


    cout << endl << "Insert any key to return to the menu..."<<endl;
    char input;
    cin >> input;

    gv->closeWindow();
    gv1->closeWindow();
}