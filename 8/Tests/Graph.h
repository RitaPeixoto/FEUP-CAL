/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;

constexpr auto INF = std::numeric_limits<double>::max();

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
template <class T>
class Vertex {
	T info;
	vector<Edge<T> *> outgoing;  // adj
	vector<Edge<T> *> incoming;
	Edge<T> * addEdge(Vertex<T> *dest, double c, double f);
	Vertex(T in);

	bool visited;  // for path finding
	Edge<T> *path; // for path finding

public:
	T getInfo() const;
	vector<Edge<T> *> getAdj() const;
	friend class Graph<T>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {
}

template <class T>
Edge<T> *Vertex<T>::addEdge(Vertex<T> *dest, double c, double f) {
	Edge<T> * e = new Edge<T>(this, dest, c, f);
	this->outgoing.push_back(e);
	dest->incoming.push_back(e);
	return e;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
vector<Edge<T> *> Vertex<T>::getAdj() const {
	return this->outgoing;
}


/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
template <class T>
class Edge {
	Vertex<T> * orig;
	Vertex<T> * dest;
	double capacity;
	double flow;
	Edge(Vertex<T> *o, Vertex<T> *d, double c, double f=0);

public:
	double getFlow() const;
	Vertex<T> *getDest() const;

	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w, double f): orig(o), dest(d), capacity(w), flow(f){}

template <class T>
double Edge<T>::getFlow() const {
	return flow;
}

template <class T>
Vertex<T>* Edge<T>::getDest() const {
	return dest;
}


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */
template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	Vertex<T>* findVertex(const T &inf) const;
public:
	vector<Vertex<T> *> getVertexSet() const;
	Vertex<T> *addVertex(const T &in);
	Edge<T> *addEdge(const T &sourc, const T &dest, double c, double f=0);
	void fordFulkerson(T source, T target);
	void ResetFlows();
    bool FindAugmentationPath(Vertex<T> * source, Vertex<T> * target);
    void TestAndVisit(queue<Vertex<T>*>* Q, Edge<T>* e, Vertex<T>* w, double residual);
    double FindMinResidualAlongPath(Vertex<T>* source, Vertex<T>* target);
    void AugumentFlowAlongPath(Vertex<T>* source, Vertex<T>* target, double f);
};

template <class T>
Vertex<T> * Graph<T>::addVertex(const T &in) {
	Vertex<T> *v = findVertex(in);
	if (v != nullptr)
		return v;
	v = new Vertex<T>(in);
	vertexSet.push_back(v);
	return v;
}

template <class T>
Edge<T> * Graph<T>::addEdge(const T &sourc, const T &dest, double c, double f) {
	auto s = findVertex(sourc);
	auto d = findVertex(dest);
	if (s == nullptr || d == nullptr)
		return nullptr;
	else
		return s->addEdge(d, c, f);
}

template <class T>
Vertex<T>* Graph<T>::findVertex(const T & inf) const {
	for (auto v : vertexSet)
		if (v->info == inf)
			return v;
	return nullptr;
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}


/**
 * Finds the maximum flow in a graph using the Ford Fulkerson algorithm
 * (with the improvement of Edmonds-Karp).
 * Assumes that the graph forms a flow network from source vertex 's'
 * to sink vertex 't' (distinct vertices).
 * Receives as arguments the source and target vertices (identified by their contents).
 * The result is defined by the "flow" field of each edge.
 */
template <class T>
void Graph<T>::TestAndVisit(queue<Vertex<T>*>* Q, Edge<T>* e, Vertex<T>* w, double residual){
    if(!w->visited && residual>0){
        w->visited=true;
        w->path=e; // previous edge in shortest path
        Q->push(w);
    }
}
template <class T>
bool Graph<T>:: FindAugmentationPath(Vertex<T> * source, Vertex<T> * target){ // Edmonds-Karp (breadth-first)
    for(Vertex<T>* v: getVertexSet()){
        v->visited= false;
    }
    source->visited = true;

    Vertex<T>*v;
    queue<Vertex<T>*> q;
    q.push(source);

    while(!q.empty()&& !target->visited){
        v=q.front();
        q.pop();
        for(Edge<T>* e: v->outgoing){ // direct residual edges
            TestAndVisit(&q, e, e->dest, e->capacity - e->flow);
        }
        for(Edge<T>* e: v->incoming){ // reverse residual edges
            TestAndVisit(&q,e,e->orig,e->flow);
        }
    }
    return  target->visited;
}

template <class T>
double Graph<T>::FindMinResidualAlongPath(Vertex<T>* source, Vertex<T>* target){
    double f = INT_MAX;
    Vertex<T>* v= target;

    while(v!=source){
        Edge<T> * e = v->path;

        if(e->dest == v){// direct residual edge
            f = min(f, e->capacity - e->flow);
            v= e->orig;
        }
        else{// reverse residual edge
            f = min(f, e->flow);
            v = e->dest;
        }
    }
    return f;
}
template <class T>
void Graph<T>::AugumentFlowAlongPath(Vertex<T>* source, Vertex<T>* target, double f){
    Vertex<T>* v = target;
    while(v!=source){
        Edge<T> * e = v->path;
        if(e->dest == v){ // direct residual edge
            e->flow += f;
            v = e->orig;
        }
        else{// reverse residual edge
            e->flow -=  f;
            v = e->dest;
        }
    }
}


template <class T>
void Graph<T>::ResetFlows(){
        for (Vertex<T> * v : vertexSet){
            for (Edge<T> * e : v->outgoing){
                e->flow = 0;
            }
        }
}

template <class T>
void Graph<T>::fordFulkerson(T source, T target) {
    // TODO
    Vertex<T>* s = findVertex(source);
    Vertex<T>* t = findVertex(target);

    ResetFlows();
    int f, maxF=0;
    while(FindAugmentationPath(s,t)){
        f = FindMinResidualAlongPath(s,t);
        AugumentFlowAlongPath(s,t,f);
        maxF += f;
        cout << "Max Flow = " << maxF << endl;
    }
}


#endif /* GRAPH_H_ */
