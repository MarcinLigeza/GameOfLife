#include "Board.h"

#include <iostream>
#include <functional>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

//#include "textbutton.h"
//#include "shapebutton.h"

#include "game.h"

#define CUBE_WIDTH 10
#define SIZE 100

using namespace std;

void fun(sf::Event e)
{
    std::cout << "Function to test: \n";
}

int main()
{
    cout << "STARTING\n";

    std::shared_ptr<sf::RenderWindow> window = make_shared<sf::RenderWindow>(sf::VideoMode(SIZE*CUBE_WIDTH + 200, SIZE*CUBE_WIDTH), "Game of Life");
    Game game(SIZE, CUBE_WIDTH, window);

    game.loadPattern("copperhead", 10, 10);
    game.loadPattern("gosperglidergun", 20, 30);
    game.loadPattern("queenbeeshuttle", 20, 60);

    game.setFPS(20);

    bool iterate = false;
    sf::Event event;
    while (window->isOpen())
    {
        while(window->pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::KeyPressed:
                {
                    switch(event.key.code){
                    case sf::Keyboard::Escape:
                        window->close();
                        break;
                    default:
                        break;
                    }
                }
                break;
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    game.on_mouseClick(event);
                }
                break;
            case sf::Event::Closed:
                window->close();
                break;
            default:
                break;
            }
        }

        game.updateBoard();
        game.drawBoard();
        window->display();
    }
}
