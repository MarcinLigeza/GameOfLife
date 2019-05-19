#include "textbutton.h"
#include "iostream"

TextButton::TextButton()
{

}

TextButton::TextButton(std::string itext, sf::Font& ifont, sf::Vector2f pos, sf::Vector2f isize)
{
    position = pos;
    size = isize;
    font = ifont;

    bg_Color = sf::Color::Cyan;
    text_Color = sf::Color::Black;

    text.setString(itext);
    text.setFont(font);
    text.setOrigin(text.getGlobalBounds().width*0.5f, text.getGlobalBounds().height * 0.6f);

    rectangle = sf::RectangleShape(isize);
    rectangle.setPosition(pos);
    rectangle.setFillColor(bg_Color);

    sf::Vector2f textPosition = sf::Vector2f(rectangle.getPosition().x + rectangle.getSize().x/2,
                                             rectangle.getPosition().y + rectangle.getSize().y/2);
    text.setPosition(textPosition);
    text.setFillColor(text_Color);

}

bool TextButton::isPressed(sf::Event e)
{
      if((e.mouseButton.x >= rectangle.getPosition().x) &&
              (e.mouseButton.x <= rectangle.getPosition().x + rectangle.getSize().x))
      {
          if((e.mouseButton.y >= rectangle.getPosition().y) &&
                  (e.mouseButton.y <= rectangle.getPosition().y + rectangle.getSize().y))
          {
              std::cout << "text button clicked\n";
              return true;
          }
      }
      return false;
}

void TextButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rectangle, states);
    target.draw(text);
}

