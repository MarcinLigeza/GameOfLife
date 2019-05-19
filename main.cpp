#include "Board.h"

#include <iostream>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "textbutton.h"
#include "shapebutton.h"

#define CUBE_WIDTH 10
#define SIZE 100

using namespace std;
//using namespace boost::filesystem;

int main()
{
    Board board(SIZE);
    cout << "STARTING\n";
    board.loadFromFile("../GameOfLife/config.txt");

    boost::filesystem::path copperhead("/home/marcin/Desktop/gol/GameOfLife/patterns/copperhead.rle");
    cout << copperhead.empty();
    RLE_Encoder tmp;
    std::string xd= tmp.decompress(copperhead);


    boost::filesystem::path gosperglidergun("../GameOfLife/patterns/gosperglidergun.rle");
    board.setPattern(gosperglidergun, 20, 30);

    boost::filesystem::path quuenbeeshuttle("../GameOfLife/patterns/queenbeeshuttle.rle");
    board.setPattern(quuenbeeshuttle, 20, 60);


    sf::RenderWindow window( sf::VideoMode(SIZE*CUBE_WIDTH + 200, SIZE*CUBE_WIDTH), "Game of Life");
    window.setFramerateLimit(20);
    sf::RectangleShape rec(sf::Vector2f(CUBE_WIDTH, CUBE_WIDTH));
    rec.setFillColor(sf::Color::Blue);

    sf::RectangleShape button(sf::Vector2f(150, 50));
    button.setFillColor(sf::Color::Red);
    button.setPosition(CUBE_WIDTH*SIZE, 100);

    sf::Font font;
    font.loadFromFile("../GameOfLife/OpenSans.ttf");

    TextButton but1("Przycisk",font, sf::Vector2f(CUBE_WIDTH*SIZE, 300), sf::Vector2f(150,50));

    sf::ConvexShape shape;
    shape.setPointCount(7);
    shape.setPoint(0, sf::Vector2f(0,0));
    shape.setPoint(1, sf::Vector2f(20,20));
    shape.setPoint(2, sf::Vector2f(20,0));
    shape.setPoint(3, sf::Vector2f(40,20));
    shape.setPoint(4, sf::Vector2f(20,40));
    shape.setPoint(5, sf::Vector2f(20,20));
    shape.setPoint(6, sf::Vector2f(0,40));
    shape.setFillColor(sf::Color::Black);
    shape.setOrigin(20,20);
    ShapeButton but2(shape, sf::Vector2f(CUBE_WIDTH*SIZE, 500), sf::Vector2f(150,50));

//    Button but(&window, CUBE_WIDTH*SIZE, 100, 150,50, "Reset");

    bool iterate = false;
    sf::Event event;



    while (window.isOpen())
//    while(false)
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
                    but1.isPressed(event);
                    but2.isPressed(event);
                    if((event.mouseButton.x >= button.getPosition().x) && (event.mouseButton.x <= button.getPosition().x + button.getSize().x))
                    {
                        if((event.mouseButton.y >= button.getPosition().y) && (event.mouseButton.y <= button.getPosition().y + button.getSize().y))
                        {
                            board.loadBoardFromFile("../boardSave1.txt");
//
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
        {
            board.iteration();

        }
        window.clear(sf::Color::White);

        for(int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if(board.getElement(i,j) == 'o')
                {
                    rec.setPosition(j*CUBE_WIDTH, i*CUBE_WIDTH);
                    window.draw(rec);
                }
            }
        }

        window.draw(button);
        window.draw(but1);
        window.draw(but2);
//        but.draw();
        window.display();
    }
}
