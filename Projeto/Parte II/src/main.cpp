#include <iostream>
#include "UserInteraction/Menu.h"

using namespace std::chrono;
int main() {
    int res;
    ClientInfo info;
    cout << "Hi! Welcome to TourMateApp\n";

    Graph<coord> gBi = readMap(true);
    Graph<coord> gUni = readMap(false);

    info.startGraph(gUni);
    info.setMeansOfTransportation('w');
    info.setPoi({"*"});
    info.setIdStart(1231);
    info.setIdEnd( 29789);
    info.setTimeAvailable(60);
    info.setCounterFactor(0.3);
    res = mainMenu(&info, gUni, gBi);

    //magicGenerator(gBi, &info);

    /*milliseconds t0 = duration_cast<milliseconds >(system_clock::now().time_since_epoch());
    //OptimizedPath path = circularPath(gBi, &info);
    OptimizedPath path = magicGenerator(gUni, &info);
    milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    cout << "First execution time: "<< t1.count()- t0.count()<< " milliseconds"<<endl;

    GraphViewer* gv = createMapViewer(gBi);
    showPath(gv, path.path, path.visitedId);

    info.setCounterFactor(1);

    t0 = duration_cast<milliseconds >(system_clock::now().time_since_epoch());
    //OptimizedPath path = circularPath(gBi, &info);
    path = magicGenerator(gBi, &info);
    t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    cout << "First execution time: "<< t1.count()- t0.count()<< " milliseconds"<<endl;

    GraphViewer* gv2 = createMapViewer(gBi);
    showPath(gv2, path.path, path.visitedId);

    getchar();*/
    //compareAllGrid();

    system("cls");
    cout <<"\nYou're exiting ...\n";
    cout <<"Thanks for using our app!\n";
    sleep(2);

    return 0;
}