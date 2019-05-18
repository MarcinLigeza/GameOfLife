#include "rle_encoder.h"
#include <fstream>
#include <iostream>
#include <ctype.h>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

RLE_Encoder::RLE_Encoder()
{

}

RLE_Encoder::~RLE_Encoder()
{

}

std::string RLE_Encoder::decompress(boost::filesystem::path path)
{
    std::cout << path.c_str() <<"\n";
    std::fstream file(path.c_str());

    std::string compressed((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

    std::vector<std::string> lines;
    boost::split(lines, compressed, boost::is_any_of("\n"));

    lines.pop_back();
    lines.pop_back();

    for(int i = 0; i < lines.size(); i++)
    {
        if(lines[i][0] == '#')
        {
            lines.erase(lines.begin() + i);
            i--;
        }
    }

    for(auto& i : lines)
    {
        std::cout << i << "\n";
    }

    int x{};
    int y{};

    std::vector<std::string> dimensions;
    boost::split(dimensions, lines[0], boost::is_any_of(","));

    x = boost::lexical_cast<int>(dimensions[0].substr(4));
    std::cout << x << "\n";
    y = boost::lexical_cast<int>(dimensions[1].substr(5));
    std::cout << y << "\n";

    std::string decompressed{};

    lines.erase(lines.begin());

    for(auto& i : lines)
    {
        int line_size = 0;
        int number = 1;
        for(int j = 0; j < i.size(); j++)
        {
            if(i[j] == 'b')
            {
                decompressed.append(number, 'b');
                line_size+=number;
                number=1;
            }
            else if(i[j] == 'o')
            {
                decompressed.append(number, 'o');
                line_size+=number;
                number=1;
            }
            else if(isdigit(i[j]))
            {
                std::string tmp{};
                do
                {
                    tmp+=i[j];
                    j++;
                    std::cout << tmp;
                }while(isdigit(i[j]));

                number = boost::lexical_cast<int>(tmp);
            }
            else if(i[j] == '$')
            {
                if(line_size < x)
                {
                    decompressed.append((x - line_size), 'b');
                }
                decompressed.append("\n");

                if(number > 1)
                {
                    for(int k =1; k < number; k++)
                    {
                        decompressed.append(8,'b');
                        decompressed.append("\n");
                    }
                }
                number=1;
                line_size = 0;
            }
            else if(i[j]=='!')
            {
                if(line_size < x)
                {
                    decompressed.append((x - line_size), 'b');
                }
            }
        }
    }

    return decompressed;
}

std::string RLE_Encoder::compress(std::string pattern)
{
    std::string compressed;


    for(int i = 0; i < pattern.size(); i++)
    {
        int count = 1;
        while(i < pattern.size() && pattern[i] == pattern[i+1])
        {
            count ++;
            i++;
        }

        if(char(pattern[i+1]) == '\n' && char(pattern[i]) == 'b')
        {
            continue;
        }

        if(count != 1)
            compressed.append(std::to_string(count));
        if(boost::lexical_cast<char>(pattern[i]) == '\n')
            compressed+='$';
        else
            compressed+=(pattern[i]);

    }
    compressed.append("!");

    std::string tmp;

    for(int i = 0; i < compressed.size(); i++)
    {
        int count = 1;
        while(i < compressed.size() && compressed[i] == compressed[i+1])
        {
            count ++;
            i++;
        }

        if(count != 1 && compressed[i] == '$')
            tmp.append(std::to_string(count));

        tmp+=(compressed[i]);

    }

    return tmp;
}















