#include <SFML/Graphics.hpp>

#include<vector>
#include <iostream>
#include <cmath>
#include <string>

int iTime = 0;

//clock to determine refresh rates
sf::Clock sfcProgramclock;

void FormatButton(sf::RectangleShape& Button, double thickness, sf::Color outline, sf::Color fill, float Xpos, float Ypos);
void FormatLabel(sf::Text& Label, std::string Text, int charactersize, sf::Color fill, float Xpos, float Ypos, sf::Font& Font);
void DisplayModel(std::vector<std::vector<sf::RectangleShape>> &DisplayValues, std::vector<std::vector<std::vector<float>>> &fModel, int i, int j, int t, int Xpos, int Ypos);
void InitialiseModel(std::vector<std::vector<std::vector<float>>> &Model);
void InitialiseDisplay(std::vector<std::vector<sf::RectangleShape>> &DisplayValues);
void InitialiseTempKey(std::vector<sf::RectangleShape> &TempKey, std::vector<sf::Text> &KeyLabel, sf::Font& font);
void CalcPoint(std::vector<std::vector<std::vector<float>>> &model, double r, int i, int j, int t);
void CalcInsulatedBoundary(std::vector<std::vector<std::vector<float>>> &Model, double r, int i, int j, int t, int boundary);

void Initialise(sf::Font &font, std::vector<sf::RectangleShape > &TempKey, std::vector<sf::Text> &KeyLabel, std::vector<std::vector<std::vector<float>>> &Model)
{
	InitialiseTempKey(TempKey, KeyLabel,font);
	InitialiseModel(Model);
}

//main function
int main()
{
	//Define 3-d vector for the numerical solution of the heat differential equation
	std::vector<std::vector<std::vector<float>>> fModel;
	//define vector to store details of every member of the calculation mesh, each point is a sfml class rectangle of size 2x2
	std::vector<std::vector<sf::RectangleShape>> sfrPosition(200, std::vector<sf::RectangleShape>(200));
	//Creates a vector to store rectangle shapes for each member cell of the temperature key
	std::vector<sf::RectangleShape> sfrTempKey(20);
	//Creates a vector to store strings for each member label of the temperature key
	std::vector<sf::Text> sftKeyLabels(20);

	//creates a window for the application
	sf::RenderWindow window(sf::VideoMode(520, 500), "2D Heat Transfer");
	sf::Event event;
	std::string sEnteredTimeSteps;
	sf::Font sffFont;
	//loads the arial font from the project file to use in the application
	if (!sffFont.loadFromFile("arial.ttf"))
	{
		return 0;
	}

	//define text variable to generate the string for the title  of the application
	sf::Text sftTitle;
	FormatLabel(sftTitle, "2-D Heat Transfer across a plane", 10, sf::Color::Color(0, 0, 0), 200, 10, sffFont);
	//define text variable to generate the string for the time step display
	sf::Text sftTimeStep;
	FormatLabel(sftTimeStep, "Time Step: 0", 8, sf::Color::Color(0, 0, 0), 160, 460, sffFont);
	//define text variable to label the Pause button
	sf::Text sftPauseButton;
	FormatLabel(sftPauseButton, "Pause", 8, sf::Color::Color(0, 0, 0), 460, 287, sffFont);
	//define text variable to label the Restart button
	sf::Text sftRestartButton;
	FormatLabel(sftRestartButton, "Unpause", 8, sf::Color::Color(0, 0, 0), 455, 312, sffFont);
	//define text variable to label the Stop button
	sf::Text sftStopButton;
	FormatLabel(sftStopButton, "Stop", 8, sf::Color::Color(0, 0, 0), 460, 337, sffFont);
	//define text variable to label the users choice of time step
	sf::Text sftTSchoice;
	FormatLabel(sftTSchoice, "Enter desired timestep", 8, sf::Color::Color(0, 0, 0), 430, 387, sffFont);
	//define text variable to label the start button
	sf::Text sftStartButton;
	FormatLabel(sftStartButton, "Start", 8, sf::Color::Color(0, 0, 0), 460, 262, sffFont);
	//define text variable to display the choice of time step that the user wants to display
	sf::Text sftUserEnteredTS;
	FormatLabel(sftUserEnteredTS, "-", 10, sf::Color::Color(0, 0, 0), 470, 402, sffFont);
	//define text variable to display the choice of time step that the user wants to display
	sf::Text sftSearchButton;
	FormatLabel(sftSearchButton, "Search", 8, sf::Color::Color(0, 0, 0), 460, 432, sffFont);

	//creates a square for the pause button
	sf::RectangleShape sfrPauseButton(sf::Vector2f(45, 15));
	FormatButton(sfrPauseButton, 2, sf::Color::Color(0, 0, 0), sf::Color::Color(240, 240, 240), 450, 285);
	//creates a square for the restart button
	sf::RectangleShape sfrRestartButton(sf::Vector2f(45, 15));
	FormatButton(sfrRestartButton, 2, sf::Color::Color(0, 0, 0), sf::Color::Color(240, 240, 240), 450, 310);
	//creates a square for the stop button
	sf::RectangleShape sfrStopButton(sf::Vector2f(45, 15));
	FormatButton(sfrStopButton, 2, sf::Color::Color(0, 0, 0), sf::Color::Color(240, 240, 240), 450, 335);
	//creates a square for the text box
	sf::RectangleShape sfrTextbox(sf::Vector2f(80, 20));
	FormatButton(sfrTextbox, 2, sf::Color::Color(0, 0, 0), sf::Color::Color(255, 255, 255), 435, 400);
	//creates a square for the start button
	sf::RectangleShape sfrStartButton(sf::Vector2f(45, 15));
	FormatButton(sfrStartButton, 2, sf::Color::Color(0, 0, 0), sf::Color::Color(240, 240, 240), 450, 260);
	//creates a square for the search button
	sf::RectangleShape sfrSearchButton(sf::Vector2f(45, 15));
	FormatButton(sfrSearchButton, 2, sf::Color::Color(0, 0, 0), sf::Color::Color(240, 240, 240), 450, 430);
	//creates a square for the display choice button
	sf::RectangleShape sfrDisplayChoice(sf::Vector2f(45, 15));
	
	InitialiseTempKey(sfrTempKey, sftKeyLabels, sffFont);
	InitialiseModel(fModel);
	InitialiseDisplay(sfrPosition);

	bool bPaused = false;
	bool bStopped = true;
	bool bEnteredTS = false;
	bool bSearch = false;
	int t = 0;

	sf::Vector2i vMousePosition;
	//event loop that checks the poll event queue to check for tasks for the application to perform
	while (window.isOpen())
	{
		//defines an event
		while (window.pollEvent(event))
		{
			//case to execute different events
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;

			case sf::Event::KeyReleased:
				if (bPaused == false && event.key.code == sf::Keyboard::Space)
				{
					bPaused = true;
				}
				else if (bPaused == true && event.key.code == sf::Keyboard::Space)
				{
					bPaused = false;
				}
				break;

			case sf::Event::MouseButtonPressed:
				vMousePosition = sf::Mouse::getPosition(window);
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//pause button
					if (495 > vMousePosition.x && vMousePosition.x > 450 && 300 > vMousePosition.y && vMousePosition.y > 285 && bPaused == false)
					{
						bPaused = true;
					}
					//unpause button
					else if (495 > vMousePosition.x && vMousePosition.x > 450 && 325 > vMousePosition.y && vMousePosition.y > 310 && bPaused == true)
					{
						bPaused = false;

					}
					//Stop button
					else if (495 > vMousePosition.x && vMousePosition.x > 450 && 350 > vMousePosition.y && vMousePosition.y > 335 && bStopped == false)
					{
						bStopped = true;
					}
					//Start button
					else if (495 > vMousePosition.x && vMousePosition.x > 450 && 275 > vMousePosition.y && vMousePosition.y > 260 && bStopped == true)
					{
						bStopped = false;
					}
					//user input
					else if (505 > vMousePosition.x && vMousePosition.x > 425 && 420 > vMousePosition.y && vMousePosition.y > 400 && bStopped == true)
					{
						bEnteredTS = true;
					}
					else if (495 > vMousePosition.x && vMousePosition.x > 450 && 445 > vMousePosition.y && vMousePosition.y > 430 && bStopped == true)
					{
						if (bSearch == true)
						{
							bSearch = false;
						}
						if (bEnteredTS == true && bStopped == true)
						{
							int iInputtedTime = std::stoi(sEnteredTimeSteps);
							if (iInputtedTime > 0)
							{
								iTime = iInputtedTime;
							}

							if (iTime < t)
							{
								bSearch = true;
							}
						}
					}
					else
					{
					bEnteredTS = false;
					}
				}
				break;

			case sf::Event::TextEntered:

				std::string sTemp;
				if (event.text.unicode == '\b' && bEnteredTS == true)
				{
					sEnteredTimeSteps = sEnteredTimeSteps.substr(0, sEnteredTimeSteps.size() - 1);
					sftUserEnteredTS.setString(sEnteredTimeSteps);
				}
				else if (event.text.unicode < 128 && bEnteredTS == true)
				{
					sTemp += static_cast<char>(event.text.unicode);
					sEnteredTimeSteps = sEnteredTimeSteps + sTemp;
					sftUserEnteredTS.setString(sEnteredTimeSteps);
				}
				break;
			}
		}

		window.clear(sf::Color::White);
		
		window.draw(sftTitle);
		sftTimeStep.setString("Time Step: " + std::to_string(t));
		window.draw(sfrStartButton);
		window.draw(sfrPauseButton);
		window.draw(sfrRestartButton);
		window.draw(sfrStopButton);
		window.draw(sfrTextbox);
		window.draw(sfrSearchButton);

		window.draw(sftPauseButton);
		window.draw(sftRestartButton);
		window.draw(sftStartButton);
		window.draw(sftStopButton);
		window.draw(sftTSchoice);
		window.draw(sftUserEnteredTS);
		window.draw(sftSearchButton);
		window.draw(sftTimeStep);
		
		for (int k = 0; k < 20; k++)
		{
			window.draw(sftKeyLabels[k]);
			window.draw(sfrTempKey[k]);
		} 

		const float r = 0.25;
		bool RHSInsulated = false;
		bool LHSInsulated = false;
		bool TOPInsulated = false;
		bool BOTInsulated = false;



		if (bPaused == false && bStopped == false)
		{

			//u(x,y,0)=0
			for (int i = 0; i < fModel.size(); i++)
			{
				for (int j = 0; j < fModel[i].size(); j++)
				{
					if (!(i == 0 || j == 0 || i == fModel.size() - 1 || j == fModel[i].size() - 1))
					{
						CalcPoint(fModel, r, i, j, t);
					}
					else if (i == fModel[i].size() - 1 && RHSInsulated == true)
					{
						CalcInsulatedBoundary(fModel, r, i, j, t,0);
					}
				
					else if (i == 0 && LHSInsulated== true )
					{
						CalcInsulatedBoundary(fModel, r, i, j, t, 1);
					}
					else if (j == fModel[i].size() - 1)
					{
						CalcInsulatedBoundary(fModel, r, i, j, t, 2);
					}
					else if (j == 0)
					{
						CalcInsulatedBoundary(fModel, r, i, j, t, 3);
					} 
					else
					{
						fModel[i][j].push_back(fModel[i][j][t]);
					}
					DisplayModel(sfrPosition,fModel,i, j, t,20,40);
					//draws point to the screen
					window.draw(sfrPosition[i][j]);
				}
			}
			++t;
			window.display();
			sfcProgramclock.restart();
		}
		else if (bStopped == true && bSearch == false)
		{
			for (int i = 0; i < fModel.size(); i++)
			{
				for (int j = 0; j < fModel[i].size(); j++)
				{
					DisplayModel(sfrPosition, fModel, i, j, iTime,20,40);
					//draws point to the screen
					window.draw(sfrPosition[i][j]);
				}
			}
			window.draw(sftUserEnteredTS);
			window.display();
		}
		else if (bStopped == true && bSearch == true)
		{
			for (int i = 0; i < fModel.size(); i++)
			{
				for (int j = 0; j < fModel[i].size(); j++)
				{
					DisplayModel(sfrPosition, fModel, i, j, iTime,20,40);
					//draws point to the screen

					window.draw(sfrPosition[i][j]);
				}
			}
			sftTimeStep.setString("Time Step: " + std::to_string(iTime));
			window.display();
		}
	}
	//end of main window loop
	return 0;
}


