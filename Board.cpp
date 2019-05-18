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
        fill(i.begin(), i.end(), '-');
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
        fill(i.begin(), i.end(), '-');

    int aliveCount{ 0 };
    for (unsigned i = 0; i < size; i++)
    {
        for (unsigned j = 0; j < size; j++)
        {
            if (board[(i==0) ? (size - 1) : (i - 1)][(j==0) ? (size-1) : (j - 1)] == 'O') aliveCount++;
            if (board[(i==0) ? (size - 1) : (i - 1)][j] == 'O') aliveCount++;
            if (board[(i==0) ? (size - 1) : (i - 1)][(j + 1)%size] == 'O') aliveCount++;
            if (board[i][(j==0) ? (size-1) : (j - 1)] == 'O') aliveCount++;
            if (board[i][(j + 1)%size] == 'O') aliveCount++;
            if (board[(i + 1)%size][(j==0) ? (size-1) : (j - 1)] == 'O') aliveCount++;
            if (board[(i + 1)%size][j] == 'O') aliveCount++;
            if (board[(i + 1)%size][(j + 1)%size] == 'O') aliveCount++;

            if (board[i][j] == 'O')
            {
                if (aliveCount == 3 || aliveCount == 2)
                {
                    nextboard[i][j] = 'O';
                }
                else
                {
                    nextboard[i][j] = '-';
                }
            }
            else if (aliveCount == 3)
            {
                nextboard[i][j] = 'O';
            }
            else {
                nextboard[i][j] = '-';
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
                j = '-';
            }
            else {
                j = 'O';
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

