#pragma once
#include <vector>
#include <string>
#include <boost/filesystem/path.hpp>

#include "rle_encoder.h"
#include "display.h"

using namespace std;

class Board
{
private:
    vector<vector<char>> board;
    int size;
    RLE_Encoder rle_encoder;

    void resize(int isize);
public:
    Board();
    Board(unsigned int size);
    ~Board();

    void print();
    void iteration();
    void loadFromFile(string fileName);
    char getElement(int x, int y);

    vector<vector<char>> getBoard();

    void setPattern(boost::filesystem::path path, int x, int y);

    void saveBoardToFile(std::string file_name);
    void loadBoardFromFile(boost::filesystem::path path);
};

