#include "Board.h"

#include <iostream>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#define CUBE_WIDTH 10
#define SIZE 100

using namespace std;
//using namespace boost::filesystem;

int main()
{
    cout << "Starting\n";
    Board board(SIZE);
    cout << "Starting\n";
    board.loadFromFile("config.txt");

    boost::filesystem::path copperhead{"/home/marcin/qtProjects/GameofLife/patterns/copperhead.rle"};
//    board.readPatternfromFile(copperhead);

    cout << "Starting\n";

    sf::RenderWindow window( sf::VideoMode(SIZE*CUBE_WIDTH + 200, SIZE*CUBE_WIDTH), "Game of Life");
    window.setFramerateLimit(20);
    sf::RectangleShape rec(sf::Vector2f(CUBE_WIDTH, CUBE_WIDTH));
    rec.setFillColor(sf::Color::Blue);

    sf::RectangleShape button(sf::Vector2f(150, 50));
    button.setFillColor(sf::Color::Red);
    button.setPosition(CUBE_WIDTH*SIZE, 100);

//    Button but(&window, CUBE_WIDTH*SIZE, 100, 150,50, "Reset");

    bool iterate = false;
    sf::Event event;

    while (window.isOpen())
    {
        while(window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::KeyPressed:
                {
                    switch(event.key.code){
                    case sf::Keyboard::Space:
                        iterate = !iterate;
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    default:
                        break;
                    }
                }
                break;
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    if((event.mouseButton.x >= button.getPosition().x) && (event.mouseButton.x <= button.getPosition().x + button.getSize().x))
                    {
                        if((event.mouseButton.y >= button.getPosition().y) && (event.mouseButton.y <= button.getPosition().y + button.getSize().y))
                        {
                            board.loadFromFile("config.txt");
                        }
                    }
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }

        if (iterate)
            board.iteration();

        window.clear(sf::Color::White);

        for(int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if(board.getElement(i,j) == 'O')
                {
                    rec.setPosition(j*CUBE_WIDTH, i*CUBE_WIDTH);
                    window.draw(rec);
                }
            }
        }

        window.draw(button);
//        but.draw();
        window.display();
    }
}
