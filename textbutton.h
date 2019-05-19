#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "button.h"

class TextButton : public Button
{
public:
    TextButton(sf::Vector2f pos, sf::Vector2f size,
               std::function<void(sf::Event)>, std::string text);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Color text_Color;

    sf::Font font;
    uint font_Size;
    sf::Text text;

};

#endif // BUTTON_H
