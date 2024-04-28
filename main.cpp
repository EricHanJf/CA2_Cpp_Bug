#include <iostream>
#include "board.h"
using namespace std;

int main() {
    board board;
    int numberChoice;
    bool exit = false;
    while(!exit){
        cout << " =============================================" << endl;
        cout << " |           Bug's Life Feature Menu         |" << endl;
        cout << " =============================================" << endl;
        cout << " |           [1]. Initialize Bug Board       |" << endl;
        cout << " |           [2]. Display All Bugs           |" << endl;
        cout << " |           [3]. Display Bug By ID          |" << endl;
        cout << " |           [4]. Tap the Bug Board          |" << endl;
        cout << " |           [5]. Display Bug Life History   |" << endl;
        cout << " |           [6]. Write Life History To File |" << endl;
        cout << " |           [7]. Display All Cell           |" << endl;
        cout << " |           [8]. Run Simulation             |" << endl;
        cout << " |           [9]. Display Bugs And Board     |" << endl;
        cout << " |           [0]. Exit The Program           |" << endl;
        cout << " =============================================\n" << endl;

        cout << "Please choice any number you want." << endl;
        cin >> numberChoice;
        switch (numberChoice) {
            case 1:
                board.intializeBugs("bugs.txt");
                cout << "Bug board initialized." << endl;
                break;
            case 2:
                board.displayAllBugs();
                break;
            case 3:
                int BugId;
                cout << "Please enter a Bug Id to search (eg. 101,102...)";
                cin >> BugId;
                board.findAndDisplayBug(BugId);
                break;
            case 4:
                board.TapBoard();
                break;
            case 5:
                board.displayBugLifeHistory();
                break;
            case 6:
                board.writeLifeHistoryToFile();
                break;
            case 7:
                board.displayAllCells();
                break;
            case 8:
                board.runSimulation();
                break;
            case 9:
                board.DisplayBoardAndBug();
                break;
            case 0:
                exit = true;
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout<<"invalid choice, please try it again" << endl;
                break;
        }
    }


    return 0;


}
