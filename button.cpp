#include "button.h"

#include <iostream>


Button::Button(sf::Vector2f i_position, sf::Vector2f i_size,
               std::function<void (sf::Event)> i_callback)
{
    position = i_position;
    size = i_size;
    callback = i_callback;

    bg_Color = sf::Color::Cyan;
    rectangle = sf::RectangleShape(size);
    rectangle.setPosition(position);
    rectangle.setFillColor(bg_Color);
}

bool Button::onClick(sf::Event e)
{
    if((e.mouseButton.x >= rectangle.getPosition().x) &&
            (e.mouseButton.x <= rectangle.getPosition().x + rectangle.getSize().x))
    {
        if((e.mouseButton.y >= rectangle.getPosition().y) &&
                (e.mouseButton.y <= rectangle.getPosition().y + rectangle.getSize().y))
        {
            std::cout << "button clicked" << "\n";
            callback(e);
            return true;
        }
    }
    return false;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rectangle, states);
}
