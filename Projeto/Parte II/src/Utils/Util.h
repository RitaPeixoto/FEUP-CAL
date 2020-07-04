#ifndef TOURMATEAPP_UTIL_H
#define TOURMATEAPP_UTIL_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <queue>
#include "graphviewer.h"
#include "GraphView.h"

using namespace std;

void menu_int_options(int &option, int omin, int nmax, const string &description);

int displayMenu(const string &title, vector<string>options,const string &description);


#endif //TOURMATEAPP_UTIL_H
