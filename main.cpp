#include "Board.h"
#include <iostream>

using namespace std;

int main()
{
    Board board(20);
    board.loadFromFile("config.txt");
    //board.setRandomPositions();
    board.print();
    getchar();
    board.iterate(100);

    cout << endl;
    getchar();
    return 0;
}
