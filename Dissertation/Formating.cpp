#include <SFML/Graphics.hpp>
#include <vector>

void FormatButton(sf::RectangleShape& Button, double thickness, sf::Color outline, sf::Color fill, float Xpos, float Ypos)
// This sub procedure formats every button on the application
{
	Button.setOutlineThickness(2);
	Button.setOutlineColor(outline);
	Button.setFillColor(fill);
	Button.setPosition(Xpos, Ypos);

}


void FormatLabel(sf::Text& Label, std::string Text,  int charactersize, sf::Color fill , float Xpos, float Ypos, sf::Font& Font)
// This sub procedure formats every text on the application
{
	Label.setFont(Font);
	Label.setString(Text);
	Label.setCharacterSize(charactersize);
	Label.setFillColor(fill);
	//set position of the string
	Label.setPosition(Xpos, Ypos);
	

}
