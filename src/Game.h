
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
  void newAnimal();
  void dragSprite(sf::Sprite* sprite);


 private:
  sf::RenderWindow& window;

  sf::Font font{ "../Data/Fonts/open-sans/OpenSans-SemiboldItalic.ttf" };

  //   M E N U   //

  menu_select menu = PLAY;
  sf::Text menu_text{ font, "MENU" };
  sf::Text play_option{ font, "PLAY" };
  sf::Text quit_option{ font, "QUIT" };

  //  T E X T U R E S  +  S P R I T E  //

  sf::Texture background_texture {"../Data/Images/WhackaMole Worksheet/background.png"};
  sf::Sprite background = sf::Sprite(background_texture);

  sf::Texture menu_background_texture{ "../Data/Images/kenney_physicspack/PNG/Backgrounds/blue_land.png" };
  sf::Sprite menu_background = sf::Sprite(menu_background_texture);

  sf::Texture accept_texture{ "../Data/Images/Critter Crossing/accept button.png" };
  sf::Sprite accept_stamp = sf::Sprite(accept_texture);

  sf::Texture reject_texture{ "../Data/Images/Critter Crossing/reject button.png" };
  sf::Sprite reject_stamp = sf::Sprite(reject_texture);

  sf::Sprite* character;
  sf::Sprite* passport;

  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];

  //   S T A T E S   //

  bool start_menu = true;
  bool in_game = false;
  bool in_menu = false;
  bool aRwindowOpen = false;

  // P A S S P O R T   M O V E //

  sf::Sprite* dragged = nullptr;
  sf::Vector2f drag_offset;

};

#endif // SFML_GAME_H
