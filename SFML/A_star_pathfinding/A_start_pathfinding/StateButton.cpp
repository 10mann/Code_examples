#include "StateButton.h"

// ========================== Constructors ==========================
StateButton::StateButton(sf::Vector2f pos, sf::Vector2f size, std::string buttonText, sf::Font& font, sf::Color defaultColor, sf::Color hoverColor, sf::Color activeColor)
    : defaultColor(defaultColor), activeColor(activeColor), active(false)
{
    this->box.setPosition(pos);
    this->box.setSize(size);
    this->box.setOutlineThickness(1.0f);
    this->box.setOutlineColor(sf::Color::Black);
    this->box.setFillColor(this->defaultColor);

    this->text.setFont(font);
    this->text.setString(buttonText);
    this->text.setCharacterSize(22);
    this->text.setFillColor(sf::Color::Black);
    this->text.setPosition(this->box.getPosition() + sf::Vector2f((this->box.getSize().x - this->text.getGlobalBounds().width) / 2.0f, this->text.getCharacterSize() / 2.2f));
}

StateButton::~StateButton()
{

}

// ========================== Functions ==========================
const bool& StateButton::isActive()
{
    return this->active;
}

const bool StateButton::isPressed(const sf::Vector2f& mousePos)
{
    if (this->box.getGlobalBounds().contains(mousePos))
    {
        this->active = !this->active;

        if (this->active)
        {
            std::cout << "Setting color: " << this->activeColor.r << std::endl;
            this->box.setFillColor(this->activeColor);
        }
        else
        {
            std::cout << "Setting color: " << this->activeColor.r << std::endl;
            this->box.setFillColor(this->defaultColor);
        }
        std::cout << "Box: " << this->box.getSize().x << ", " << this->box.getSize().y << std::endl;
        return true;
    }

    return false;
}

void StateButton::update(const sf::Vector2f& mousePos)
{
    if (this->active)
    {
        
    }
    else
    {
        
    }
}

void StateButton::render(sf::RenderWindow* window)
{
    window->draw(this->box);
    window->draw(this->text);
}
