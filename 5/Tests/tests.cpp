#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <random>
#include <time.h>
#include <chrono>
#include "Graph.h"

using namespace std;
using testing::Eq;


/**
 * Auxiliary functions to tests...
 *
 */
Graph<int> CreateTestGraph() {
    Graph<int> myGraph;

    for(int i = 1; i <= 7; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 2, 2);
    myGraph.addEdge(1, 4, 7);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 5, 5);
    myGraph.addEdge(3, 1, 2);
    myGraph.addEdge(3, 6, 5);
    myGraph.addEdge(4, 3, 1);
    myGraph.addEdge(4, 5, 1);
    myGraph.addEdge(4, 6, 6);
    myGraph.addEdge(4, 7, 4);
    myGraph.addEdge(5, 7, 2);
    myGraph.addEdge(6, 4, 3);
    myGraph.addEdge(7, 6, 4);

    return myGraph;
}

template <typename T1, typename T2>
basic_ostream<char>& operator<<(basic_ostream<char> & strm, const pair<T1, T2>& kvPair)
{
    strm << "(" << kvPair.first << ", " << kvPair.second << ")";
    return strm;
}


void geneateRandomGridGraph(int n, Graph<pair<int,int>> & g) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g.addVertex(make_pair(i,j));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++)
                    if ((di != 0) != (dj != 0) && i+di >= 0 && i+di < n && j+dj >= 0 && j+dj < n)
                        g.addEdge(make_pair(i,j), make_pair(i+di,j+dj), dis(gen));
}

template <class T>
void checkAllPaths(Graph<T> &g, string expected) {
    stringstream ss;
    vector<Vertex<T>* > vs = g.getVertexSet();
    for(unsigned int i = 0; i < vs.size(); i++) {
        ss << vs[i]->getInfo() << "<-";
        if ( vs[i]->getPath() != NULL )
            ss << vs[i]->getPath()->getInfo();
        ss << "|";
    }
    EXPECT_EQ(expected, ss.str());
}

template <class T>
void checkSinglePath(vector<T> path, string expected) {
    stringstream ss;
    for(unsigned int i = 0; i < path.size(); i++)
        ss << path[i] << " ";
    EXPECT_EQ(expected, ss.str());
}

/**
 * Unit tests... must be uncommented to proceed...
 */

/* //Uncomment the test below...
TEST(CAL_FP05, test_unweightedShortestPath) {
    Graph<int> myGraph = CreateTestGraph();

    myGraph.unweightedShortestPath(3);
    checkAllPaths(myGraph, "1<-3|2<-1|3<-|4<-1|5<-2|6<-3|7<-4|");
    checkSinglePath(myGraph.getPathTo(7), "3 1 4 7 ");

    myGraph.unweightedShortestPath(5);
    checkSinglePath(myGraph.getPathTo(6), "5 7 6 ");
}
*/


/* //Uncomment the test below...
TEST(CAL_FP05, test_dijkstra) {
    Graph<int> myGraph = CreateTestGraph();

    myGraph.dijkstraShortestPath(3);
    checkAllPaths(myGraph, "1<-3|2<-1|3<-|4<-2|5<-4|6<-3|7<-5|");

    myGraph.dijkstraShortestPath(1);
    checkAllPaths(myGraph, "1<-|2<-1|3<-4|4<-2|5<-4|6<-4|7<-5|");
    checkSinglePath(myGraph.getPathTo(7), "1 2 4 5 7 ");

    myGraph.dijkstraShortestPath(5);
    checkSinglePath(myGraph.getPathTo(6), "5 7 6 ");

    myGraph.dijkstraShortestPath(7);
    checkSinglePath(myGraph.getPathTo(1), "7 6 4 3 1 ");
}
*/


 /* //Uncomment the test below...
TEST(CAL_FP05, test_performance_dijkstra) {
    for (int n = 10; n <= 100; n += 10) {
        Graph< pair<int,int> > g;
        cout << "Dijkstra generating grid " << n << " x " << n << " ..." << endl;
        geneateRandomGridGraph(n, g);
        cout << "Dijkstra processing grid " << n << " x " << n << " ..." << endl;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                g.dijkstraShortestPath(make_pair(i,j));
        auto finish = std::chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();
        cout << "Dijkstra processing grid " << n << " x " << n << " average time (micro-seconds)=" << (elapsed / (n*n)) << endl;
    }
}
*/


/* //Uncomment the test below...
TEST(CAL_FP05, test_bellmanFord) {
    Graph<int> myGraph = CreateTestGraph();

    myGraph.bellmanFordShortestPath(3);
    checkAllPaths(myGraph, "1<-3|2<-1|3<-|4<-2|5<-4|6<-3|7<-5|");

    myGraph.bellmanFordShortestPath(1);
    checkSinglePath(myGraph.getPathTo(7), "1 2 4 5 7 ");

    myGraph.bellmanFordShortestPath(5);
    checkSinglePath(myGraph.getPathTo(6), "5 7 6 ");

    myGraph.bellmanFordShortestPath(7);
    checkSinglePath(myGraph.getPathTo(1), "7 6 4 3 1 ");
}
*/


/* //Uncomment the test below...
TEST(CAL_FP05, test_floydWarshall) {
    Graph<int> myGraph = CreateTestGraph();
    myGraph.floydWarshallShortestPath();
    checkSinglePath(myGraph.getfloydWarshallPath(1, 7), "1 2 4 5 7 ");
    checkSinglePath(myGraph.getfloydWarshallPath(5, 6), "5 7 6 ");
    checkSinglePath(myGraph.getfloydWarshallPath(7, 1), "7 6 4 3 1 ");
}
*/

