#pragma once
#include <vector>

using namespace std;

class Board
{
private:
    vector<vector<char>> board;
    int size;

    void resize(int isize);
public:
    Board(unsigned int size = 10);
    ~Board();

    void print();
    void iteration();
    void setRandomPositions();
    void iterate(int iterations);
    void loadFromFile(string fileName);
};

