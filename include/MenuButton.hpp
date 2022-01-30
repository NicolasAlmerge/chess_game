#pragma once
#include <SFML/Graphics.hpp>
#include <string> 
using namespace sf;

class MenuButton {
    int m_index;
    // Texture texture;
    Sprite m_sprite{};
    RectangleShape m_rectangle{};
    Text m_text{};
    std::string m_string;
    bool m_isRotatable;

    void handleRectangle(uint8_t);
    void handleSprite(uint8_t);
    void handleText(uint8_t);

    public: 
    MenuButton(uint8_t, bool, const std::string&);
    RectangleShape getRectangle() { return m_rectangle; }; 
    Sprite getSprite() { return m_sprite; };
    Text getText() { return m_text; };
    void setSpriteTexture(Texture& texture) { m_sprite.setTexture(texture); };
    void drawMenuButton(RenderWindow&); 
};