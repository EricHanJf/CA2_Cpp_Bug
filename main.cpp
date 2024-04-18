#include <iostream>
#include "board.h"
using namespace std;

int main() {
    board board;
    board.intializeBugs("bugs.txt");
    board.displayAllBugs();

    int BugId;
    cout << "Please enter a Bug Id to search (eg. 101,102...)";
    cin >> BugId;
    board.findAndDisplayBug(BugId);
    return 0;

//    int BugId;
//    cout << "Please enter a Bug Id to search (eg. 101,102...)";
//    cin >> BugId;
}
