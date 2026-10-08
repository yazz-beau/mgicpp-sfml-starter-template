#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL)); //seeds random number generator with the current time
}

Game::~Game()
{

}

// We call this once after the game class is instantiated
bool Game::init()
{
	start_menu = true;

	textDetail(menu_text, sf::Color::Black, 50);
	textPosition(menu_text, 450, 100);

	textDetail(play_option, sf::Color::Black, 30);
	textPosition(play_option, 100, 300);

	textDetail(quit_option, sf::Color::Black, 30);
	textPosition(quit_option, 850, 300);

	menu_background.setScale({ 1.5,0.9 });

	return true;
}

//Update runs after event polling and before rendering
//use it for everything that needs to update between frames
void Game::update(float dt)
{

}

// Runs after update, use it to tell the window what to draw this frame
void Game::render()
{
	//window.display();

	if (start_menu)
	{
		window.draw(menu_background);
		window.draw(menu_text);
		window.draw(play_option);
		window.draw(quit_option);

		return;
	}

	if (in_game)
	{
		window.draw(background);
		return;
	}

}

//Called by event polling when a MouseButtonPressed event is found
void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
	// Event contains mouse position and which button was clicked

	// Don't need to extract position to a variable like this, this is just to show you it's a Vector2i
	sf::Vector2i position = event->position;

	// You can tell which button was pressed by comparing it to SFML's definitions of mouse buttons
	if (event->button == sf::Mouse::Button::Left)
	{
		//Left mouse button was pressed
	}
}

//Called by event polling when a MouseButtonReleased event is found
void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
	//Works the same as MouseButtonPressed
	if (event->button == sf::Mouse::Button::Left)
	{
		//Left mouse button was released
	}
}

// Called by event polling when a KeyPressed event is found
void Game::keyPressed(const sf::Event::KeyPressed* event)
{
	switch (menu)
	{
	case PLAY:
	{
		if (event->scancode == sf::Keyboard::Scancode::Right || event->scancode == sf::Keyboard::Scancode::Left)
		{
			menu = QUIT;

			textDetail(quit_option, sf::Color::Blue, 30);
			textDetail(play_option, sf::Color::Black, 30);
		}
		if (event->scancode == sf::Keyboard::Scancode::Enter)
		{
			in_game = true;
			start_menu = false;
		}
		break;
	}
	case QUIT:
	{
		if (event->scancode == sf::Keyboard::Scancode::Left || event->scancode == sf::Keyboard::Scancode::Right)
		{
			menu = PLAY;
			textDetail(play_option, sf::Color::Blue, 30);
			textDetail(quit_option, sf::Color::Black, 30);

		}
		if (event->scancode == sf::Keyboard::Scancode::Enter)
		{
			window.close();
		}
		break;
	}
	}

	// You can tell which button was pressed by the scancode to SFML's definitions of keyboard keys
	if (event->scancode == sf::Keyboard::Scancode::Escape)
	{
		window.close();
	}

}

// Called by event polling when a KeyReleased event is found
void Game::keyReleased(const sf::Event::KeyReleased* event)
{
	// Works the same way as KeyPressed
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was released
	}

}

void Game::textDetail(sf::Text& text, sf::Color color, int charsize)
{
	text.setFillColor(sf::Color(color));
	text.setCharacterSize(charsize);
}

void Game::textPosition(sf::Text& text, float x, float y)
{
	text.setPosition({ x, y });
}
