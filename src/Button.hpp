///////////////////////////////////////////////////////////////////////////////
/// \file         Button.hpp
/// \author       Tifanie Ngo
/// \date         4/20/25
/// \brief        This file sets up the play button for the title screen of
///               Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

using namespace std;
//using namespace sf;

class Button : public sf::RectangleShape
{
public:
	Button(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& color) :
		sf::RectangleShape(size)
	{
		this->setFillColor(color);
		this->setPosition(pos);
	}

	void setBackColor(sf::Color color)
	{
		this->setFillColor(color);
	}

	bool isMouseOverButton(sf::RenderWindow& window)
	{
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = this->getPosition().x;
		float btnPosY = this->getPosition().y;

		float x2 = btnPosX + this->getSize().x;
		float y2 = btnPosY + this->getSize().y;
		
		if (mouseX >= btnPosX && mouseX <= x2 && mouseY >= btnPosY && mouseY <= y2) return true;
		return false;
	}
};