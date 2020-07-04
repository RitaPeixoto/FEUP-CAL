#include "MagicGenerator.h"

/*------------------------------------------------- Magic Generator function --------------------------------------------------*/
OptimizedPath magicGenerator(Graph<coord> &g, ClientInfo* info) {
    OptimizedPath res;

    int time = info->getMinutes(g, info->getIdStart(), info->getIdEnd());
    if(time == -1) {
        cout << "There is no path between starting and end point." << endl;
        return res;
    }

    if(time > info->getTimeAvailable()) {
        cout << "There is no time to get from where you are to the point you want!" << endl;
        cout << "However, we have found the quickest way to get there ..."<< endl;
        res.path = info->getPath(g, info->getIdStart(), info->getIdEnd());
        cout << "It takes " << g.minutesFromDistance(g.distancePath(res.path), info->getMeansOfTransportation()) << " minutes." << endl;
        return res;
    }

    system("cls");

    cout << endl <<  "Loading Path between " << info->getIdStart() << " and " << info->getIdEnd() << "." << endl;
    info->meanOfTransportationToString();

    vector<Vertex<coord>*> poi = g.bfsAllPOI(info->getIdStart(), info->getPoi(), info->getTimeAvailable());
    res = findPoiInPath(g, info, poi, info->getIdStart(), info->getIdEnd(), info->getTimeAvailable());



    return res;
}

/*------------------------------------------------- Public Transportation function --------------------------------------------------*/

void metroPathGenerator(Graph<coord> &g, ClientInfo* info) {

    system("cls");

    cout << endl <<  "Loading Path between " << info->getIdStart() << " and " << info->getIdEnd() << "." << endl;
    info->meanOfTransportationToString();

    double origDist = INT_MAX, endDist = INT_MAX;
    MetroStation stopOrig, stopEnd;

    for(MetroStation station: g.getMetroStations()) {
        double dist = info->getDistance(g, info->getIdStart(), station.getID());
        if(dist < origDist) {
            origDist = dist;
            stopOrig = station;
        }
        dist = info->getDistance(g, station.getID(), info->getIdEnd());
        if (dist < endDist) {
            endDist = dist;
            stopEnd = station;
        }
    }

    if(stopOrig.getStopNum() == stopEnd.getStopNum()){
        cout << "It's better to just walk this route! Please select a different menu." << endl;
        sleep(3);
        return;
    }

    int timeLeft = info->getTimeAvailable() - g.getMetroTime(stopOrig, stopEnd);

    if(timeLeft <= 0) {
        cout << "No time for the metro trip" << endl;
        sleep(3);
        return; //no time to do the metro trip
    }

    int origTime = info->getMinutes(g, info->getIdStart(), stopOrig.getID());
    int endTime = info->getMinutes(g, stopEnd.getID(), info->getIdEnd());

    if(origTime + endTime >= timeLeft) {
        cout << "No time to get to the metro." << endl;
        cout << endl << endl << "Insert any key to return to the menu..." << endl;
        char input;
        cin >> input;
        return;
    }

    int origFactor = floor(timeLeft * (double)origTime / (double)(endTime + origTime));
    vector<Vertex<coord>*> poi = g.bfsAllPOI(info->getIdStart(), info->getPoi(), origFactor);

    OptimizedPath pathFromOrig = findPoiInPath(g, info, poi, info->getIdStart(), stopOrig.getID(), origFactor);

    int endFactor = floor(timeLeft * (double)endTime / (double)(endTime + origTime));
    poi = g.bfsAllPOI(stopEnd.getID(), info->getPoi(), endFactor);

    OptimizedPath pathToEnd = findPoiInPath(g, info, poi, stopEnd.getID(), info->getIdEnd(), endFactor);

    vector<int> aux;
    for(int id: pathToEnd.visitedId)
        aux.push_back(id);
    for(int id: pathFromOrig.visitedId)
        aux.push_back(id);

    GraphViewer* gv = createMapViewer(g, false);
    showPathWithMetro(gv, g, pathFromOrig.path, pathToEnd.path, aux, stopOrig, stopEnd);


    double dist = g.distancePath(pathFromOrig.path) + g.distancePath(pathToEnd.path);
    cout << "Walking distance: " << dist << "km" << endl;
    cout << "Moving time: " << g.minutesFromDistance(dist, 'w') << "m" << endl;
    if(!pathFromOrig.visitedId.empty()) {
        cout << "Average time in visited points:" << endl;
        for(int id: aux) {
            Vertex<coord>* v = g.findVertex(id);
            cout << id << " - " << v->getType() << " - " << v->getDuration() << "m" << endl;
        }
    }

    cout << endl << endl << "Insert any key to return to the menu..." << endl;
    char input;
    cin >> input;

    gv->closeWindow();
}


/*--------------------------------------------- Circular Path ---------------------------------------------------------------------*/

OptimizedPath circularPath(Graph<coord> &g, ClientInfo* info){

    system("cls");
    cout << endl <<  "Loading Circular Path starting at "<< info->getIdStart() << "." << endl;
    info->meanOfTransportationToString();

    OptimizedPath res;

    //getting all points acessible from the orig
    vector<Vertex<coord>*> points = g.bfsAllPOI(info->getIdStart(), info->getPoi(), info->getTimeAvailable());
    if(points.empty()) {
        cout << "Cant get anywhere!" << endl;
        return res;
    }

    int counter = ceil(points.size()*info->getCounterFactor());
    for(Vertex<coord>* point: points) {
        if(point->getId() == info->getIdStart())
            continue;

        if(counter == 0) {
            break;
        }

        int timeLeft = info->getTimeAvailable() - g.minutesFromDistance(info->getDistance(g, info->getIdStart(), point->getId()), info->getMeansOfTransportation());
        timeLeft -= point->getDuration();
        if(timeLeft <= 0) {
            counter--;
            continue;
        }

        vector<Vertex<coord>*> poi = g.bfsAllPOI(point->getId(), info->getPoi(), timeLeft);
        queue<Vertex<coord>*> path = info->getPath(g, info->getIdStart(), point->getId());
        vector<Vertex<coord>*> POIs = POIsInPath(path, points);

        for (Vertex<coord>*vertex: POIs) {
            auto it = find(poi.begin(), poi.end(), vertex);
            if (it != poi.end())
                poi.erase(it);
        }

        OptimizedPath optPath = findPoiInPath(g, info, poi, point->getId(), info->getIdStart(), timeLeft);
        if(optPath.path.empty()) {
            counter--;
            continue;
        }

        OptimizedPath newOpt;
        path.pop();
        newOpt.path = joinQueue(optPath.path, path);
        newOpt.visitedId = optPath.visitedId;
        newOpt.visitedId.push_back(point->getId());
        if(optPath.visitedId.size() > res.visitedId.size()
        || (optPath.visitedId.size() == res.visitedId.size() && g.distancePath(optPath.path) < g.distancePath(res.path))) {
            res = newOpt;
        }
    }
    return res;
}


/*----------------------------------------------- Find poi in path ---------------------------------------------------------------*/

OptimizedPath findPoiInPath(Graph<coord> &g, ClientInfo* info, const vector<Vertex<coord>*> &poi, const int &orig, const int &dest, const int &availableTime) {
    struct OptimizedPath empty;  //empty queue to return when cant find path
    struct OptimizedPath best;

    int minTime = info->getMinutes(g, orig, dest);
    best.path = info->getPath(g, orig, dest);
    if(minTime > availableTime) {
        return empty;   //no time to go straight from orig to dest
    }
    else if(minTime == availableTime) {
        return best;
    }

    int counter = ceil(poi.size()*info->getCounterFactor());

    for (Vertex<coord>* point: poi) {
        if(counter == 0) {
            break;
        }

        if (point->getId() == orig || point->getId() == dest)
            continue;   //point is the same as orig or dest

        int time = info->getMinutes(g, orig, point->getId());
        if(time == -1) {
            counter--;
            continue;
        }
        int remainingTime = availableTime - time - point->getDuration();
        if (remainingTime <= 0) {
            counter--;
            continue;   //no time to go from orig to point
        }

        time = info->getMinutes(g, point->getId(), dest);
        if(time == -1) {
            counter--;
            continue;
        }

        int finalTime = remainingTime - time;

        if (finalTime <= 0) {
            counter--;
            continue;       //no time to go from orig to point to dest
        }

        if (best.visitedId.empty()) {
            best.path = joinQueue(info->getPath(g, point->getId(), dest), info->getPath(g, orig, point->getId()));
            best.visitedId = {point->getId()};
        }

        //remove points of interest already visited in the way from orig to point
        //remove points of interest that cant go to from point
        vector<Vertex<coord>*> POIsFromOrig = POIsInPath(info->getPath(g, orig, point->getId()), poi);
        vector<Vertex<coord>*> vec = g.bfsAll(point->getId());
        vector<Vertex<coord>*> aux;

        for (Vertex<coord>* vertex: poi) {
            if (find(vec.begin(), vec.end(), vertex) != vec.end() &&
                find(POIsFromOrig.begin(), POIsFromOrig.end(), vertex) == POIsFromOrig.end() &&
                vertex->getDuration() < remainingTime)
                aux.push_back(vertex);
        }

        OptimizedPath optPathToDest = findPoiInPath(g, info, aux, point->getId(), dest, remainingTime);

        if (optPathToDest.path.empty()) {
            counter--;
            continue;     //couldn't find path
        }

        //update best with path found recursively
        optPathToDest.visitedId.push_back(point->getId());
        optPathToDest.path = joinQueue(optPathToDest.path, info->getPath(g, orig, point->getId()));
        if (optPathToDest.visitedId.size() > best.visitedId.size()
             || (optPathToDest.visitedId.size() == best.visitedId.size() && g.distancePath(optPathToDest.path) < g.distancePath(best.path))) {
            best = optPathToDest;
        }
    }
    return best;
}

/*----------------------------------------------- Day Tour ---------------------------------------------------------------*/

//cafe majestic, santa catarina, bolhao, aliados, livraria lello, centro da fotografia, clerigos

queue<Vertex<coord>*> calculateDayTour(Graph<coord> &g){
    queue<Vertex<coord>*> morning = calculateMorningTour(g);
    queue<Vertex<coord>*> afternoon = calculateAfternoonTour(g);

    return joinQueue(afternoon, morning);
}

queue<Vertex<coord>*> calculateMorningTour(Graph<coord> &g){

    queue<Vertex<coord>*> path = g.biDirAStarShortestPath(30413, 18083);
    queue<Vertex<coord>*> path1 = g.biDirAStarShortestPath(18083, 17001);
    queue<Vertex<coord>*> path2 = g.biDirAStarShortestPath(17001, 24107);
    queue<Vertex<coord>*> path3 = g.biDirAStarShortestPath(24107, 3295);
    queue<Vertex<coord>*> path4 = g.biDirAStarShortestPath(3295, 36869);
    queue<Vertex<coord>*> path5 = g.biDirAStarShortestPath(36869, 41230);

    queue<Vertex<coord>*> final = joinQueue(path5, path4);
    final = joinQueue(final, path3);
    final = joinQueue(final, path2);
    final = joinQueue(final, path1);
    final = joinQueue(final, path);
    return final;
}

queue<Vertex<coord>*> calculateAfternoonTour(Graph<coord> &g){

    queue<Vertex<coord>*> path = g.biDirAStarShortestPath(41230, 35225);
    queue<Vertex<coord>*> path1 = g.biDirAStarShortestPath(35225, 28445);
    queue<Vertex<coord>*> path2 = g.biDirAStarShortestPath(28445, 1144);
    queue<Vertex<coord>*> path3 = g.biDirAStarShortestPath(1144, 14820);

    queue<Vertex<coord>*> final = joinQueue(path3, path2);
    final = joinQueue(final, path1);
    final = joinQueue(final, path);
    return final;
}



/*------------------------------------------Auxiliar functions-----------------------------------------*/

queue<Vertex<coord>*> joinQueue(queue<Vertex<coord>*> frontQ, queue<Vertex<coord>*> backQ) {
    while(!backQ.empty()) {
        frontQ.push(backQ.front());
        backQ.pop();
    }
    return frontQ;
}

vector<Vertex<coord>*> POIsInPath(queue<Vertex<coord>*> path, vector<Vertex<coord>*> poi) {
    vector<Vertex<coord>*> res;
    while(!path.empty()) {
        if(find(poi.begin(), poi.end(), path.front()) != poi.end())
            res.push_back(path.front());
        path.pop();
    }
    return res;
}

/*------------------------------------ Functions to get client info --------------------------*/
int getTransportation(bool circular) {
    vector<string> items;
    if(circular) items = {"Walking/Biking", "Car", "Back to main"};
    else items = {"Walking/Biking", "Car", "Public Transportations", "Back to main"};

    string description = "Choose one means of transportation from the menu (integer number): ";

    int op = displayMenu("How do you want to do your tour?", items, description);

    if(op == items.size()) return 0;

    return op;
}
int getAvailableTime() {
    int time;
    cout << "Please enter the time you have available for the tour (in minutes, insert 0 to go back and CTRL+Z to leave the app): ";
    cin >> time;
    while(cin.fail() && cin.eof()){
        if(cin.eof()){
            cin.clear();
            return -1;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please insert a valid integer: ";
        cin >> time;
    }
    return time;
}
string getTypeStartPoint(){
    vector<string> items = {"Information", "Hotel", "Attraction", "ViewPoint", "Guest_House", "Picnic_Site", "Artwork", "Camp_Site","Museum","Generic", "Back to main"};

    string description = "Choose what type of point where your journey starts (integer number):";
    string title = "Type of start point";

    int op = displayMenu(title, items, description);

    if(op == items.size()) return "";
    if(op == items.size()-1) return "*";
    if(op == -1) return "crash";

    string lowercase = items.at(op-1);
    transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);
    return lowercase;
}

int getStartPoint(const Graph<coord> &g, const string &typeStart, bool circular, bool metro) {
    GraphViewer* gv = createMapViewer(g, false);
    //filtrar para mostrar
    vector<Vertex<coord>*> poi;
    for(Vertex<coord>* vertex: g.getVertexSet()) {
        if(vertex->getType() == typeStart)
            poi.push_back(vertex);
    }
    //mostrar
    showPOI(gv, poi, -1);
    if(metro)
        showMetroLine(gv, g);
    //escolher o ponto
    int op;
    string description;
    if(circular ) description = "Choose the id of the point where your journey starts and ends on the map (integer number): ";
    else description = "Choose the id of your starting point on the map (integer number): ";
    menu_int_options(op,1, poi.size(), description);
    gv->closeWindow();
    if(op==-1) return -1;


    return poi.at(op-1)->getId();
}

string getTypeEndPoint(){
    vector<string> items = {"Information", "Hotel", "Attraction", "ViewPoint", "Guest_House", "Picnic_Site", "Artwork", "Camp_site","Museum","Generic", "Back to main"};

    string description = "Choose what type of point where your journey ends (integer number):";
    string title = "Type of end point";

    int op = displayMenu(title, items, description);

    if(op == items.size()) return "";
    if(op == items.size()-1) return "*";
    if(op == -1) return "crash";

    string lowercase = items.at(op-1);
    transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);
    return lowercase;
}

int getEndPoint(Graph<coord> &g, int orig, const string &typeEnd, const int &availableTime, bool metro) {
    //filtrar para mostrar

    vector<Vertex<coord>*> v = g.bfsAllPOI(orig,{typeEnd},availableTime);

    if(v.empty()){
        cout << "There isn't any points of that type to reach from your starting point with your available time! " << endl;
        cout << "We're redirecting you to the main menu ..." << endl;
        sleep(3);
        return 0;
    }

    GraphViewer* gv = createMapViewer(g, false);
    vector<Vertex<coord>*> poi;
    for(Vertex<coord>* i: v) {
        if(i->getType() == typeEnd)
            poi.push_back(i);
    }
    //mostrar
    showPOI(gv, poi, orig);
    if(metro)
        showMetroLine(gv, g);

    //escolher o ponto
    int op;
    string description = "Choose the id of your ending point on the map (integer number): ";
    menu_int_options(op,1, poi.size(), description);
    gv->closeWindow();
    if(op==-1) return -1;
    return poi.at(op-1)->getId();
}

