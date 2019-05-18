#pragma once
#include <vector>
#include <string>
#include <boost/filesystem/path.hpp>

#include "rle_encoder.h"

using namespace std;

class Board
{
private:
    vector<vector<char>> board;
    int size;
    RLE_Encoder rle_encoder;

    void resize(int isize);
public:
    Board(unsigned int size = 100);
    ~Board();

    void print();
    void iteration();
    void setRandomPositions();
    void iterate(int iterations);
    void loadFromFile(string fileName);
    char getElement(int x, int y);

    void saveBoardToFile(std::string file_name);
};

