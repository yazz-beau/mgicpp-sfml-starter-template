
#ifndef SFML_GAME_H
#define SFML_GAME_H

#include <SFML/Graphics.hpp>

enum menu_select {PLAY, QUIT, INST};
enum win_lose {DAYS, WIN, LOSE};

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
  void acceptRejectPoints();
  void winloseConditions();
  void reset_game();

 private:
  sf::RenderWindow& window;

  sf::Font font{ "../Data/Fonts/open-sans/OpenSans-SemiboldItalic.ttf" };

  //   M E N U   //

  menu_select menu = PLAY;
  sf::Text menu_text{ font, "MENU" };
  sf::Text play_option{ font, "PLAY" };
  sf::Text quit_option{ font, "QUIT" };
  sf::Text instruct_{ font, "INSTRUCTIONS" };

  sf::Text instruct_menu{ font, "INSTRUCTIONS" };
  sf::Text instructions{ font, "left click to bring up stamps" };

  //  T E X T U R E S  +  S P R I T E  //

  sf::Texture background_texture {"../Data/Images/WhackaMole Worksheet/background.png"};
  sf::Sprite background = sf::Sprite(background_texture);

  sf::Texture menu_background_texture{ "../Data/Images/kenney_physicspack/PNG/Backgrounds/blue_land.png" };
  sf::Sprite menu_background = sf::Sprite(menu_background_texture);

  sf::Texture accept_texture{ "../Data/Images/Critter Crossing/accept button.png" };
  sf::Sprite accept_stamp = sf::Sprite(accept_texture);

  sf::Texture reject_texture{ "../Data/Images/Critter Crossing/reject button.png" };
  sf::Sprite reject_stamp = sf::Sprite(reject_texture);

  sf::Texture accept_ink_texture{ "../Data/Images/Critter Crossing/accept.png" };
  sf::Sprite accept_ink = sf::Sprite(accept_ink_texture);

  sf::Texture reject_ink_texture{ "../Data/Images/Critter Crossing/reject.png" };
  sf::Sprite reject_ink = sf::Sprite(reject_ink_texture);

  sf::Sprite* character;
  sf::Sprite* passport;

  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];

  //   S T A T E S   //

  bool start_menu = true;
  bool in_game = false;
  bool in_menu = false;
  bool instruct = false;
  bool aRwindowOpen = false;
  bool accept = false;
  bool reject = false;
  bool stamped = false;
  
  int animal_index;
  int passport_index;

  int score = 0;
  sf::Text score_ {font, "Score: " + std::to_string(score)};

  int lives = 3;
  sf::Text lives_{ font, "Lives: " + std::to_string(lives)};

  // P A S S P O R T   M O V E //

  sf::Sprite* dragged = nullptr;
  sf::Vector2f drag_offset;

  sf::Vector2f reject_stamp_offset;
  sf::Vector2f accept_stamp_offset;

  // W I N   &   L O S E //

  enum win_lose winLose = DAYS;
  bool win = false;
  bool lose = false;

  sf::Text lose_text{ font, "YOU LOST" };
  sf::Text win_text{ font, "YOU WIN" };
  sf::Text menu_option { font, "RETURN TO MENU" };

};

#endif // SFML_GAME_H
