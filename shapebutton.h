#ifndef SHAPEBUTTON_H
#define SHAPEBUTTON_H

#include "button.h"

class ShapeButton : public Button
{
public:
    ShapeButton(sf::Vector2f pos, sf::Vector2f size,
                std::function<void(sf::Event)>, sf::ConvexShape i_shape);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::ConvexShape shape;
};

#endif // SHAPEBUTTON_H
