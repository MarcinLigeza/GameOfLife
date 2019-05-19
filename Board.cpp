#include "Board.h"
#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <fstream>
#include <unistd.h>

#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

void Board::resize(int isize)
{
    size = isize;
    board.resize(size);
    for (auto& i : board)
    {
        i.resize(size);
        fill(i.begin(), i.end(), 'b');
    }
}

Board::Board(unsigned int isize)
{
    resize(isize);
}

Board::~Board()
{
}

void Board::print()
{
    string buffer{};
    for (unsigned i = 0; i < size - 1; i++)
    {
        for (unsigned j = 0; j < size - 1; j++)
        {
            buffer += board[i][j];
            buffer += ' ';
        }
        buffer += "\n";
    }
    system("clear");
    cout << buffer;
}

void Board::iteration()
{
    vector<vector<char>> nextboard;
    nextboard.resize(size);
    for (auto& i : nextboard)
        i.resize(size);
    for (auto& i : nextboard)
        fill(i.begin(), i.end(), 'b');

    int aliveCount{ 0 };
    for (unsigned i = 0; i < size; i++)
    {
        for (unsigned j = 0; j < size; j++)
        {
            if (board[(i==0) ? (size - 1) : (i - 1)][(j==0) ? (size-1) : (j - 1)] == 'o') aliveCount++;
            if (board[(i==0) ? (size - 1) : (i - 1)][j] == 'o') aliveCount++;
            if (board[(i==0) ? (size - 1) : (i - 1)][(j + 1)%size] == 'o') aliveCount++;
            if (board[i][(j==0) ? (size-1) : (j - 1)] == 'o') aliveCount++;
            if (board[i][(j + 1)%size] == 'o') aliveCount++;
            if (board[(i + 1)%size][(j==0) ? (size-1) : (j - 1)] == 'o') aliveCount++;
            if (board[(i + 1)%size][j] == 'o') aliveCount++;
            if (board[(i + 1)%size][(j + 1)%size] == 'o') aliveCount++;

            if (board[i][j] == 'o')
            {
                if (aliveCount == 3 || aliveCount == 2)
                {
                    nextboard[i][j] = 'o';
                }
                else
                {
                    nextboard[i][j] = 'b';
                }
            }
            else if (aliveCount == 3)
            {
                nextboard[i][j] = 'o';
            }
            else {
                nextboard[i][j] = 'b';
            }

            aliveCount = 0;
        }
    }

    board = nextboard;
}


void Board::iterate(int iterations)
{
    for (int i = 0; i < iterations; i++)
    {
        iteration();
        print();
        usleep(100000);
        //getchar();
    }
}

void Board::loadFromFile(string fileName)
{
    ifstream plik;
    plik.open(fileName);


    int isize{};
    plik >> isize;
    if (isize > size)
        resize(isize);

    for (unsigned i = 0; i < isize; i++)
    {
        for (unsigned j = 0; j < isize; j++)
        {
            char sign;
            plik >> sign;
            board[i][j] = sign;
            cout << sign;
        }
        cout << "\n";
    }


}

char Board::getElement(int x, int y)
{
    return board[x][y];
}

void Board::setPattern(boost::filesystem::path path, int x, int y)
{
    std::string pattern = rle_encoder.decompress(path);

    std::cout << pattern << "\n";

    std::vector<std::string> lines;
    boost::split(lines, pattern, boost::is_any_of("\n"));

    int ix = stoi(lines[0]);
    int iy = stoi(lines[1]);

    std::cout << ix << "\n";
    std::cout << iy << "\n";

    for(int i = 0; i < iy; i++)
    {
        std::cout << lines[i] << "\n";
        for(int j = 0; j < ix; j++)
        {
            board[i+y][j+x] = lines[i+2][j];
        }
    }
}

void Board::saveBoardToFile(string file_name)
{
    cout << "Saving board to file\n";
    std::string board_string;

    fstream file;
    file.open(file_name, fstream::out);

    for(auto& i : board)
    {
        for (auto& j : i)
        {
            board_string+=j;
        }
        board_string+='\n';
    }

    board_string = rle_encoder.compress(board_string);

    string dimensions;
    dimensions += "x = ";
    dimensions.append(std::to_string(size));
    dimensions += ", y = ";
    dimensions.append(std::to_string(size));
    dimensions += '\n';

    file << dimensions;

    file << board_string;
    file << "\n";
}

void Board::loadBoardFromFile(boost::filesystem::path path)
{
    std::string boardstring = rle_encoder.decompress(path);

    std::cout << boardstring;

    std::vector<std::string> lines;
    boost::split(lines, boardstring, boost::is_any_of("\n"));

    int x = stoi(lines[0]);
    int y = stoi(lines[1]);

    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            board[i][j] = lines[i+2][j];
        }
    }

}



