#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

// NEED PASSPORT BORDER//

Game::Game(sf::RenderWindow& game_window): window(game_window)
{
	srand(time(NULL)); //seeds random number generator with the current time
}

Game::~Game()
{
	delete[] animals;
	delete[] passports;
	delete[] character;
	delete[] passport;
}

// We call this once after the game class is instantiated
bool Game::init()
{
	//////   M E N U   //////

	start_menu = true;

	textDetail(menu_text, sf::Color::Black, 50);
	textPosition(menu_text, 450, 100);

	textDetail(play_option, sf::Color::Black, 30);
	textPosition(play_option, 100, 300);

	textDetail(quit_option, sf::Color::Black, 30);
	textPosition(quit_option, 850, 300);

	textDetail(instruct_, sf::Color::Black, 30);
	textPosition(instruct_, 400, 300);

	menu_background.setScale({ 1.5,0.9 });

	/////////  M A I N   G A M E ///////

	//   T E X T   //

	textDetail(score_, sf::Color::Black, 50);
	textPosition(score_, 500, 20);

	textDetail(lives_, sf::Color::Black, 50);
	textPosition(lives_, 800, 20);

	//  T E X T U R E S  +  S P R I T E  //

	animals[0].loadFromFile("../Data/Images/critcros/Char1.png");
	animals[1].loadFromFile("../Data/Images/critcros/Char2.png");
	animals[2].loadFromFile("../Data/Images/critcros/Char3.png");

	passports[0].loadFromFile("../Data/Images/critcros/Char1_passport.jpg");
	passports[1].loadFromFile("../Data/Images/critcros/Char2_passport.jpg");
	passports[2].loadFromFile("../Data/Images/critcros/Char3_passport.jpg");

	character = new sf::Sprite(animals[0]);
    passport = new sf::Sprite(passports[0]);

	character->setTexture(animals[animal_index]);
	passport->setTexture(passports[passport_index]);

	/*character->setScale({1.5, 1.5});
	character->setPosition(sf::Vector2f(window.getSize().x / 12, window.getSize().y / 12));

	passport->setTexture(passports[passport_index], true);
	passport->setScale({ 0.6, 0.6 });
	passport->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 3));*/

	/*character->setPosition({ 500.f,500.f });*/
	passport->setPosition({ 500.f,50.f });

	newAnimal();

	// M O U S E   M O V E //

	/*sf::Sprite* dragged = nullptr;
	sf::Vector2f drag_offset;*/

	// R E J E C T   A N D   A C C E P T //

	accept_stamp.setPosition({ 700.f,300.f });
	reject_stamp.setPosition({ 700.f,500.f });

	// W I N   &   L O S E //

	textDetail(win_text, sf::Color::Black, 50);
	textPosition(win_text, 450, 100);
	textDetail(lose_text, sf::Color::Black, 50);
	textPosition(lose_text, 450, 100);

	textDetail(menu_option, sf::Color::Blue, 50);
	textPosition(menu_option, 350, 400);

	textDetail(instruct_menu, sf::Color::Black, 50);
	textPosition(instruct_menu, 400, 100);

	textDetail(instructions, sf::Color::Black, 25);
	textPosition(instructions, 200, 300);


	return true;
}

//Update runs after event polling and before rendering
//use it for everything that needs to update between frames
void Game::update(float dt)
{
	dragSprite(dragged);
	score_.setString("Score: " + std::to_string(score));
	lives_.setString("Lives: " + std::to_string(lives));

	if (accept == true)
	{
		accept_ink.setPosition(passport->getPosition() + accept_stamp_offset);
	}

	if (reject == true)
	{
		reject_ink.setPosition(passport->getPosition() + reject_stamp_offset);
	}
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
		window.draw(instruct_);

		return;
	}

	if (in_game)
	{
		window.draw(background);
		window.draw(*character);
		window.draw(*passport);
		window.draw(score_);
		window.draw(lives_);

		if (accept == true)
		{
			window.draw(accept_ink);
		}
		if (reject == true)
		{
			window.draw(reject_ink);
		}

		if (aRwindowOpen == true)
		{
			window.draw(accept_stamp);
			window.draw(reject_stamp);
		}

		return;
	}

	if (instruct == true)
	{
		window.draw(menu_background);
		window.draw(instructions);
		window.draw(instruct_menu);

		return;
	}

	if (win == true)
	{
		window.draw(menu_background);
		window.draw(menu_option);
		window.draw(win_text);

		return;
	}

	if (lose == true)
	{
		window.draw(menu_background);
		window.draw(menu_option);
		window.draw(lose_text);

		return;
	}

}

//Called by event polling when a MouseButtonPressed event is found
void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
	if (event->button == sf::Mouse::Button::Left)
	{
		sf::Vector2i position = event->position;
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(position);

		/*switch (clickLeft)*/

		if (aRwindowOpen == true && accept_stamp.getGlobalBounds().contains(mouse_positionf))
		{
			if (accept_stamp.getGlobalBounds().findIntersection(passport->getGlobalBounds()))
			{
				accept = true;
				stamped = true;
				reject = false;

				std::cout << "accept_stamped,";

				std::optional<sf::FloatRect> stamp_pos = accept_stamp.getGlobalBounds().findIntersection(passport->getGlobalBounds());

				if (stamp_pos.has_value())
				{
					accept_stamp_offset = stamp_pos->position - passport->getPosition();
					accept_ink.setPosition(passport->getPosition() + accept_stamp_offset);

				}
			}
			else
			{
				std::cout << "accept_stamped_attempted,";
			}
		}

		if (aRwindowOpen == true && reject_stamp.getGlobalBounds().contains(mouse_positionf))
		{
			if (reject_stamp.getGlobalBounds().findIntersection(passport->getGlobalBounds()))
			{
				reject = true;
				stamped = true;
				accept = false;

				std::cout << "reject_stamped,";

				// can use auto? ask dont understand fully
				std::optional<sf::FloatRect> stamp_pos = reject_stamp.getGlobalBounds().findIntersection(passport->getGlobalBounds());

				if (stamp_pos.has_value())
				{
					reject_stamp_offset = stamp_pos->position - passport->getPosition();
					reject_ink.setPosition(passport->getPosition() + reject_stamp_offset);

				}

			}
			else
			{
				std::cout << "reject_stamped_attempt,";
			}
		}

		else if (passport->getGlobalBounds().contains(mouse_positionf))
		{
			dragged = passport;

			drag_offset = mouse_positionf - passport->getPosition();
		}

		if (stamped == true && character->getGlobalBounds().findIntersection(passport->getGlobalBounds()))
		{
			acceptRejectPoints();
			stamped = false;
		}
     
	}

	if (event->button == sf::Mouse::Button::Right)
	{
		if (aRwindowOpen == false)
		{
			aRwindowOpen = true;
			return;
		}

		if (aRwindowOpen == true)
		{
			aRwindowOpen = false;
			return;
		}
	}

	// Don't need to extract position to a variable like this, this is just to show you it's a Vector2i
	sf::Vector2i position = event->position;
	
}

//Called by event polling when a MouseButtonReleased event is found
void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
	//Works the same as MouseButtonPressed
	if (event->button == sf::Mouse::Button::Left)
	{
		dragged = nullptr;
	}
}

// Called by event polling when a KeyPressed event is found
void Game::keyPressed(const sf::Event::KeyPressed* event)
{
	switch (menu)
	{
	case PLAY:
	{
		if (start_menu == true)
		{
			if (event->scancode == sf::Keyboard::Scancode::Right)
			{
				menu = INST;

				textDetail(instruct_, sf::Color::Blue, 30);
				textDetail(play_option, sf::Color::Black, 30);
			}
			if (event->scancode == sf::Keyboard::Scancode::Left)
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
	}
	case QUIT:
	{

		if (start_menu == true)
		{
			if (event->scancode == sf::Keyboard::Scancode::Right)
			{
				menu = PLAY;
				textDetail(play_option, sf::Color::Blue, 30);
				textDetail(quit_option, sf::Color::Black, 30);

			}
			if (event->scancode == sf::Keyboard::Scancode::Left)
			{
				menu = INST;
				textDetail(instruct_, sf::Color::Blue, 30);
				textDetail(quit_option, sf::Color::Black, 30);

			}
			if (event->scancode == sf::Keyboard::Scancode::Enter)
			{
				window.close();
			}
			break;
		}
	}
	case INST:
	{

		if (start_menu == true)
		{
			if (event->scancode == sf::Keyboard::Scancode::Right)
			{
				menu = QUIT;
				textDetail(quit_option, sf::Color::Blue, 30);
				textDetail(instruct_, sf::Color::Black, 30);

			}
			if (event->scancode == sf::Keyboard::Scancode::Left)
			{
				menu = PLAY;
				textDetail(play_option, sf::Color::Blue, 30);
				textDetail(instruct_, sf::Color::Black, 30);

			}
			if (event->scancode == sf::Keyboard::Scancode::Enter)
			{
				start_menu = false;
				instruct = true;
			}
			break;
		}
	}
	}
	// You can tell which button was pressed by the scancode to SFML's definitions of keyboard keys
	if (event->scancode == sf::Keyboard::Scancode::Escape)
	{
		window.close();
	}

	if (win == true)
	{
		if (event->scancode == sf::Keyboard::Scancode::Enter)
		{
			win == false;

			start_menu = true;
		}
	}

	if (lose == true)
	{
		if (event->scancode == sf::Keyboard::Scancode::Enter)
		{
			lose == false;

			start_menu = true;
		}
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

void Game::newAnimal()
{
	animal_index = rand() % 3;
	passport_index = rand() % 3;

	character->setTexture(animals[animal_index], true);
	character->setScale({ 1.5, 1.5 });
	character->setPosition(sf::Vector2f(window.getSize().x / 12, window.getSize().y / 12));

	passport->setTexture(passports[passport_index], true);
	passport->setScale({ 0.6, 0.6 });
	passport->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 3));

}

void Game::dragSprite(sf::Sprite* sprite)
{
	if (sprite != nullptr)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

		sf::Vector2f drag_position = mouse_positionf - drag_offset;
		sprite->setPosition({ drag_position.x, drag_position.y });
	}
}

void Game::acceptRejectPoints()
{

	if (animal_index == passport_index && accept == true)
	{
		score = score + 1;
		std::cout << "Correct";
	}
	else if (accept == true)
	{
		lives = lives - 1;
		std::cout << "Wrong";
	}
	
	if (animal_index == passport_index && reject == true)
	{
		lives = lives - 1;
		std::cout << "Wrong";
	}
	else if (reject == true)
	{
		score = score + 1;
		std::cout << "Correct";
	}

	if (score == 10)
	{
		win = true;
		in_game = false;

		reset_game();
	}

	if (lives == 0)
	{
		lose = true;
		in_game = false;

		reset_game();
	}


	accept = false;
	reject = false;

	newAnimal();
}

void Game::winloseConditions()
{
	/*switch (winLose)
	{
	case DAYS:
	{
		if()
	}
	case WIN:
	{
		if (score == 10)
		{
			win = true;

		}
		if (event->scancode == sf::Keyboard::Scancode::Enter)
		{
			window.close();
		}
		break;
	}
	}*/
}

void Game::reset_game()
{
	if (win == true || lose == true)
	{
		score = 0;
		lives = 0; 
	}

}
