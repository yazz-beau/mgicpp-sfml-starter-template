
#ifndef SFML_GAME_H
#define SFML_GAME_H

#include <SFML/Graphics.hpp>

enum menu_select {PLAY, QUIT};
class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
  void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
  void keyPressed(const sf::Event::KeyPressed* event);
  void keyReleased(const sf::Event::KeyReleased* event);
  void textPosition(sf::Text& text, float x, float y);
  void textDetail(sf::Text& text, sf::Color color, int charsize);


 private:
  sf::RenderWindow& window;

  sf::Font font{ "../Data/Fonts/open-sans/OpenSans-SemiboldItalic.ttf" };
  menu_select menu = PLAY;
  sf::Text menu_text{ font, "MENU" };
  sf::Text play_option{ font, "PLAY" };
  sf::Text quit_option{ font, "QUIT" };

  sf::Texture background_texture {"../Data/Images/WhackaMole Worksheet/background.png"};
  sf::Sprite background = sf::Sprite(background_texture);

  sf::Texture menu_background_texture{ "../Data/Images/kenney_physicspack/PNG/Backgrounds/blue_land.png" };
  sf::Sprite menu_background = sf::Sprite(menu_background_texture);

  bool start_menu = true;
  bool in_game = false;
  bool in_menu = false;

};

#endif // SFML_GAME_H
