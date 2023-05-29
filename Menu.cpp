#include "Menu.h"


Menu::Menu(int w, int h, sf::RenderWindow* win)
	: width(w), height(h), window(win)
{
	if (!font.loadFromFile("Modern.ttf"))
	{
		std::cout << "Failed to load font.";
	}

	font_size = height / 12;
	x_pos = width / 10;
	y_pos_unit = height / (2 * BUTTONS_NUMBER);

	for (int i = 0; i < BUTTONS_NUMBER; ++i)
	{
		selectedButtonIndex = i;
		buttons[i].setFont(font);

		if (i == 0) highlightButton();
		else unhighlightButton();
	}

	selectedButtonIndex = 0;
	buttons[0].setString("Play");
	buttons[1].setString("Ranking");
	buttons[2].setString("Exit");
}

Menu::Menu()
{

}

void Menu::drawMenu()
{
	window->clear();
	for (int i = 0; i < BUTTONS_NUMBER; ++i)
	{
		window->draw(buttons[i]);
	}
	window->display();
}

void Menu::upKeyAction()
{
	if (selectedButtonIndex - 1 >= 0)
	{
		unhighlightButton();
		selectedButtonIndex--;
		highlightButton();
	}
}

void Menu::downKeyAction()
{
	if (selectedButtonIndex + 1 < BUTTONS_NUMBER)
	{
		unhighlightButton();
		selectedButtonIndex++;
		highlightButton();
	}
}

void Menu::enterKeyAction()
{
	switch (selectedButtonIndex)
	{
	case 0:
		playButtonAction();
		break;

	case 1:
		rankingButtonAction();
		break;

	case 2:
		window->close();
		break;
	}
}

void Menu::playButtonAction()
{
	ChooseGameMenu* choose_game_menu;
	choose_game_menu = new ChooseGameMenu{ width, height, window };

	while (!choose_game_menu->returnButtonPressed())
	{
		choose_game_menu->run();
	}

	delete choose_game_menu;
}

void Menu::rankingButtonAction()
{
	int index = 0;
	int modes_number = 3;
	std::vector <Ranking*> rankings{ 3 };

	for (int i = 0; i < modes_number; ++i)
	{
		std::string file_name = "scores" + std::to_string(i) + ".txt";
		rankings[i] = new Ranking{ width, height, window, file_name };
	}

	while (!rankings[index]->escapeClicked())
	{
		rankings[index]->run();
		if (rankings[index]->rightClicked())
		{
			index = (index + 1) % modes_number;
		}
		else if (rankings[index]->leftClicked())
		{
			index = (index + modes_number - 1) % modes_number;
		}
	}

	for (int i = 0; i < rankings.size(); ++i)
	{
		delete rankings[i];
	}
}

void Menu::highlightButton()
{
	y_pos = y_pos_unit * (BUTTONS_NUMBER + selectedButtonIndex) - (1.5 * font_size);

	buttons[selectedButtonIndex].setFillColor(sf::Color::Red);
	buttons[selectedButtonIndex].setCharacterSize(font_size * 2);
	buttons[selectedButtonIndex].setPosition(sf::Vector2f(x_pos, y_pos));
}

void Menu::unhighlightButton()
{
	y_pos = y_pos_unit * (BUTTONS_NUMBER + selectedButtonIndex) - (0.75 * font_size);

	buttons[selectedButtonIndex].setFillColor(sf::Color::White);
	buttons[selectedButtonIndex].setCharacterSize(font_size);
	buttons[selectedButtonIndex].setPosition(sf::Vector2f(x_pos, y_pos));
}

int Menu::getSelectedButtonIndex()
{
	return selectedButtonIndex;
}

void Menu::run()
{
	sf::Event event;

	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				upKeyAction();
				break;

			case sf::Keyboard::Down:
				downKeyAction();
				break;

			case sf::Keyboard::Enter:
				enterKeyAction();
				break;
			}
		}
	}

	drawMenu();
}





ChooseGameMenu::ChooseGameMenu(int w, int h, sf::RenderWindow* win)
	: width(w), height(h), window(win)
{
	if (!font.loadFromFile("Modern.ttf"))
	{
		std::cout << "Failed to load font.";
	}

	font_size = height / 12;
	x_pos = width / 10;
	y_pos_unit = height / (2 * BUTTONS_NUMBER);

	for (int i = 0; i < BUTTONS_NUMBER; ++i)
	{
		selectedButtonIndex = i;
		buttons[i].setFont(font);

		if (i == 0) highlightButton();
		else unhighlightButton();
	}

	std::cout << font_size << x_pos;

	selectedButtonIndex = 0;
	return_pressed = false;

	buttons[0].setString("New game");
	buttons[1].setString("Load saved game");
	buttons[2].setString("Return");
}

void ChooseGameMenu::drawMenu()
{
	window->clear();
	for (int i = 0; i < BUTTONS_NUMBER; ++i)
	{
		window->draw(buttons[i]);
	}
	window->display();
}

void ChooseGameMenu::upKeyAction()
{
	if (selectedButtonIndex - 1 >= 0)
	{
		unhighlightButton();
		selectedButtonIndex--;
		highlightButton();
	}
}

void ChooseGameMenu::downKeyAction()
{
	if (selectedButtonIndex + 1 < BUTTONS_NUMBER)
	{
		unhighlightButton();
		selectedButtonIndex++;
		highlightButton();
	}
}

void ChooseGameMenu::enterKeyAction()
{
	switch (selectedButtonIndex)
	{
	case 0:
		newGameButtonAction();
		break;

	case 1:
		loadSavedGameButtonAction();
		break;

	case 2:
		returnButtonAction();
		break;
	}
}

void ChooseGameMenu::newGameButtonAction()
{
	std::string nickname;
	std::cout << "Enter your nickname: ";
	std::cin >> nickname;
	Game* game;
	game = new Game(0, nickname);
	game->start();
}

void ChooseGameMenu::loadSavedGameButtonAction()
{
	std::cout << "Load saved game" << std::endl;
}

void ChooseGameMenu::returnButtonAction()
{
	return_pressed = true;
}

bool ChooseGameMenu::returnButtonPressed()
{
	return return_pressed;
}

void ChooseGameMenu::highlightButton()
{
	y_pos = y_pos_unit * (BUTTONS_NUMBER + selectedButtonIndex) - (1.5 * font_size);

	buttons[selectedButtonIndex].setFillColor(sf::Color::Red);
	buttons[selectedButtonIndex].setCharacterSize(font_size * 2);
	buttons[selectedButtonIndex].setPosition(sf::Vector2f(x_pos, y_pos));
}

void ChooseGameMenu::unhighlightButton()
{
	y_pos = y_pos_unit * (BUTTONS_NUMBER + selectedButtonIndex) - (0.75 * font_size);

	buttons[selectedButtonIndex].setFillColor(sf::Color::White);
	buttons[selectedButtonIndex].setCharacterSize(font_size);
	buttons[selectedButtonIndex].setPosition(sf::Vector2f(x_pos, y_pos));
}

void ChooseGameMenu::run()
{
	sf::Event event;

	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				upKeyAction();
				break;

			case sf::Keyboard::Down:
				downKeyAction();
				break;

			case sf::Keyboard::Enter:
				enterKeyAction();
				break;
			}
		}
	}
	drawMenu();
}