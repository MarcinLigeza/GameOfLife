#ifndef DISPLAY_H
#define DISPLAY_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "button.h"

class Display
{
public:
    Display(int i_size, int pixel_size, std::shared_ptr<sf::RenderWindow> i_target);

    void add_button(std::shared_ptr<Button> but);
    void onClick(sf::Event e);
    void draw(std::vector<std::vector<char>> board);

private:
    std::vector<std::shared_ptr<Button>> buttons;
    std::shared_ptr<sf::RenderWindow> target;
    int size;
    int pixel_size;
};

#endif // DISPLAY_H
