#include <SFML/Graphics.hpp>
#include <vector>

sf::Color GetTempColour(float fTemp);

void InitialiseDisplay(std::vector<std::vector<sf::RectangleShape>> &DisplayValues)
{
	sf::RectangleShape sfrPoint(sf::Vector2f(2, 2));
	
	for (int i = 0; i < 200; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			//loop designed to generate visual representation of the mesh 200 points by 200 points
			DisplayValues[i][j] = sfrPoint;
		}
	}
}

void InitialiseModel(std::vector<std::vector<std::vector<float>>> &Model)
{
	//sets length dimension  
	Model.resize(200);
	for (int i = 0; i < Model.size(); ++i)
	{
		//sets width dimension
		Model[i].resize(200);
		for (int j = 0; j < Model[i].size(); ++j)
		{
			//sets time dimension
			Model[i][j].resize(1);
			Model[i][j][0] = 0;
		}

	}

	//set the models boundary conditions
	//u(x,0,t)=0
	for (int i = 0; i < Model.size(); ++i)
	{
		Model[i][0][0] = 25;
		Model[i][199][0] = 25;
	}
	//u(0,y,t)=100
	for (int j = 0; j < 200; ++j)
	{
		Model[0][j][0] = 100;
		Model[199][j][0] = 100;
	}


}

void InitialiseTempKey(std::vector<sf::RectangleShape> &TempKey, std::vector<sf::Text> &KeyLabel, sf::Font &font)
{

	//creates a general cell for the temperature key of size 10x10
	sf::RectangleShape sfrTempKeyStep(sf::Vector2f(10, 10));
	//creates a general label for the key
	sf::Text sftGeneralKeyLabel;


	//defines left edge of temperature key cells
	int iXpos = 460;
	//defines top of temperature key cells
	int iYpos = 40;


	for (int k = 0; k < 20; ++k)
	{
		//Save each cell and label as members of the dynamic vectors
		TempKey[k] = sfrTempKeyStep;
		KeyLabel[k] = sftGeneralKeyLabel;

		//define positions of each cell and its label
		TempKey[k].setPosition(iXpos, iYpos + (k * 10));
		KeyLabel[k].setPosition(iXpos + 20, iYpos + (k * 10));

		//define attributes of the cells of the temperature key
		TempKey[k].setOutlineColor(sf::Color::Black);
		TempKey[k].setOutlineThickness(1);

		//Define attributes of the labels for the temperature key
		KeyLabel[k].setFont(font);
		KeyLabel[k].setCharacterSize(10);
		KeyLabel[k].setFillColor(sf::Color::Black);

		//each case of the switch changes the colour of the key cell and the text of the label
		switch (k)
		{
		case 0:
			TempKey[k].setFillColor(GetTempColour(2.5));
			KeyLabel[k].setString("0-5");
			break;
		case 1:
			TempKey[k].setFillColor(GetTempColour(7.5));
			KeyLabel[k].setString("5-10");
			break;
		case 2:
			TempKey[k].setFillColor(GetTempColour(12.5));
			KeyLabel[k].setString("10-15");
			break;
		case 3:
			TempKey[k].setFillColor(GetTempColour(17.5));
			KeyLabel[k].setString("15-20");
			break;
		case 4:
			TempKey[k].setFillColor(GetTempColour(22.5));
			KeyLabel[k].setString("20-25");
			break;
		case 5:
			TempKey[k].setFillColor(GetTempColour(27.5));
			KeyLabel[k].setString("25-30");
			break;
		case 6:
			TempKey[k].setFillColor(GetTempColour(32.5));
			KeyLabel[k].setString("30-35");
			break;
		case 7:
			TempKey[k].setFillColor(GetTempColour(37.5));
			KeyLabel[k].setString("35-40");
			break;
		case 8:
			TempKey[k].setFillColor(GetTempColour(42.5));
			KeyLabel[k].setString("40-45");
			break;
		case 9:
			TempKey[k].setFillColor(GetTempColour(47.5));
			KeyLabel[k].setString("45-50");
			break;
		case 10:
			TempKey[k].setFillColor(GetTempColour(52.5));
			KeyLabel[k].setString("50-55");
			break;
		case 11:
			TempKey[k].setFillColor(GetTempColour(57.5));
			KeyLabel[k].setString("55-60");
			break;
		case 12:
			TempKey[k].setFillColor(GetTempColour(62.5));
			KeyLabel[k].setString("60-65");
			break;
		case 13:
			TempKey[k].setFillColor(GetTempColour(67.5));
			KeyLabel[k].setString("65-70");
			break;
		case 14:
			TempKey[k].setFillColor(GetTempColour(72.5));
			KeyLabel[k].setString("70-75");
			break;
		case 15:
			TempKey[k].setFillColor(GetTempColour(77.5));
			KeyLabel[k].setString("75-80");
			break;
		case 16:
			TempKey[k].setFillColor(GetTempColour(82.5));
			KeyLabel[k].setString("80-85");
			break;
		case 17:
			TempKey[k].setFillColor(GetTempColour(87.5));
			KeyLabel[k].setString("85-90");
			break;
		case 18:
			TempKey[k].setFillColor(GetTempColour(92.5));
			KeyLabel[k].setString("90-95");
			break;
		case 19:
			TempKey[k].setFillColor(GetTempColour(97.5));
			KeyLabel[k].setString("95-100");
			break;
		}

	}
	return;
}