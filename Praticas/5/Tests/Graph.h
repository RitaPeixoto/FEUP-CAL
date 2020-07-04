/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
    vector<vector<double>> d;
    vector<vector<Vertex<T>*>> p;
public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);    //TODO...
	void dijkstraShortestPath(const T &s);      //TODO...
	void bellmanFordShortestPath(const T &s);   //TODO...
	vector<T> getPathTo(const T &dest) const;   //TODO...

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

/*
 * 1. Marcar o vértice s com distância 0 e todos os outros com
distância 
2. Entre os vértices já alcançados (distância != 00) e não
processados (no passo 3), escolher para processar o vértice v
marcado com distância mínima
3. Processar vértice v: analisar os adjacentes de v, marcando os
que ainda não tinham sido alcançados (distância ) com
distância de v mais 1
4. Voltar ao passo 2, se existirem mais vértices para processar*/
template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	// TODO
	Vertex<T> *s = findVertex(orig);
	Vertex<T> *aux;

	for(auto vertex: vertexSet){//1
	    vertex->dist = INT64_MAX;//representa o infinito
        vertex->path = NULL;
	}
    s->dist = 0;//1
    queue<Vertex<T>*> q;
	q.push(s);

	while(!q.empty()){
	    aux = q.front();//2
	    q.pop();
	    typename vector<Edge<T>>::const_iterator it = aux->adj.begin();
	    while(it != aux->adj.end()){//analisar os adjacentes, 3
	        if((*it).dest->dist == INT64_MAX){
	            q.push((*it).dest);
                (*it).dest->dist = aux->dist +1;//3
                (*it).dest->path =  aux;
	        }
	        it ++;//4
	    }
	}

}
/*DIJKSTRA(G, s): // G=(V,E), s  V
1. for each v  V do
2. dist(v)  
3. path(v)  nil
4. dist(s)  0
5. Q   // min-priority queue
6. INSERT(Q, (s, 0)) // inserts s with key 0
7. while Q   do
8. v  EXTRACT-MIN(Q) // greedy
9. for each w  Adj(v) do
10. if dist(w) > dist(v) + weight(v,w) then
11. dist(w)  dist(v)+ weight(v,w)
12. path(w)  v
13. if w  Q then // old dist(w) was 
14. INSERT(Q, (w, dist(w)))
15. else
16. DECREASE-KEY(Q, (w, dist(w)))*/

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    // good video explaining the algorithm : https://www.youtube.com/watch?v=_lHSawdgXpI
	// TODO
	Vertex<T>* s = findVertex(origin);
	Vertex<T>* v;
    for(auto vertex : vertexSet){
        vertex->dist = INT64_MAX;
        vertex->path = NULL;
    }

    s->dist = 0;
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);
     while(!q.empty()){
         v= q.extractMin();
         for(auto w: v->adj){
             if(w.dest->dist > (v->dist + w.weight)){
                 w.dest->dist = v->dist + w.weight;
                 w.dest->path = v;
                 if(!q.inQueue(w.dest)){
                     q.insert(w.dest);
                 }
                 else{
                     q.decreaseKey(w.dest);
                 }
             }
         }
     }

}
/*
 * for each v  V do
2. dist(v)  
3. path(v)  nil
4. dist(s)  0
5. for i = 1 to |V|-1 do
6. for each (v, w)  E do
7. if dist(w) > dist(v) + weight(v,w) then
8. dist(w)  dist(v)+ weight(v,w)
9. path(w)  v
10. for each (v, w)  E do
11. if dist(v) + weight(v,w) < dist(w) then
12. fail("there are cycles of negative weight")*/

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	// TODO
    Vertex<T> * s = findVertex(orig);
	for(auto vertex: vertexSet){
	    vertex->dist = INT64_MAX;
	    vertex->path = NULL;
	}

	s->dist  = 0;
	for(int i =1; i<vertexSet.size()-1; i++){
	    for(auto vertex: vertexSet){
	        for(Edge<T> edge: vertex->adj){
	            if(edge.dest->dist > vertex->dist + edge.weight){
	                edge.dest->dist = vertex->dist + edge.weight;
	                edge.dest->path = vertex;
	            }
	        }
	    }
	}
    for(auto vertex: vertexSet){
        for(Edge<T> edge: vertex->adj) {
            if (edge.dest->dist > vertex->dist + edge.weight) {
                cout <<"there are cycles of negative weight"<<endl;
            }
        }
    }

}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	vector<T> res;
	// TODO
	Vertex<T>* vertex = findVertex(dest);
	res.insert(res.begin(),vertex->info);
	vertex = vertex->path;
	res.insert(res.begin(),vertex->info);
	while(vertex->path != NULL){
        vertex = vertex->path;
        res.insert(res.begin(),vertex->info);
	}
	return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	// TODO
    d.clear();
	p.clear();
    d = vector<vector<double>>(vertexSet.size(), vector<double>(vertexSet.size(), INT64_MAX));
    p = vector<vector<Vertex<T>*>>(vertexSet.size(), vector<Vertex<T>*>(vertexSet.size(), NULL));

    int i =0, j=0;
	for(auto aux_1: vertexSet){
	    for(auto aux_2: vertexSet) {
            if (i == j)
                d[i][j] = 0;//a distancia de um vertice a si proprio é 0
            else {
                for (Edge<T> edge: aux_1->adj) {
                    if (edge.dest->info == aux_2->info) {
                        d[i][j] = edge.weight;
                        p[i][j] = aux_1;
                    }

                }
            }
            j++;
        }
        i++;
        j = 0;
	}

    for(int k=0; k<vertexSet.size();k++){
	    int i=0,j=0;
        for(auto aux_1: vertexSet){
            for(auto aux_2: vertexSet){
                if(d[i][k]+d[k][j]<d[i][j]){
                    d[i][j] = d[i][k]+d[k][j];
                    p[i][j] = p[k][j];
                }
                j++;
            }
            i++;
            j = 0;
        }
	}
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	// TODO
	int s_index, d_index;

	for(int i =0; i<vertexSet.size();i++){
	    if(vertexSet.at(i)->info == orig)
	        s_index = i;
	    else if(vertexSet.at(i)->info==dest)
	        d_index = i;
	}

	while(p[s_index][d_index]!= vertexSet[s_index]){
	    res.emplace(res.begin(),p[s_index][d_index]->info);
	    for(int i=0;i<vertexSet.size();i++){
	        if(vertexSet.at(i)->info == p[s_index][d_index]->info){
	            d_index = i;
	            break;
	        }
	    }
	}
	res.push_back(dest);
	res.insert(res.begin(),orig);

	return res;
}


#endif /* GRAPH_H_ */
