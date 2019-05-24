#include "Board.h"

#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>
#include <algorithm>

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

Board::Board()
{

}

unsigned long get_free_mem()
{
    std::string token;
        std::ifstream file("/proc/meminfo");
        while(file >> token) {
            if(token == "MemFree:") {
                unsigned long mem;
                if(file >> mem) {
                    return mem;
                } else {
                    return 0;
                }
            }
            // ignore rest of the line
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return 0; // nothing found
}

Board::Board(unsigned int isize)
{
    resize(isize);
    boardSizeBytes = sizeof(board) + (sizeof(char)*size*size);
    maxIterations = get_free_mem() * 1024 / boardSizeBytes;
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

void checkCell(vector<vector<char>> &board, int i, int j, vector<vector<char>> &nextboard)
{
    int size = board.size();
    int aliveCount{ 0 };
    if (board[(i==0) ? (size - 1) : (i - 1)][(j==0) ? (size-1) : (j - 1)] == 'o') aliveCount++;
    if (board[(i==0) ? (size - 1) : (i - 1)][j] == 'o') aliveCount++;
    if (board[(i==0) ? (size - 1) : (i - 1)][(j + 1)%size] == 'o') aliveCount++;
    if (board[i][(j==0) ? (size-1) : (j - 1)] == 'o') aliveCount++;
    if (board[i][(j + 1)%size] == 'o') aliveCount++;
    if (board[(i + 1)%size][(j==0) ? (size-1) : (j - 1)] == 'o') aliveCount++;
    if (board[(i + 1)%size][j] == 'o') aliveCount++;
    if (board[(i + 1)%size][(j + 1)%size] == 'o') aliveCount++;

    if (board[i][j] == 'o' && aliveCount == 2)
    {
        nextboard[i][j] =  'o';
    }
    else if (aliveCount == 3)
    {
        nextboard[i][j] =  'o';
    }
    else
    {
        nextboard[i][j] =  'b';
    }
}

void checkRow(vector<vector<char>> &board, int i, vector<vector<char>> &nextboard)
{
    for(unsigned k = i; (k < i+13 && k < board.size()); k++)
    for (unsigned j = 0; j < board.size(); j++)
    {
        checkCell(board, k, j, nextboard);
    }
}

void Board::iteration()
{
    vector<vector<char>> nextboard;
    nextboard.resize(size);
    for (auto& i : nextboard)
        i.resize(size);
    for (auto& i : nextboard)
        fill(i.begin(), i.end(), 'b');

    vector<thread> threads(8);

    for (unsigned i = 0; i < 8; i++)
    {
        threads[i] = std::thread(checkRow, std::ref(board), i*13, std::ref(nextboard));
    }

    for (unsigned i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    history.push_back(board);

    board = nextboard;
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
        }
    }
}

char Board::getElement(int x, int y)
{
    return board[x][y];
}

unsigned int Board::getMaxIterations()
{
    return maxIterations;
}

vector<vector<char> > Board::getBoard()
{
    return board;
}

void Board::setPattern(boost::filesystem::path path, int x, int y)
{
    std::string pattern = rle_encoder.decompress(path);

    std::vector<std::string> lines;
    boost::split(lines, pattern, boost::is_any_of("\n"));

    int ix = stoi(lines[0]);
    int iy = stoi(lines[1]);

    for(int i = 0; i < iy; i++)
    {
        for(int j = 0; j < ix; j++)
        {
            board[(i+y)%size][(j+x)%size] = lines[i+2][j];
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

void Board::prevBoard()
{
    if(history.empty())
    {
        std::cout << "History is empty\n";
    }
    else
    {
        std::copy(history.back().begin(), history.back().end(), board.begin());
        history.pop_back();
    }
}

unsigned int Board::historySize()
{
    history.size();
}



