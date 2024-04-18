#include <iostream>
#include "board.h"
using namespace std;

int main() {
    board board;
    board.intializeBugs("bugs.txt");
    board.displayAllBugs();
    return 0;
}
