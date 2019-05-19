#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>


class TextButton : public sf::Drawable
{
public:
    TextButton();
    TextButton(std::string text, sf::Font& font, sf::Vector2f pos, sf::Vector2f size);

    bool isPressed(sf::Event e);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Color bg_Color;
    sf::Color text_Color;

    sf::Vector2f position;
    sf::Vector2f size;

    sf::Font font;
    uint font_Size;
    sf::Text text;

    sf::RectangleShape rectangle;

};

#endif // BUTTON_H
