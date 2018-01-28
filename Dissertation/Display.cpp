#include <SFML/Graphics.hpp>
#include <vector>



sf::Color GetTempColour(float fTemp)
{
	const float pi = 3.141592653;

	// Calc goes here
	int iRed, iGreen, iBlue;


	iRed = 255 * pow((fTemp / 100), 2);
	iGreen = 255 * sin((fTemp / 100)*pi);
	iBlue = 255 * (pow((fTemp / 100), 2) - 2 * (fTemp / 100) + 1);

	return sf::Color(iRed, iGreen, iBlue);
}

void DisplayModel(std::vector<std::vector<sf::RectangleShape>> &DisplayValues, std::vector<std::vector<std::vector<float>>> &fModel, int i, int j, int t, int Xpos, int Ypos)
{
	//sets the colour of the point
	DisplayValues[i][j].setFillColor(GetTempColour(fModel[i][j][t]));
	//defines location of each point on application
	DisplayValues[i][j].setPosition(Xpos + (i * 2), Ypos + (j * 2));
}


