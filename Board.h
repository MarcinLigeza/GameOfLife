#pragma once
#include <vector>
#include <string>
#include <boost/filesystem/path.hpp>

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
    char getElement(int x, int y);
//    vector<vector<char>> readPatternfromFile(boost::filesystem::path path);
};

