#include "Menu.h"

int mainMenu(ClientInfo *info, Graph<coord> &g, Graph<coord> &gbdir){
    vector<string> items = {"View Map", "Generate Path","Generate Circular Path", "Day Tour", "Manage Preferences","Algorithm Analysis", "Quit Program", "main"};
    string description = "Choose one option from the menu (integer number): ";
    
    int value = 0, option;

    do{
        option = displayMenu("Welcome", items, description);

        if(option == 1) value = viewMaps(g);
        else if (option == 2) value = generatePath(info, g, gbdir);
        else if (option == 3) value = generateCircularPath(info, g, gbdir);
        else if (option == 4) value = dayTour(gbdir);
        else if (option == 5) value = managePreferences(info);
        else if (option == 6) value = algorithmAnalysis(g, gbdir);
    } while((option != 7) && (value != -1));

    return 0;
}

int generatePath(ClientInfo* info, Graph<coord> &g, Graph<coord> &gbdir){
    //meio de transporte
    int op = getTransportation(false);
    if(op == -1 || op == 0) return op;

    bool bidir = (op == 1);
    if(op==1) info->setMeansOfTransportation('w');
    else if(op==2) info->setMeansOfTransportation('c');
    else if(op==3) info->setMeansOfTransportation('p');


    //tempo
    int time = getAvailableTime();
    if(time == -1 || time == 0) return time;
    info->setTimeAvailable(time);

    //coordenadas de inicio
    string typeStart = getTypeStartPoint();//escolher o tipo de ponto
    if(typeStart.empty()) return 0;
    if(typeStart == "crash") return -1;

    int idStart = getStartPoint(g, typeStart, false, (op==3));//escolher o ponto em si 
    if(idStart == -1 || idStart == 0) return idStart;
    info->setIdStart(idStart);

    //coordenadas de fim
    string typeEnd = getTypeEndPoint();// escolher o tipo de ponto
    if(typeEnd.empty()) return 0;
    if(typeStart == "crash") return -1;

    int idEnd = getEndPoint(g, idStart, typeEnd, time, (op==3));//escolher o ponto em si
    if(idEnd == -1 || idEnd == 0) return idEnd;
    info->setIdEnd(idEnd);

    //escolheu o mesmo ponto para fim e inicio -- circular path-- redirecionar
    if(idStart == idEnd){
        cout << "If you want a path starting and ending in the same point choose Generate Circular Path in the main menu"<<endl;
        cout << "We're redirecting you to the main menu ..."<<endl;
        sleep(3);
        return 0;
    }

    //chamar a função respetiva à escolha 
    if(op == 3){
        metroPathGenerator(gbdir, info);//caminho de transportes públicos
        return 0;
    }

    OptimizedPath optPath;
    if(bidir) {
        optPath = magicGenerator(gbdir, info);//gerar caminho a pe
    } 
    else {
        optPath = magicGenerator(g, info);//gerar caminho de carro 
    }

    if(optPath.path.empty()) return 0; //não ha caminho

    double dist = g.distancePath(optPath.path);
    cout << "Walking distance: " << dist << "km" << endl;
    cout << "Moving time: " << g.minutesFromDistance(dist, info->getMeansOfTransportation()) << "min" << endl;
    if(!optPath.visitedId.empty()) {
        cout << "Average time in visited points:" << endl;
        for(int id: optPath.visitedId) {
            Vertex<coord>* v = g.findVertex(id);
            cout << id << " - " << v->getType() << " - " << v->getDuration() << "min" << endl;
        }
    }

    //mostrar o caminho gerado no mapa
    GraphViewer *gv = createMapViewer(g, false);
    showPath(gv, optPath.path, optPath.visitedId);

    cout << endl << endl << "Insert any key to return to the menu..." << endl;
    char input;
    cin >> input;

    gv->closeWindow();
    return 0;

}
int generateCircularPath(ClientInfo * info, Graph<coord> &g, Graph<coord> &gbdir){

    //meio de transporte
    int op = getTransportation(true);
    if(op == -1 || op == 0) return op;

    bool bidir = (op == 1);
    if(op==1) info->setMeansOfTransportation('w');
    else if(op==2) info->setMeansOfTransportation('c');

    //tempo
    int time = getAvailableTime();
    if(time == -1 || time == 0) return time;
    info->setTimeAvailable(time);


    //escolher o ponto onde começa e acaba o caminho
    string typeStart = getTypeStartPoint();//escolher o tipo de ponto
    if(typeStart.empty()) return 0;
    if(typeStart == "crash") return -1;

    int idStart = getStartPoint(g, typeStart, true, false);//escolher o ponto em si 
    if(idStart == -1 || idStart == 0) return idStart;
    info->setIdStart(idStart);

    OptimizedPath optPath;
    
    if(bidir)
        optPath = circularPath(gbdir, info); // caminho circular a pe 
    else
        optPath = circularPath(g, info);//caminho circular de carro
    
    if(optPath.path.empty()) {
        cout << endl << endl << "No time! Insert any key to return to the menu..." << endl;
        char input;
        cin >> input;
        return 0;
    }

    double dist = g.distancePath(optPath.path);
    cout << "Total distance: " << dist << "km" << endl;
    cout << "Moving time: " << g.minutesFromDistance(dist, info->getMeansOfTransportation()) << "min" << endl;
    if(!optPath.visitedId.empty()) {
        cout << "Average time in visited points:" << endl;
        for(int id: optPath.visitedId) {
            Vertex<coord>* v = g.findVertex(id);
            cout << id << " - " << v->getType() << " - " << v->getDuration() << "min" << endl;
        }
    }

    //mostrar o caminho gerado no mapa 
    GraphViewer *gv = createMapViewer(g, false);
    showPath(gv, optPath.path, optPath.visitedId);

    cout << endl << endl << "Insert any key to return to the menu..." << endl;
    char input;
    cin >> input;

    gv->closeWindow();

    return 0;
}



int managePreferences(ClientInfo * info){
    vector<string> items = {"Add interest", "Remove interest", "View current interests", "Back to Main"};
    string description = "Choose one option from the menu(integer number): ";
    int option = displayMenu("Manage Preferences", items, description);  
    
    while(true){
        if(option==1){
            addInterest(info);// adicionar um interesse
        }
        else if (option==2){
            removeInterest(info);// remover um interesse 
        }
        else if(option == 3){
            viewInterest(info);//visualizar os  interesses
        }
        else if (option == 4) break; //back to main
        else if (option == -1) return -1; // crtl+z

        option = displayMenu("Manage Preferences", items, description);
    }  
    return 0;
}


int viewMaps(const Graph<coord> &g){
    GraphViewer *gv = createMapViewer(g, true);

    cout << endl << endl << "Insert any key to return to the menu..." << endl;
    char input;
    cin >> input;

    gv->closeWindow();

    return 0;
}

int dayTour(Graph<coord> &g){

    //cafe majestic, santa catarina, bolhao, aliados, livraria lello, centro da fotografia, clerigos

    cout << "Loading tour..." << endl;
    queue<Vertex<coord>*> path = calculateDayTour(g);
    GraphViewer *gv = createMapViewer(g, false);
    vector<int> visitedPoi = {18083, 17001, 24107, 3295, 36869, 41230, 35225, 28445, 1144};


    showRealPOIPath(gv, g, path, visitedPoi);

    double dist = g.distancePath(path);
    cout << "Total distance: " << dist << "km" << endl;
    cout << "Moving time: " << g.minutesFromDistance(dist, 'w') << "min" << endl<<endl;

        cout << "Starting in "<< g.realPOIName(30413) << endl<< endl;
        for(int id: visitedPoi) {
            Vertex<coord> * v = g.findVertex(id);
            if(id == 41230) {
                cout << "--Almoco--"<< endl;
            }
            cout << id << " - " << g.realPOIName(id) << " - " << v->getDuration() << "min" << endl;
        }
        cout <<endl <<"Ending in " << g.realPOIName(14820) << endl;


    cout << endl << endl << "Insert any key to return to the menu..." << endl;
    char input;
    cin >> input;

    gv->closeWindow();

    return 0;
}

int algorithmAnalysis(Graph<coord> &g, Graph<coord> &gbdir){
    vector<string> items = {"Comparing Dijkstra and AStar in small path", "Comparing Dijkstra and AStar in big path", "Comparing bidirectional Dijkstra and bidirectional AStar", "Comparing DFS and BFS", "Comparing Dijkstra, AStar and Floyd-Warshall in grid graphs",  "Back to main menu"};
    string description = "Choose one option from the menu(integer number): ";
    int option;
    do {
        option = displayMenu("Manage Preferences", items, description);
        if (option == 1) comparePath(g, 30413, 36869);
        else if (option == 2) comparePath(g, 1231, 29789);
        else if (option == 3) compareBidirectional(gbdir);
        else if (option == 4) compareDFSBFS(g);
        else if (option == 5) compareAllGrid();
    }while(option != 6 && option != -1);
    if (option == -1) return option;
    return 0;
}


