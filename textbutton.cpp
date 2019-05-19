#include "textbutton.h"
#include "iostream"

TextButton::TextButton(sf::Vector2f pos, sf::Vector2f size,
                       std::function<void (sf::Event)> callback, std::string i_text)
    : Button(pos, size, callback)
{
    font.loadFromFile("../GameOfLife/OpenSans.ttf");

    text_Color = sf::Color::Black;

    text.setString(i_text);
    text.setFont(font);
    text.setOrigin(text.getGlobalBounds().width*0.5f, text.getGlobalBounds().height * 0.6f);

    sf::Vector2f textPosition = sf::Vector2f(rectangle.getPosition().x + rectangle.getSize().x/2,
                                             rectangle.getPosition().y + rectangle.getSize().y/2);
    text.setPosition(textPosition);
    text.setFillColor(text_Color);

}

void TextButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rectangle, states);
    target.draw(text);
}

