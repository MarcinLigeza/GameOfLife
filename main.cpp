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


int main()
{
    cout << "STARTING\n";

    std::shared_ptr<sf::RenderWindow> window = make_shared<sf::RenderWindow>(sf::VideoMode(SIZE*CUBE_WIDTH + 300, SIZE*CUBE_WIDTH), "Game of Life");
    Game game(SIZE, CUBE_WIDTH, window);

    game.loadPattern("copperhead", 10, 10);
    game.loadPattern("gosperglidergun", 80, 30);
    game.loadPattern("queenbeeshuttle", 40, 60);

    sf::Clock clock;

    sf::Time elapsed = clock.restart();

    std::cout << "Time: " << elapsed.asMicroseconds() << "\n";

    double average {0.0};
    int counter {0};

    sf::Event event;
    while (window->isOpen())
    {
        average += clock.restart().asSeconds();
        counter++;

        if(counter == 1000)
        {
            std::cout << 1.0/(average/1000.0) << "\n";
            average = 0.0;
            counter = 0;
        }

        while(window->pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::TextEntered:
                game.on_TextEntered(event);
                break;
            case sf::Event::KeyPressed:
                {
                    switch(event.key.code){
                    case sf::Keyboard::Escape:
                        window->close();
                        break;
                    case sf::Keyboard::Return:
                        game.on_EnterPressed(event);
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
