#ifndef TOURMATEAPP_STOP_H
#define TOURMATEAPP_STOP_H


#include <string>
#include <vector>

using namespace std;

class MetroStation {
    int ID;
    string stationName;
    int stopNum;

public:
    MetroStation(){}
    MetroStation(int ID, string stationName, int stopNum): ID(ID), stationName(stationName), stopNum(stopNum) {}
    void setStationName(string stationName){ this->stationName = stationName;}
    int getID() {return ID;}
    string getStationName() {return stationName;}
    int getStopNum() {return stopNum;}
};

#endif //TOURMATEAPP_STOP_H
