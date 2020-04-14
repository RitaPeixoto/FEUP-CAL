#include <cstdio>
#include "graphviewer.h"
#include <fstream>
//#include <string>
#include<iostream>
#include <sstream>

using namespace std;
void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{
// TODO: Implement here exercise 1!
//alinea a
    GraphViewer *gv = new GraphViewer(600, 600, true);
    gv->createWindow(600, 600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");
//alinea b
    gv->addNode(0);
    gv->addNode(1);
    gv->rearrange();
    gv->addEdge(0,0,1,EdgeType::UNDIRECTED);
    gv->removeNode(1);
    gv->addEdge(0,0,2,EdgeType::UNDIRECTED);
    gv->addNode(2);
    gv->rearrange();
    gv->setVertexLabel(2, "Isto e um no");
    gv->setEdgeLabel(0, "Isto e uma aresta");
    gv->setVertexColor(2, "green");
    gv->setEdgeColor(0, "yellow");
    gv->setBackground("background.jpg");
}

void exercicio2()
{
// TODO: Implement here exercise 2!
//alinea a
    GraphViewer *gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    gv->addNode(0,300,50);
    gv->addNode(1,318,58);
    gv->addNode(2,325,75);
    gv->addNode(3,318,93);
    gv->addNode(4,300,100);
    gv->addNode(5,282,93);
    gv->addNode(6,275,75);
    gv->addNode(7,282,58);
    gv->addNode(8,150,200);
    gv->addNode(9,300,200);
    gv->addNode(10,450,200);
    gv->addNode(11,300,400);
    gv->addNode(12,200,550);
    gv->addNode(13,400,550);
//alinea b
    gv->addEdge(0, 0, 1,EdgeType::UNDIRECTED);
    gv->addEdge(1, 1, 2,EdgeType::UNDIRECTED);
    gv->addEdge(2, 2, 3,EdgeType::UNDIRECTED);
    gv->addEdge( 3, 3, 4,EdgeType::UNDIRECTED);
    gv->addEdge(4, 4, 5,EdgeType::UNDIRECTED);
    gv->addEdge(5, 5, 6,EdgeType::UNDIRECTED);
    gv->addEdge(6, 6, 7,EdgeType::UNDIRECTED);
    gv->addEdge(7, 7, 0,EdgeType::UNDIRECTED);
    gv->addEdge(8, 4, 9,EdgeType::UNDIRECTED);
    gv->addEdge(9, 9, 8,EdgeType::UNDIRECTED);
    gv->addEdge(10, 9, 10,EdgeType::UNDIRECTED);
    gv->addEdge(11, 9, 11,EdgeType::UNDIRECTED);
    gv->addEdge(12, 11, 12,EdgeType::UNDIRECTED);
    gv->addEdge(13, 11, 13,EdgeType::UNDIRECTED);
//alinea c e d
    while(true){
        gv->removeNode(12);
        gv->removeNode(13);
        gv->addNode(14, 250, 550);
        gv->addNode(15, 350, 550);
        gv->removeEdge(12);
        gv->removeEdge(13);
        gv->addEdge(12, 11, 14, EdgeType::UNDIRECTED);
        gv->addEdge(13, 11, 15, EdgeType::UNDIRECTED);
        Sleep(1000);
        gv->rearrange();
        gv->removeNode(14);
        gv->removeNode(15);
        gv->addNode(12, 200, 550);
        gv->addNode(13, 400, 550);
        gv->removeEdge(12);
        gv->removeEdge(13);
        gv->addEdge(12, 11, 12, EdgeType::UNDIRECTED);
        gv->addEdge(13, 11, 13, EdgeType::UNDIRECTED);
        Sleep(1000);
        gv->rearrange();
    }

}

void exercicio3()
{
// TODO: Implement here exercise 3!
// To read map files, use relative paths:
// Vertices data: "../resources/mapa1/nos.txt"
// Edges data: "../resources/mapa1/arestas.txt"
// ...
    GraphViewer * gv = new GraphViewer(600, 600, false);
    gv->setBackground("../background.jpg");
    gv->createWindow(600, 600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    ifstream nodes;
    ifstream edges;
    string line;



    nodes.open("../resources/mapa1/nos.txt");
    edges.open("../resources/mapa1/arestas.txt");

    while(getline(nodes, line)) {
        int id, x, y;
        size_t pos = 0;
        pos = line.find(";");
        id = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        pos = line.find(";");
        x = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        y = stoi(line);
        gv->addNode(id, x, y);
    }
    nodes.close();
    while(getline(edges, line)) {
        int id, n1, n2;
        size_t pos = 0;
        pos = line.find(";");
        id = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        pos = line.find(";");
        n1 = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        n2 = stoi(line);
        gv->addEdge(id, n1, n2, EdgeType::UNDIRECTED);
    }
    edges.close();

    gv->rearrange();
}

int main() {
    /*
     * Uncomment the line below to run Exercise 1
     */
    //exercicio1();

    /*
      * Uncomment the line below to run Exercise 2
      */
    //exercicio2();

    /*
      * Uncomment the line below to run Exercise 3
      */
	//
	exercicio3();

	getchar();
    return 0;
}
