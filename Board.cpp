#include "Board.h"
#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <fstream>
#include <unistd.h>

#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>

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
//    nextboard[size - 1] = nextboard[1];
//    nextboard[0] = nextboard[size - 2];
//    for (unsigned i = 0; i < size; i++)
//    {
//        nextboard[i][size - 1] = nextboard[i][1];
//        nextboard[i][0] = nextboard[i][size - 2];
//    }

    board = nextboard;
}

void Board::setRandomPositions()
{
    srand(time(NULL));
    for (auto& i : board)
    {
        for (auto& j : i)
        {
            if (rand() % 10 > 3)
            {
                j = 'b';
            }
            else {
                j = 'o';
            }
        }
    }
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

    file << board_string;
}

