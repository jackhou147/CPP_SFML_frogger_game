#ifndef FROG_H
#define FROG_H
#include <SFML/Graphics.hpp>
#include "constants.h"

class Frog{
public:
    Frog();

    //getters
    int posX(),
        posY(),
        log(),
        dead();
    float width();
    float length();
    char facing();
    int rowNum();
    sf::Sprite sprite();

    //setters
    void set_posX(float posX),
        set_posY(float posY),
        set_width(int width),
        set_length(int length),
        set_log(int logNum),
        set_dead(int dead),
        set_facing(char facing);
    //utilities
    void draw(sf::RenderWindow& window);
    void move(char dir);
    void up();
    void down();
    void left();
    void right();
private:
    float _posX,   //x-coordinate
          _posY;   //y-coordinate
    float _length;
    float _width;
    int _rowNum; //which row the frog is on right now
    int _log,   //what log is the frog on
        _dead;  //1 is dead, -1 is not dead
    char _facing;   //facing which direction(up, down,left,right)
    sf::Texture frog_texture;
    sf::Sprite frog_sprite;

};

#endif // FROG_H
