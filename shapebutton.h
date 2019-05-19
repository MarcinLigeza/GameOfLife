#ifndef SHAPEBUTTON_H
#define SHAPEBUTTON_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class ShapeButton : public sf::Drawable
{
public:
    ShapeButton();
    ShapeButton(sf::ConvexShape shape, sf::Vector2f pos, sf::Vector2f size);

    bool isPressed(sf::Event e);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Color bg_Color;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::RectangleShape rectangle;

    sf::ConvexShape shape;
};

#endif // SHAPEBUTTON_H
