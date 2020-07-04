#ifndef TOURMATEAPP_ALGORITHMANALYSIS_H
#define TOURMATEAPP_ALGORITHMANALYSIS_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "../Utils/ReadFiles.h"
using namespace std;

void comparePath(Graph<coord> &g, int idStart, int idEnd);
void compareBidirectional(Graph<coord> &g);
void compareDFSBFS(Graph<coord> &g);

void compareAllGrid();



#endif //TOURMATEAPP_ALGORITHMANALYSIS_H
