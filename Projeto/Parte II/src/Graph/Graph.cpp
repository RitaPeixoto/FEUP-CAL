#include "Graph.h"

/************************************** Vertex  ***************************************/

template <class T>
Vertex<T>::Vertex(T in, int id): info(in), id(id) {}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    Edge<T> *newEdge = new Edge<T>(this, d, w);  
	this->outgoing.push_back(newEdge);
    d->incoming.push_back(newEdge);
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

template <class T>
vector<Edge<T> *> Vertex<T>::getAdj() const{
    return this->outgoing;
}

template <class T>
vector<Edge<T> *> Vertex<T>::getIncoming() const{
    return this->incoming;
}

template <class T>
int Vertex<T>::getId() const {
	return this->id;
}

template <class T>
string Vertex<T>::getType() const {
	return this->type;
}

template <class T>
int Vertex<T>::getDuration() const {
	return this->duration;
}

template <class T>
void Vertex<T>::setType(string type) {
	this->type = type;
}

template <class T>
void Vertex<T>::setDuration(int dur) {
	this->duration = dur;
}

template<class T>
bool Vertex<T>::compare(const Vertex<T> &vertex, bool inv) {
    return (inv)? (this->distI < vertex.distI) : (this->dist < vertex.dist);
}

template <class T>
bool Vertex<T>::operator<(const Vertex &vertex) const {
    return this->dist < vertex.dist;
}

template<class T>
bool Vertex<T>::operator>(const Vertex &vertex) const {
    return vertex < *this;
}

template<class T>
bool Vertex<T>::operator<=(const Vertex &vertex) const {
    return !(vertex < *this);
}

template<class T>
bool Vertex<T>::operator>=(const Vertex &vertex) const {
    return !(*this < vertex);
}



/**************************************  Edge  ***************************************/


template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w): orig(o), dest(d), weight(w) {}

template <class T>
double Edge<T>::getWeight() const {
	return this->weight;
}

template <class T>
Vertex<T> * Edge<T>::getDest() const {
	return this->dest;
}
template <class T>
Vertex<T>* Edge<T>::getOrig() const {
    return this->orig;
}

/**************************************  Graph  ***************************************/

template <class T>
Graph<T>::~Graph() {
    deleteMatrix(W, vertexSet.size());
    deleteMatrix(P, vertexSet.size());
}


template <class T>
void Graph<T>::initializeRealPOIs(){

    realPOIs.insert(make_pair(1144, "Museu do Vinho do Porto"));
    realPOIs.insert(make_pair(41230, "Clerigos"));
    realPOIs.insert(make_pair(28445, "Palacio da Bolsa"));
    realPOIs.insert(make_pair(14820, "Ribeira"));
    realPOIs.insert(make_pair(24107, "Aliados"));
    realPOIs.insert(make_pair(18083, "Santa Catarina"));
    realPOIs.insert(make_pair(41920, "Restaurante"));
    realPOIs.insert(make_pair(3295, "Livraria Lello"));
    realPOIs.insert(make_pair(35225, "Sao Bento"));
    realPOIs.insert(make_pair(17238, "Se do Porto"));
    realPOIs.insert(make_pair(36869, "Centro Portugues de Fotografia"));
    realPOIs.insert(make_pair(30413, "Cafe Majestic"));
    realPOIs.insert(make_pair(17001, "Mercado do Bolhao"));

}

template <class T>
double Graph<T>::getMaxX() const{
    return this->maxX;
}

template <class T>
double Graph<T>::getMinX() const{
    return this->minX;
}

template <class T>
double Graph<T>::getMaxY() const{
    return this->maxY;
}

template <class T>
double Graph<T>::getMinY() const{
    return this->minY;
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return this->vertexSet;
}

template <class T>
vector<MetroStation> Graph<T>::getMetroStations() const {
    return this->stations;
}

template <class T>
int Graph<T>::getMetroTime(MetroStation stopOrig, MetroStation stopEnd) const {
    int total = 0;
    int min, max;

    if(stopOrig.getStopNum() < stopEnd.getStopNum()) {
        min = stopOrig.getStopNum();
        max = stopEnd.getStopNum();
    }
    else {
        min = stopEnd.getStopNum();
        max = stopOrig.getStopNum();
    }

    for(int i = min; i < max; i++) {
        Vertex<T>* v1 = findVertex(stationsMap.find(i)->second);
        Vertex<T>* v2 = findVertex(stationsMap.find(i+1)->second);

        double distance = euclideanDistance(v1, v2) / 1000;
        total += minutesFromDistance(distance, 'p');
    }
    return total;
}

template <class T>
unordered_map<int, string> Graph<T>::getRealPOIs() const{
    return realPOIs;
}

template <class T>
int Graph<T>::getPath(const int &orig, const int &dest) const{
    int i = findVertexIdx(orig);
    int j = findVertexIdx(dest);
    return P[i][j];
}

template <class T>
double Graph<T>::getDistance(const int &orig, const int &dest) const {
    int i = findVertexIdx(orig);
    int j = findVertexIdx(dest);
    return W[i][j];

}

template <class T>
Vertex<T> * Graph<T>::findVertex(const int &id) const {
	auto it = vertexMap.find(id); 
    if(it == vertexMap.end())
        return nullptr;
    return vertexSet.at(it->second);
}

template <class T>
int Graph<T>::findVertexIdx(const int &id) const {
	for (unsigned i = 0; i < currentPoints.size(); i++)
        if (currentPoints.at(i) == id)
            return i;
    return -1;
}

template <class T>
int Graph<T>::findStationID(const int &numStop) const{
    auto it = stationsMap.find(numStop);
    return it->second;
}

template <class T>
bool Graph<T>::addVertex(const int &id, const T &info) {
    if(findVertex(id) != nullptr) return false;

    Vertex<T>* vertex = new Vertex<T>(info, id);

    if(info.first > maxX) maxX = info.first;
    if(info.first < minX) minX = info.first;
    if(info.second > maxY) maxY = info.second;
    if(info.second < minY) minY = info.second;

    vertexSet.push_back(vertex);
    vertexMap.insert(make_pair(id, vertexSet.size() - 1));
    return true;
}

template <class T>
bool Graph<T>::addEdge(const int &sourc, const int &dest, double w){
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);

    if (v1 == nullptr || v2 == nullptr)
        return false;

    for(Edge<T>* e: v1->getAdj()){
        if(e->getDest()->getId() == dest)
            return false;
    }

    v1->addEdge(v2, w);
    return true;
}

template <class T>
bool Graph<T>::addBiDirEdge(const int &sourc, const int &dest, double w){
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);

    if (v1 == nullptr || v2 == nullptr)
        return false;

    bool found = false;
    for(Edge<T>* e: v1->getAdj()){
        if(e->getDest()->getId() == dest) {
            found = true;
            break;
        }
    }

    if(!found)
        v1->addEdge(v2,w);


    for(Edge<T>* e: v2->getAdj()){
        if(e->getDest()->getId() == sourc)
            return true;
    }

    v2->addEdge(v1, w);

    return true;
}

template <class T>
void Graph<T>::addMetroStation(MetroStation station){
    stations.push_back(station);
    stationsMap.insert(make_pair(station.getStopNum(), station.getID()));
}


template <class T>
double Graph<T>::euclideanDistance(Vertex<T> * v1, Vertex<T> * v2) const {
    T info1 = v1->getInfo();
    T info2 = v2->getInfo();
    return sqrt(pow((info1.first - info2.first), 2) + pow((info1.second - info2.second), 2));
}

template <class T>
string Graph<T>::realPOIName(const int &id) const{
    auto it = realPOIs.find(id);
    return it->second;
}

template <class T>
double Graph<T>::distancePath(queue<Vertex<T>*> path) {
    if(path.empty())
        return 0;

    double res = 0;
    Vertex<T> * v1 = path.front();
    path.pop();
    Vertex<T>* v2;

    while(!path.empty()) {
        v2 = path.front();
        path.pop();
        for(Edge<T> *e: v2->getAdj()) {
            if (e->getDest() == v1) {
                res += e->getWeight();
                break;
            }
        }
        v1 = v2;
    }
    return res / 1000;
}

template <class T>
int Graph<T>::minutesFromDistance(double distance, const char& transportation) const{
    if (transportation == 'w') //walking
        return ceil((distance/5.0)*60);
    else if(transportation == 'c') //car
        return ceil((distance/30.0)*60);
    else if (transportation == 'p') //public
        return ceil((distance/50.0)*60);
    return 0;
}

template <class T>
void deleteMatrix(T **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}


/**************************************  Initialize Graph For Algorithms  ***************************************/


template <class T>
void Graph<T>::initializeForSearch(){
    for(Vertex<T>* v: vertexSet)
        v->visited = false;
}

template <class T>
void Graph<T>::initializeForShortestPath(){
    for(Vertex<T>* v: vertexSet) {
        v->dist = INT_MAX;
        v->path = NULL;
        v->queueIndex = 0;
    }
}

template <class T>
void Graph<T>::initializeForBiDir(){
    for(Vertex<T>* v: vertexSet){
        v->dist = INT_MAX;
        v->distI = INT_MAX;
        v->queueIndex = 0;
        v->queueIndexInv = 0;
        v->path = NULL;
        v->pathI = NULL;
    }
}


/**************************************  Algorithms  ***************************************/

template<class T>
vector<Vertex<T>*> Graph<T>::dfs(const int &source) const {
    vector<Vertex<T>*> res;
    for (auto v : vertexSet)
        v->visited = false;
    Vertex<T>* s = findVertex(source);
    dfsVisit(s, res);
    return res;

}

template <class T>
vector<Vertex<T>*> Graph<T>::dfsVisit(Vertex<T> *v, vector<Vertex<T>*> & res) const {
    v->visited = true;
    res.push_back(v);
    for (auto & e : v->getAdj()) {
        auto w = e->dest;
        vector<Vertex<T>*> aux;
        if (!w->visited)
            dfsVisit(w, res);
    }
    return res;
}

template <class T>
vector<Vertex<T>*> Graph<T>::bfs(const int &source, const int &dest){
    
    vector<Vertex<T>*> res;

    if(source == dest) return res;

    initializeForSearch();
    queue<Vertex<T>*> q;
    Vertex<T>* s = findVertex(source);
    Vertex<T>* destination = findVertex(dest);

    q.push(s);
    s->visited = true;;

    while (!q.empty()) {
        Vertex<T>* temp = q.front();
        q.pop();
        res.push_back(temp);

        for(Edge<T>* edge: temp->getAdj()) {
            Vertex<T> *d = edge->getDest();
            if(d == destination) {
                res.push_back(d);
                return res;
            }
            if (!d->visited) { //if not visited
                q.push(d);
                d->visited = true;
            }
        }
    }
    res.clear();
    return res;
}

template <class T>
vector<Vertex<T>*> Graph<T>::bfsAll( const int & source) {
    vector<Vertex<T>*> res;
    queue<Vertex<T>*> q;
    initializeForSearch();

    Vertex<T>* s = findVertex(source);
    if(s == nullptr)
        return res;
    q.push(s);
    s->visited = true;

    while (!q.empty()) {
        Vertex<T>* temp = q.front();
        q.pop();
        res.push_back(temp);
        for(Edge<T>* edge: temp->getAdj()) {
            Vertex<T> *d = edge->getDest();
            if (!d->visited) {
                q.push(d);
                d->visited = true;
            }
        }
    }
    return res;
}

template<class T>
vector<Vertex<T>*> Graph<T>::bfsAllPOI(const int & source, vector<string> types, int dur) {
    vector<Vertex<T>*> res;
    queue<Vertex<T>*> q;
    initializeForSearch();

    Vertex<T>* s = findVertex(source);
    if(s == nullptr)
        return res;
    q.push(s);
    s->visited = true;

    while (!q.empty()) {
        Vertex<T>* temp = q.front();
        q.pop();
        if(temp->getType() != " " && temp->getDuration() < dur) {
            if (types.empty() || find(types.begin(), types.end(), temp->getType()) != types.end()) {
                res.push_back(temp);
            }
        }
        for(Edge<T>* edge: temp->getAdj()) {
            Vertex<T>*d = edge->getDest();
            if (!d->visited) {
                q.push(d);
                d->visited = true;
            }
        }
    }
    return res;
}


template<class T>
inline bool Graph<T>::relax(Vertex<T> *v, Vertex<T> *w, double weight) {
	if (v->dist + weight < w->dist) {
		w->dist = v->dist + weight;
		w->path = v;
		return true;
	}
	else
		return false;
}

template <class T>
queue<Vertex<T>*> Graph<T>::dijkstraShortestPath(const int &origin, const int &dest){

    queue<Vertex<T>*> path;
    if(origin == dest) return path;

    initializeForShortestPath();
    Vertex<T> * orig = findVertex(origin);
    Vertex<T> * final = findVertex(dest);

    orig->dist = 0;
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(orig);


    while(!q.empty()) {
        Vertex<T>* temp = q.extractMin();

        if(temp == final) break;

        for(Edge<T>* edge: temp->getAdj()) {
            Vertex<T> * v = edge->getDest();
            bool notFound = (v->getDist() == INT_MAX);

            if(relax(temp, v, edge->getWeight())){
                if(notFound) q.insert(v);
                else q.decreaseKey(v);
            }
        }
    }

    path.push(final);
    Vertex<T>* previous = final->getPath();
    path.push(previous);
    while(previous != orig) {
        previous = previous->getPath();
        path.push(previous);
    }

    return path;
}

template <class T>
queue<Vertex<T>*> Graph<T>::aStarShortestPath(const int &origin, const int &dest){

    queue<Vertex<T>*> path;
    if(origin == dest) return path;

    initializeForShortestPath();
    Vertex<T> * orig = findVertex(origin);
    Vertex<T> * final = findVertex(dest);

    orig->dist = 0;
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(orig);


    while(!q.empty()) {
        Vertex<T>* temp = q.extractMin();

        if(temp == final) break;

        for(Edge<T>* edge: temp->getAdj()) {

            Vertex<T> * v = edge->getDest();

            double f = temp->getDist() - euclideanDistance(temp, final) + euclideanDistance(v, final) + edge->getWeight();

            bool notFound = (v->getDist() == INT_MAX);

            if(f < v->getDist()){
                v->dist = f;
                v->path = temp;

                if(notFound) q.insert(v);
                else q.decreaseKey(v);
            }
        }
    }

    

    path.push(final);
    Vertex<T>* previous = final->getPath();
    path.push(previous);
    while(previous != orig) {
        previous = previous->getPath();
        path.push(previous);
    }

    return path;
}


template <class T>
void Graph<T>::floydWarshallShortestPath(){
    unsigned n = vertexSet.size();

    deleteMatrix(W, n);
    deleteMatrix(P, n);

    W = new double *[n];
    P = new int *[n];

    for (unsigned i = 0; i < n; i++) {
        W[i] = new double[n];
        P[i] = new int[n];
        for (unsigned j = 0; j < n; j++) {
            W[i][j] = i == j? 0 : INT_MAX;
            P[i][j] = -1;
        }

        for (auto e : vertexSet.at(i)->outgoing) {
            int j = findVertexIdx(e->dest->id);
            W[i][j] = e->weight;
            P[i][j] = i;
        }
    }
    for(unsigned k = 0; k < n; k++)
        for(unsigned i = 0; i < n; i++)
            for(unsigned j = 0; j < n; j++) {
                if(W[i][k] == INT_MAX || W[k][j] == INT_MAX)
                    continue; // avoid overflow
                int val = W[i][k] + W[k][j];
                if (val < W[i][j]) {
                    W[i][j] = val;
                    P[i][j] = P[k][j];
                }
            }
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const int &orig, const int &dest) const{
    vector<T> res;
    int i = orig;
    int j = dest;
    if (i == -1 || j == -1 || W[i][j] == INT_MAX) // missing or disconnected
        return res;
    for ( ; j != -1; j = P[i][j])
        res.push_back(vertexSet[j]->info);
    reverse(res.begin(), res.end());
    return res;
}

template <class T>
queue<Vertex<T>*> Graph<T>:: biDirDijkstraShortestPath(const int &origin, const int &dest){
    queue<Vertex<T>*> path;
    if(origin == dest) return path;

    initializeForBiDir();

    //Maps to keep track of visited vertices
    unordered_map<int, bool> fVisited;
    unordered_map<int, bool> iVisited;

    //Creating forward and reverse priority queues
    MutablePriorityQueue<Vertex<T>> fQueue;
    MutablePriorityQueue<Vertex<T>> iQueue(true);


    //Starting values
    Vertex<T> *src = findVertex(origin), *final = findVertex(dest), *mid;

    src->dist = 0;
    final->distI = 0;

    fQueue.insert(src);
    iQueue.insert(final);


    while(!fQueue.empty() && !iQueue.empty()){
        //Forward search
        //Starting by extracting the minimum from forward queue and set vertex as visited by forward search
        Vertex<T>* fV = fQueue.extractMin();
        fVisited.emplace(fV->getId(), true);

        //Checks if it has been visited by reverse search, if so the path has been found
        if(iVisited.count(fV->getId())>0){
            mid = fV;
            break;
        }


        //Explore edges in regular graph
        for (Edge<T>* edge: fV->outgoing){
            Vertex<T> * v = edge->getDest();
            bool notFound = (v->getDist() == INT_MAX);

            if(relax(fV, v, edge->getWeight())){
                if(notFound) fQueue.insert(v);
                else fQueue.decreaseKey(v);
            }
        }

        //Reverse seacrh
        //Starting by extracting the minimum from reverse queue and set vertex as visited by reverse search
        Vertex<T>* iV = iQueue.extractMin();
        iVisited.emplace(iV->getId(), true);

        //Checks if it has been visited by forward search, if so the path has been found
        if(fVisited.count(iV->getId())>0){
            mid = iV;
            break;
        }

        //Explore edges in reverse graph
        for (Edge<T> *edge: iV->incoming){
            Vertex<T> * v = edge->getOrig();
            bool notFound = (v->distI == INT_MAX);

            double temp = iV->distI + edge->getWeight();

            if(v->distI > temp){

                v->distI = temp;
                v->pathI = iV;

                if(notFound) iQueue.insert(v);
                else iQueue.decreaseKey(v);
            }
        }
    }

    //Verify if alternatives paths are better, not passing through the mid vertex
    queue<Vertex<T>*> aux;

    double f = mid->dist + mid->distI;

    for (auto node : fVisited){
        Vertex<T>* temp = findVertex(node.first);

        for(Edge<T>* e: temp->outgoing){

            Vertex<T>* tent = e->getDest();
            if(iVisited.count(tent->getId()) > 0){

                double f_temp = temp->getDist() + tent->getDist() + e->getWeight();

                if(f_temp < f){
                    tent->path = temp;
                    mid = tent;
                    f = f_temp;
                }

            }
        }
    }

    //Start to build the final path from mid
    vector<Vertex<T>*> t;
    t.push_back(mid);
    Vertex<T>* v = mid;


    while(v->path != NULL){
        v = v->path;
        t.emplace(t.begin(),v);
    }

    v = mid;

    while(v->pathI != NULL){
        v = v->pathI;
        t.push_back(v);
    }

    for (unsigned i = t.size(); i-- > 0; ){
        path.push(t.at(i));
    }


    return path;
}


template <class T>
queue<Vertex<T>*> Graph<T>::biDirAStarShortestPath(const int &origin, const int &dest){

    queue<Vertex<T>*> path;
    if(origin == dest) return path;

    initializeForBiDir();

    //Maps to keep track of visited vertices
    unordered_map<int, bool> fVisited;
    unordered_map<int, bool> iVisited;

    //Creating forward and reverse priority queues
    MutablePriorityQueue<Vertex<T>> fQueue;
    MutablePriorityQueue<Vertex<T>> iQueue(true);


    //Starting values
    Vertex<T> *src = findVertex(origin), *final = findVertex(dest), *mid;
    src->dist = 0;
    final->distI = 0;

    fQueue.insert(src);
    iQueue.insert(final);

    while(!fQueue.empty() && !iQueue.empty()){
        //Forward search
        //Starting by extracting the minimum from forward queue and set vertex as visited by forward search
        Vertex<T>* fV = fQueue.extractMin();
        fVisited.emplace(fV->getId(), true);

        //Checks if it has been visited by reverse search, if so the path has been found
        if(iVisited.count(fV->getId())>0){
            mid = fV;
            break;
        }

        //Explore edges in regular graph
        for (Edge<T>* e: fV->outgoing){
            Vertex<T> * v = e->getDest();
            double temp = fV->getDist() + e->getWeight() - euclideanDistance(fV, final) + euclideanDistance(v, final);
            bool notFound = (v->getDist() == INT_MAX);
            if(v->getDist() > temp){
                v->dist = temp;
                v->path = fV;
                if(notFound) fQueue.insert(v);
                else
                    fQueue.decreaseKey(v);
            }
        }

        //Reverse seacrh
        //Starting by extracting the minimum from reverse queue and set vertex as visited by reverse search
        Vertex<T>* iV = iQueue.extractMin();
        iVisited.emplace(iV->getId(), true);

        //Checks if it has been visited by forward search, if so the path has been found
        if(fVisited.count(iV->getId())>0){
            mid = iV;
            break;
        }


        //Explore edges in reverse graph
        for (Edge<T> *e: iV->incoming){
            Vertex<T> * v = e->getOrig();

            double temp = iV->distI + e->getWeight() - euclideanDistance(iV, src) + euclideanDistance(v, src);
            bool notFound = (v->distI == INT_MAX);
            if(v->distI > temp){
                v->distI = temp;
                v->pathI = iV;
                if(notFound) iQueue.insert(v);
                else
                    iQueue.decreaseKey(v);
            }
        }
    }

    //Verify if alternatives paths are better, not passing through mid vertex
    queue<Vertex<T>*> aux;
    double f = mid->dist - euclideanDistance(mid, final) + euclideanDistance(mid, src) + mid->distI;

    for (auto node : fVisited){
        Vertex<T>* temp = findVertex(node.first);

        for(Edge<T>* e: temp->outgoing){

            Vertex<T>* tent = e->getDest();
            if(iVisited.count(tent->getId()) > 0){

                double f_temp = temp->getDist() + tent->getDist() + e->getWeight() - euclideanDistance(temp, final) - euclideanDistance(tent, src);

                if(f_temp < f){
                    tent->path = temp;
                    mid = tent;
                    f = f_temp;
                }

            }
        }
    }

    //Start to build the final path from mid
    vector<Vertex<T>*> t;
    t.push_back(mid);
    Vertex<T>* v = mid;

    while(v->path != NULL){
        v = v->path;
        t.emplace(t.begin(),v);
    }

    v = mid;

    while(v->pathI != NULL){
        v = v->pathI;
        t.push_back(v);
    }

    for (unsigned i = t.size(); i-- > 0; ){
        path.push(t.at(i));
    }

    return path;
}

template<class T>
int Graph<T>::numOfVisitedNodes() {
    int sum = 0;
    for(Vertex<T>* vertex: vertexSet) {
        if(vertex->visited)
            sum++;
    }
    return sum;
}


template class Graph<coord>;
template class Vertex<coord>;
template class Edge<coord>;

