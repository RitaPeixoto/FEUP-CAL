#ifndef TOURMATEAPP_CLIENTINFO_H
#define TOURMATEAPP_CLIENTINFO_H


#include <string>
#include <vector>
#include <algorithm>
#include "../POIGraph/POIGraph.h"


using namespace std;

class ClientInfo{
    private:
        char meansOfTransportation;
        int idStart;
        int idEnd;
        int timeAvailable;
        vector<string> poi;
        double counterFactor = 1;
        POIGraph poiGraph;

    public:
        void startGraph(Graph<coord> g);
        double getDistance(Graph<coord> g,int orig, int end);
        queue<Vertex<coord>*> getPath(Graph<coord> g,int orig, int end);
        int getMinutes(Graph<coord> g,int orig, int end);
        void setMeansOfTransportation(char meansOfTransportation);
        void setIdStart(int idStart);
        void setIdEnd(int idEnd);
        void setTimeAvailable(int timeAvailable);
        void setPoi(vector <string> poi);
        void setCounterFactor(double factor);
        char getMeansOfTransportation();
        int getIdStart();
        int getIdEnd();
        int getTimeAvailable();
        vector<string> getPoi();
        double getCounterFactor();
        void addPoi(const string &point);
        void addAllPoi(const vector<string> &points);
        void removePoi(const string& point);
        void removeAllPoi();
        void meanOfTransportationToString();
};

#endif //TOURMATEAPP_CLIENTINFO_H
