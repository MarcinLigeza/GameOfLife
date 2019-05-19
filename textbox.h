#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <functional>

class TextBox : public sf::Drawable
{
public:
    TextBox(sf::Vector2f i_position, sf::Vector2f i_size,
            std::function<void (unsigned int)> callback);
    void onTextEntered(sf::Event e);
    void onEnterPressed(sf::Event e);
    void onClick(sf::Event e);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool isActive;

    std::function<void(unsigned int)> callback;

    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color out_color;
    sf::Color in_color;
    sf::Color active_in_color;
    sf::RectangleShape out_rectangle;
    sf::RectangleShape in_rectangle;

    sf::String input;

    sf::Text text;
    sf::Font font;
};

#endif // TEXTBOX_H
