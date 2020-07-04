#ifndef TOURMATEAPP_MENU_H
#define TOURMATEAPP_MENU_H
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <zconf.h>
#include "AlgorithmAnalysis.h"

using namespace std;

int mainMenu(ClientInfo *info, Graph<coord> &g, Graph<coord> &gbdir);

int generatePath(ClientInfo* info, Graph<coord> &g, Graph<coord> &gbdir);

int managePreferences(ClientInfo * info);

int viewMaps(const Graph<coord> &g);

int dayTour(Graph<coord> &g);

int generateCircularPath(ClientInfo * info, Graph<coord> &g, Graph<coord> &gbdir);

int algorithmAnalysis(Graph<coord> &g, Graph<coord> &gbdir);



#endif //TOURMATEAPP_MENU_H
