#include "shapebutton.h"

#include <iostream>

ShapeButton::ShapeButton()
{

}

ShapeButton::ShapeButton(sf::ConvexShape ishape, sf::Vector2f ipos, sf::Vector2f isize)
{
    shape = ishape;
    position = ipos;
    size = isize;

    bg_Color = sf::Color::Cyan;

    rectangle = sf::RectangleShape(size);
    rectangle.setPosition(position);
    rectangle.setFillColor(bg_Color);

    sf::Vector2f shapePosition = sf::Vector2f(rectangle.getPosition().x + rectangle.getSize().x/2,
                                             rectangle.getPosition().y + rectangle.getSize().y/2);
    shape.setPosition(shapePosition);

}

bool ShapeButton::isPressed(sf::Event e)
{
    if((e.mouseButton.x >= rectangle.getPosition().x) &&
            (e.mouseButton.x <= rectangle.getPosition().x + rectangle.getSize().x))
    {
        if((e.mouseButton.y >= rectangle.getPosition().y) &&
                (e.mouseButton.y <= rectangle.getPosition().y + rectangle.getSize().y))
        {
            std::cout << "shape button clicked\n";
            return true;
        }
    }
    return false;
}

void ShapeButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rectangle,states);
    target.draw(shape, states);
}
