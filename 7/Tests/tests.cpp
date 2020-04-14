#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <random>
#include <time.h>
#include <chrono>
#include "Graph.h"

using namespace std;
using testing::Eq;


Graph<int> createTestGraph() {
	Graph<int> myGraph;

	for(int i = 1; i < 8; i++)
		myGraph.addVertex(i);

	myGraph.addBidirectionalEdge(1, 2, 2);
	myGraph.addBidirectionalEdge(1, 4, 7);
	myGraph.addBidirectionalEdge(2, 4, 3);
	myGraph.addBidirectionalEdge(2, 5, 5);
	myGraph.addBidirectionalEdge(3, 1, 2);
	myGraph.addBidirectionalEdge(3, 6, 5);
	myGraph.addBidirectionalEdge(4, 3, 1);
	myGraph.addBidirectionalEdge(4, 5, 1);
	myGraph.addBidirectionalEdge(4, 7, 4);
	myGraph.addBidirectionalEdge(5, 7, 2);
	myGraph.addBidirectionalEdge(6, 4, 3);
	myGraph.addBidirectionalEdge(7, 6, 4);

	return myGraph;
}



TEST(CAL_FP07, testPrim) {
	Graph<int> graph = createTestGraph();
	vector<Vertex<int>* > res = graph.calculatePrim();

	stringstream ss;
	for(auto v : res) {
		ss << v->getInfo() << "<-";
		if ( v->getPath() != nullptr )
			ss << v->getPath()->getInfo();
		ss << "|";
	}

	cout << ss.str() << endl;

	EXPECT_EQ("1<-|2<-1|3<-1|4<-3|5<-4|6<-4|7<-5|", ss.str());
}



TEST(CAL_FP07, testKruskal) {
	Graph<int> graph = createTestGraph();
	vector<Vertex<int>* > res = graph.calculateKruskal();

	stringstream ss;
	for(auto v : res) {
		ss << v->getInfo() << "<-";
		if ( v->getPath() != nullptr )
			ss << v->getPath()->getInfo();
		ss << "|";
	}

	cout << ss.str() << endl;

	EXPECT_EQ("1<-|2<-1|3<-1|4<-3|5<-4|6<-4|7<-5|", ss.str());
	// Nota: a melhorar esta verficacao (o que interessa sao as arestas serem selecionadas)

}


