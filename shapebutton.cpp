#include "shapebutton.h"

#include <iostream>


ShapeButton::ShapeButton(sf::Vector2f pos, sf::Vector2f size,
                         std::function<void (sf::Event)> callback, sf::ConvexShape i_shape)
    : Button(pos, size, callback)
{
    sf::Vector2f shapePosition = sf::Vector2f(rectangle.getPosition().x + rectangle.getSize().x/2,
                                             rectangle.getPosition().y + rectangle.getSize().y/2);

    shape = i_shape;
    shape.setPosition(shapePosition);
    shape.setFillColor(sf::Color::Black);
}

void ShapeButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rectangle, states);
    target.draw(shape, states);
}
