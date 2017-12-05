#ifndef GAME_H
#define GAME_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "constants.h"
#include "car.h"
#include "log.h"
#include "frog.h"
using namespace std;


class Game
{
public:
    Game();
    void makeCars();
    Car makeCar(int lane, int posX = -100, int model = -100);
    void makeLogs();
    Log makeLog(int row, int posX, int length);
    void drawBg();
    void drawCars();
    void drawLogs();
    void run();
    void processEvents();
    void update();
    void render();
    void reset();   //reset/restart the game
    int playMusic();   //play background music
    void drawFrog(int dead);    //draw frog to window object
    bool bounds_check(float x, float y);
    bool collides(float x1, float y1, float w1, float l1,
                  float x2, float y2, float w2, float l2);
    bool carCollision();
    int logCollision();
    bool waterCollision();
    void drawPrompt();  //when frog dies, draw text on screen
    bool checkWin();    //checks if frog is on the winning row
    bool checkColumn(); //checks if frog is within bounds of last columns


private:
    char _command;
    sf::RenderWindow window;
    Frog frog;
    vector<Car> cars;
    vector<Log> logs;
    sf::Texture bg_texture; //background texture
    sf::Sprite bg_sprite;   //background sprite
};

#endif // GAME_H
