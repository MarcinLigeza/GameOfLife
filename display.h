#ifndef DISPLAY_H
#define DISPLAY_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "button.h"
#include "textbox.h"

class Display
{
public:
    Display();
    Display(int i_size, int pixel_size, std::shared_ptr<sf::RenderWindow> i_target);

    void add_button(std::shared_ptr<Button> but);
    void set_textBox(std::shared_ptr<TextBox> box);

    void onClick(sf::Event e);
    void onTextEntered(sf::Event &event);
    void onEnterPressed(sf::Event &event);

    void draw(std::vector<std::vector<char>> board);
    void setFPS(unsigned int i_fps);

private:
    std::vector<std::shared_ptr<Button>> buttons;
    std::shared_ptr<TextBox> textBox;

    std::shared_ptr<sf::RenderWindow> target;
    int size;
    int pixel_size;
    unsigned int fps;
};

#endif // DISPLAY_H
