#include "display.h"

Display::Display()
{

}

Display::Display(int i_size, int i_pixel_size, std::shared_ptr<sf::RenderWindow> i_target)
{
    target = i_target;
    size = i_size;
    pixel_size = i_pixel_size;
}

void Display::onClick(sf::Event e)
{
    for(auto& i : buttons)
        i->onClick(e);
}

void Display::draw(std::vector<std::vector<char> > board)
{
    sf::RectangleShape rec(sf::Vector2f(pixel_size, pixel_size));
    rec.setFillColor(sf::Color::Blue);

    target->clear(sf::Color::White);

    for(int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(board[i][j] == 'o')
            {
                rec.setPosition(j*pixel_size, i*pixel_size);
                target->draw(rec);
            }
        }
    }

    for(auto& i : buttons)
        target->draw(*i);
}

void Display::setFPS(unsigned int fps)
{
    target->setFramerateLimit(fps);
}

void Display::add_button(std::shared_ptr<Button> but)
{
    buttons.push_back(but);
}
