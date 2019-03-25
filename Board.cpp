#include "Board.h"
#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <Windows.h>
#include <fstream>


void Board::resize(int isize)
{
    size = isize + 2;
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
    for (unsigned i = 1; i < size - 1; i++)
    {
        for (unsigned j = 1; j < size - 1; j++)
        {
            buffer += board[i][j];
            buffer += ' ';
        }
        buffer += "\n";
    }
    system("cls");
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
    for (unsigned i = 1; i < size - 1; i++)
    {
        for (unsigned j = 1; j < size - 1; j++)
        {
            if (board[i - 1][j - 1] == 'O') aliveCount++;
            if (board[i - 1][j] == 'O') aliveCount++;
            if (board[i - 1][j + 1] == 'O') aliveCount++;
            if (board[i][j - 1] == 'O') aliveCount++;
            if (board[i][j + 1] == 'O') aliveCount++;
            if (board[i + 1][j - 1] == 'O') aliveCount++;
            if (board[i + 1][j] == 'O') aliveCount++;
            if (board[i + 1][j + 1] == 'O') aliveCount++;

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
    nextboard[size - 1] = nextboard[1];
    nextboard[0] = nextboard[size - 2];
    for (unsigned i = 0; i < size; i++)
    {
        nextboard[i][size - 1] = nextboard[i][1];
        nextboard[i][0] = nextboard[i][size - 2];
    }

    board = nextboard;
}

void Board::setRandomPositions()
{
    srand(time(NULL));
    for (auto& i : board)
    {
        for (auto& j : i)
        {
            if (rand() % 10 > 6)
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
        Sleep(100);
        //getchar();
    }
}

void Board::loadFromFile(string fileName)
{
    ifstream plik;
    plik.open(fileName);

    int isize;
    plik >> isize;
    resize(isize);
  
    for (unsigned i = 1; i < size - 1; i++)
    {
        for (unsigned j = 1; j < size - 1; j++)
        {
            char sign;
            plik >> sign;
            board[i][j] = sign;
        }
    }

}
