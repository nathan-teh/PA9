///////////////////////////////////////////////////////////////////////////////
/// \file         Button.hpp
/// \author       Tifanie Ngo
/// \date         4/20/25
/// \brief        This file sets up the play button for the title screen of
///               Yo-Ho Jump!
///////////////////////////////////////////////////////////////////////////////

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

using namespace std;

class Button : public sf::RectangleShape
{
public:
///////////////////////////////////////////////////////////////////////
/// Button(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& color)
/// \pre     none
/// \post    button initialized, positioned with given fill color
/// \param   size (width & height of button); pos (screen position for button); color 
///              (fill color of button)
/// \return  none
/// \throw   none
///////////////////////////////////////////////////////////////////////
	Button(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Color& color) :
		sf::RectangleShape(size)
	{
		this->setFillColor(color);
		this->setPosition(pos);
	}

///////////////////////////////////////////////////////////////////////
/// setBackColor(sf::Color color)
/// \pre     none
/// \post    button's fill color updated
/// \param   color (fill color for button)
/// \return  none
/// \throw   none
///////////////////////////////////////////////////////////////////////
	void setBackColor(sf::Color color)
	{
		this->setFillColor(color);
	}

///////////////////////////////////////////////////////////////////////
/// isMouseOverButton(sf::RenderWindow& window)
/// \pre     valid SFML RenderWindow passed
/// \post    returns true if mouse position overlaps button bounds
/// \param   window (reference to SFML render window for mouse position)
/// \return  true if button registers mouse hovering under it (otherwise false)
/// \throw   none
///////////////////////////////////////////////////////////////////////
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

#endif // BUTTON_HPP