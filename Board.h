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
    unsigned int boardSizeBytes;
    unsigned int maxIterations;

    RLE_Encoder rle_encoder;

    vector<vector<vector<char>>> history;

    void resize(int isize);
public:
    Board();
    Board(unsigned int size);
    ~Board();

    void print();
    void iteration();
    void loadFromFile(string fileName);
    char getElement(int x, int y);
    unsigned int getMaxIterations();

    vector<vector<char>> getBoard();

    void setPattern(boost::filesystem::path path, int x, int y);

    void saveBoardToFile(std::string file_name);
    void loadBoardFromFile(boost::filesystem::path path);

    void prevBoard();
    unsigned int historySize();
};

