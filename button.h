#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <functional>

class Button : public sf::Drawable
{
public:
    Button(sf::Vector2f i_position, sf::Vector2f i_size,
           std::function<void(sf::Event)>);

    virtual bool onClick(sf::Event e);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

    sf::Color bg_Color;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::RectangleShape rectangle;

    std::function<void(sf::Event)> callback;

};

#endif // BUTTON_H
