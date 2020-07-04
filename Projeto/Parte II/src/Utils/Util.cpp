#include "Util.h"

void menu_int_options(int &option, int omin, int nmax, const string& description){
//funcao que verifica os inputs do menu 
    cout << endl << description;
    cin >> option;
    while (cin.fail() || option > nmax || option < omin) {
        if (cin.eof()) { //caso de ter sido introduzido o 'crtl+z'
            cin.clear();
            option = -1;
            return;
        }
        else if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid operation, please insert a valid one: ";
            cin >> option;
        }
        else { //qualquer outro caso que nao corresponda ao input pretendido
            cin.ignore(1000, '\n');
            cout << "Invalid operation, please insert a valid one: ";
            cin >> option;
        }
    }
}


int displayMenu(const string& title, vector<string>options, const string& description){
    //funcao generica de display de menus
    int option = -1;
    system("cls");
    unsigned i = 0;
    cout << "---------------- "<<title <<" ----------------\n\n";
    for(; i<options.size()-1;i++){
        cout << i+1 <<" . "<<options.at(i)<<"\n";
    }
    if(options.at(options.size()-1)!= "main"){//se for o main menu não se utiliza o ctrl+z para sair da aplicaçao
        cout << i +1 << " . "<<options.at(options.size()-1)<<endl;
        cout <<"\nInsert CTRL+Z to leave the app\n";
    }
    cout << "--------------------------------------\n";


    menu_int_options(option,1,options.size(),description);
    return option;
}

