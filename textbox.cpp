#include "textbox.h"

#include <boost/lexical_cast.hpp>

#include <iostream>


TextBox::TextBox(sf::Vector2f i_position, sf::Vector2f i_size,
                 std::function<void(unsigned int)> i_callback)
{
    isActive = false;

    position = i_position;
    size = i_size;
    callback = i_callback;

    out_color = sf::Color(183,183,183);
    in_color = sf::Color(201,201,201);
    active_in_color = sf::Color(240,240,240);

    out_rectangle = sf::RectangleShape(size);
    out_rectangle.setPosition(position);
    out_rectangle.setFillColor(out_color);

    in_rectangle = sf::RectangleShape(sf::Vector2f(size.x-10, size.y-10));
    in_rectangle.setPosition(position.x+5, position.y+5);
    in_rectangle.setFillColor(in_color);

    font.loadFromFile("../GameOfLife/OpenSans.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setOrigin(text.getGlobalBounds().width*0.5f, text.getGlobalBounds().height * 0.5f);

    sf::Vector2f textPosition = sf::Vector2f(in_rectangle.getPosition().x,
                                             in_rectangle.getPosition().y);
    text.setPosition(textPosition);

    input.clear();
}

void TextBox::onTextEntered(sf::Event e)
{
    if(isActive)
    {
        input += e.text.unicode;
        text.setString(input);
    }
}

void TextBox::onEnterPressed(sf::Event e)
{
    if(!(text.getString().toAnsiString() == ""))
    {
        std::string number = text.getString().toAnsiString();
        std::cout << "Number FPS: " << number << "\n";
        callback(boost::lexical_cast<int>(number));
        input.clear();
        text.setString(input);
    }
    isActive = false;
    in_rectangle.setFillColor(in_color);
}

void TextBox::onClick(sf::Event e)
{
    if((e.mouseButton.x >= in_rectangle.getPosition().x) &&
            (e.mouseButton.x <= in_rectangle.getPosition().x + in_rectangle.getSize().x))
    {
        if((e.mouseButton.y >= in_rectangle.getPosition().y) &&
                (e.mouseButton.y <= in_rectangle.getPosition().y + in_rectangle.getSize().y))
        {
            std::cout << "textbox clicked" << "\n";
            isActive = true;
            in_rectangle.setFillColor(active_in_color);
        }
    }
}

void TextBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(out_rectangle);
    target.draw(in_rectangle);
    target.draw(text);

}
