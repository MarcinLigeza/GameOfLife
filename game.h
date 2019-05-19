#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "display.h"

class Game
{
public:
    Game(unsigned int size, int pixel_size, std::shared_ptr<sf::RenderWindow> target);

    void updateBoard();
    void drawBoard();
    void on_mouseClick(sf::Event& event);

    void loadPattern(std::string name, int x, int y);

    void setFPS(unsigned int fps);

    void play();
    void stop();
    void next();
    void prev();

private:
    Board board;
    Display display;

    int size;
    int pixel_size;

    void addButtons();
};

#endif // GAME_H
