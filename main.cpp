#include <iostream>
#include <array>
#include <random>
#include <chrono>
#include <windows.h>
#include <string>

#define SIZE 30

using namespace std;

void printBoard(array<array<char, SIZE>, SIZE> board);
void iterate(array<array<char, SIZE>, SIZE>& board);

int main()
{
    array<array<char, SIZE>, SIZE> board;

    for(auto& i : board)
    {
        for(auto& j : i)
        {
            unsigned seed = chrono::system_clock::now().time_since_epoch().count();
            if(auto random1 = mt19937 (seed); (random1() % 10) < 6)
            {
                j = '-';
            }
            else {
                j = 'O';
            }
        }
    }

    printBoard(board);
    getchar();

    for(;;)
    {
        iterate(board);
        printBoard(board);
        Sleep(100);
        if(getchar() == 113)
            break;
    }


    cout << endl;
    return 0;
}


void printBoard(array<array<char, SIZE>, SIZE> board)
{
    string buffer{};
    for (auto i : board)
    {
        for (auto j: i)
        {
            buffer += j;
            buffer += ' ';
        }
        buffer += "\n";
    }
    system("cls");
    cout << buffer;
}

void iterate(array<array<char, SIZE>, SIZE>& prevboard)
{
    array<array<char, SIZE>, SIZE> nextboard;
    int aliveCount{0};
    for (unsigned i = 1; i < SIZE-1; i++)
    {
        for (unsigned j = 1; j < SIZE-1; j++)
        {
            if(prevboard[i-1][j-1] == 'O') aliveCount++;
            if(prevboard[i-1][j] == 'O') aliveCount++;
            if(prevboard[i-1][j+1] == 'O') aliveCount++;
            if(prevboard[i][j-1] == 'O') aliveCount++;
            if(prevboard[i][j+1] == 'O') aliveCount++;
            if(prevboard[i+1][j-1] == 'O') aliveCount++;
            if(prevboard[i+1][j] == 'O') aliveCount++;
            if(prevboard[i+1][j+1] == 'O') aliveCount++;

            if(prevboard[i][j] == 'O')
            {
                if (aliveCount==3 || aliveCount == 2)
                {
                    nextboard[i][j] = 'O';
                }
                else
                {
                    nextboard[i][j] = '-';
                }
            }
            else if(aliveCount==3)
            {
                nextboard[i][j] = 'O';
            }
            else {
                nextboard[i][j] = '-';
            }

            aliveCount = 0;
        }
    }

    prevboard = nextboard;
}
