#pragma once
#include <SFML/Graphics.hpp>

class Button : public Text {
    void centerOrigin() {
        FloatRect bounds = getLocalBounds();
        setOrigin({ bounds.size.x / 2, bounds.size.y / 2 });
    }
public:
    Button(const Font& font, String string = "", unsigned int characterSize = 30) : Text(font, string, characterSize)
    {
        setFillColor(sf::Color::White);
        centerOrigin();
    }
};