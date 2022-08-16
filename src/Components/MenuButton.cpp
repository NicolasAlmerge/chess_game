#include "../../include/Components/MenuButton.hpp"
#include "../../include/GameThread.hpp"
#include "../../include/Utilities/MoveList.hpp"
#include "../../include/Utilities/DrawableSf.hpp"

namespace 
{
    const Color transitionColors[5] =
    {
        { 218, 224, 242 }, { 218, 224, 145 }, { 218, 224, 200 },
        { 218, 224, 45 }, { 218, 224, 242 }
    };

    void handleRectangle(uint8_t i_, RectangleShape& rectangle_)
    {
        DrawableSf::drawRectangleSf(rectangle_, g_BUTTON_POS*i_, 0, { g_BUTTON_POS, g_MENUBAR_HEIGHT }, { 23,23,23 });
        rectangle_.setOutlineThickness(2.f);
        rectangle_.setOutlineColor({ 239, 242, 249 });
    }

    void handleSprite(uint8_t i_, Sprite& sprite_)
    {
        sprite_.setOrigin(g_BUTTON_SIZE/2, g_BUTTON_SIZE/2);
        sprite_.setPosition(g_BUTTON_POS*i_ + 20, g_MENUBAR_HEIGHT/2);
        sprite_.setScale(g_SPRITE_SCALE, g_SPRITE_SCALE);
    }

    void handleText(uint8_t i, Text& text_)
    {
        text_.setStyle(Text::Bold);
        text_.setFillColor(Color(240, 248, 255));
        text_.setOrigin(g_BUTTON_SIZE/2 - g_BUTTON_POS/3, g_BUTTON_SIZE/1.75);
        text_.setPosition(g_BUTTON_POS*i + g_BUTTON_POS/3, g_MENUBAR_HEIGHT);
    }

    void rotateIcon(Sprite& sprite_)
    {
        sprite_.setRotation(sprite_.getRotation() + 180);
    }
}

MenuButton::MenuButton(uint8_t index_, const std::string& name_, bool isRotatable_)
: m_index(index_), m_isRotatable(isRotatable_)
{
    auto font = RessourceManager::getFont("Arial.ttf");
    m_text.setString(name_);
    m_text.setFont(*font);
    m_text.setCharacterSize(14);

    handleRectangle(index_, m_rectangle);
    handleSprite(index_, m_sprite);
    handleText(index_, m_text);
}

void MenuButton::drawMenuButton(RenderWindow& window_) const
{
    window_.draw(m_rectangle);
    window_.draw(m_sprite);
    window_.draw(m_text);
}

bool MenuButton::isClicked(coor2d& mousePos_) const
{
    float xi = m_rectangle.getGlobalBounds().left;
    float xf = xi + m_rectangle.getGlobalBounds().width;
    return mousePos_.first >= xi && mousePos_.first < xf;
}

void MenuButton::doColorTransition()
{
    m_transitionColorIndex += 5;
    sf::Uint8 i = (sf::Uint8)m_transitionColorIndex;
    m_rectangle.setFillColor({ (sf::Uint8) (218-i), (sf::Uint8) (224-i), (sf::Uint8) (241-i) });

    if (m_transitionColorIndex == 45)
    {
        m_isColorTransitioning = false;
        m_transitionColorIndex = 0;
        m_rectangle.setFillColor({ 218, 224, 241 });
    }
}

int MenuButton::performClick(Board& game_, MoveList& moveList_)
{
    switch (m_index)
    {
        case 0:
            // Clicked menu button
            rotateIcon(m_sprite);
            break;
        case 1:
            // Clicked reset button
            game_.reset();
            moveList_.reset();

            break;
        case 2:
            // Clicked flip button
            GameThread::flipBoard();
            m_isColorTransitioning = true;
            break;
    }
    // make clicking shadow flashing animation
    m_isColorTransitioning = true;
    return m_index;
}
