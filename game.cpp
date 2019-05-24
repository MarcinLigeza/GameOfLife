#include "game.h"

#include "shapebutton.h"
#include "textbox.h"

#include <iostream>

Game::Game(unsigned int i_size, int i_pixel_size, std::shared_ptr<sf::RenderWindow> target)
{
    size = i_size;
    pixel_size = i_pixel_size;
    iterating = false;

    board = Board(size);
    display = Display(i_size,board.getMaxIterations(), i_pixel_size, target);

    setFPS(20);
    addButtons();
    addTextBox();
}

void Game::updateBoard()
{
    if(iterating)
        board.iteration();
}

void Game::drawBoard()
{
    display.draw(board.getBoard(), board.historySize());
}

void Game::on_mouseClick(sf::Event& event)
{
    display.onClick(event);
}

void Game::on_TextEntered(sf::Event& event)
{
    display.onTextEntered(event);
}

void Game::on_EnterPressed(sf::Event& event)
{
    display.onEnterPressed(event);
}

void Game::loadPattern(string name, int x, int y)
{
    boost::filesystem::path path("../GameOfLife/patterns/" + name + ".rle");
    board.setPattern(path,x,y );
}

void Game::setFPS(unsigned int fps)
{
    display.setFPS(fps);
}

void Game::play()
{
    iterating = true;
}

void Game::stop()
{
    iterating = false;
}

void Game::next()
{
    board.iteration();
}

void Game::prev()
{
    board.prevBoard();
}

void Game::addButtons()
{
    int b_height = 50;
    int b_width = 150;
    int separation = 50;

    int x_pos = size*pixel_size+separation;

    //play button ###########################
    sf::ConvexShape playShape;
    playShape.setPointCount(4);
    playShape.setPoint(0, sf::Vector2f(0,0));
    playShape.setPoint(1, sf::Vector2f(20,20));
    playShape.setPoint(2, sf::Vector2f(0,40));
    playShape.setFillColor(sf::Color::Black);
    playShape.setOrigin(10,20);

    std::function<void(sf::Event)> playfun = std::bind(&Game::play, this);
    std::shared_ptr<Button> playButton = std::make_shared<ShapeButton>
            (sf::Vector2f(x_pos, separation), sf::Vector2f(b_width, b_height), playfun, playShape);
    display.add_button(playButton);


    //stop button ########################
    sf::ConvexShape stopShape;
    stopShape.setPointCount(4);
    stopShape.setPoint(0, sf::Vector2f(0,0));
    stopShape.setPoint(1, sf::Vector2f(40,0));
    stopShape.setPoint(2, sf::Vector2f(40,40));
    stopShape.setPoint(3, sf::Vector2f(0,40));
    stopShape.setFillColor(sf::Color::Black);
    stopShape.setOrigin(20,20);

    std::function<void(sf::Event)> stopfun = std::bind(&Game::stop, this);
    std::shared_ptr<Button> stopButton = std::make_shared<ShapeButton>
            (sf::Vector2f(x_pos, separation+(separation+b_height)*1),
             sf::Vector2f(b_width, b_height), stopfun, stopShape);
    display.add_button(stopButton);

    //next button ########################
    sf::ConvexShape nextShape;
    nextShape.setPointCount(7);
    nextShape.setPoint(0, sf::Vector2f(0,0));
    nextShape.setPoint(1, sf::Vector2f(20,20));
    nextShape.setPoint(2, sf::Vector2f(20,0));
    nextShape.setPoint(3, sf::Vector2f(40,20));
    nextShape.setPoint(4, sf::Vector2f(20,40));
    nextShape.setPoint(5, sf::Vector2f(20,20));
    nextShape.setPoint(6, sf::Vector2f(0,40));
    nextShape.setFillColor(sf::Color::Black);
    nextShape.setOrigin(20,20);

    std::function<void(sf::Event)> nextfun = std::bind(&Game::next, this);
    std::shared_ptr<Button> nextButton = std::make_shared<ShapeButton>
            (sf::Vector2f(x_pos, separation + (separation+b_height)*2),
             sf::Vector2f(b_width, b_height), nextfun, nextShape);
    display.add_button(nextButton);

    //prev button ########################
    sf::ConvexShape prevShape;
    prevShape.setPointCount(7);
    prevShape.setPoint(0, sf::Vector2f(0,20));
    prevShape.setPoint(1, sf::Vector2f(20,0));
    prevShape.setPoint(2, sf::Vector2f(20,20));
    prevShape.setPoint(3, sf::Vector2f(40,0));
    prevShape.setPoint(4, sf::Vector2f(40,40));
    prevShape.setPoint(5, sf::Vector2f(20,20));
    prevShape.setPoint(6, sf::Vector2f(20,40));
    prevShape.setFillColor(sf::Color::Black);
    prevShape.setOrigin(20,20);

    std::function<void(sf::Event)> prevfun = std::bind(&Game::prev, this);
    std::shared_ptr<Button> prevButton = std::make_shared<ShapeButton>
            (sf::Vector2f(x_pos, separation + (separation+b_height)*3),
             sf::Vector2f(b_width, b_height), prevfun, prevShape);
    display.add_button(prevButton);

}

void Game::addTextBox()
{
    int x_pos = size*pixel_size+50;

    std::function<void(unsigned int)> textFun = std::bind(&Game::setFPS, this, std::placeholders::_1);
    std::shared_ptr<TextBox> textBox =
            make_shared<TextBox>(sf::Vector2f(x_pos, 500), sf::Vector2f(150, 50),
                                 textFun);
    display.set_textBox(textBox);
}















