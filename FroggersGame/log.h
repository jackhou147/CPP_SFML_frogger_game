#ifndef LOG_H
#define LOG_H
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Log
{
public:
    //constructors
    Log();
    Log(int x, int y, int row, int speed, int dir, int size);
    //SFML
    void draw(sf::RenderWindow& window);
    //utilities
    bool out_of_bounds();
    void move();
    //getters
    int width(),
        length(),
        posX(),
        posY(),
        dir(),
        speed(),
        row(),
        size();
    //setters
    void set_width(int width),
        set_length(int length),
        set_posX(int posX),
        set_posY(int posY),
        set_dir(),
        set_speed(),
        set_row();
    void wrap(); //when the log is out of bounds, move back to beginning

private:
    int _posX,   //x-coordinate
        _posY,   //y-coordinate
        _row,   //which lane this car is on
        _speed,
        _dir,  //what model this car is
        _length,
        _width,
        _size;  //size 0 ~ 4

    sf::Texture log_texture;
    sf::Sprite log_sprite;
    struct LogSize{
       int width;       //horizontal
       int length;      //vertical
    };

    LogSize sizes[3] = {
        {10*40,21},
        {10*29,24},
        {10*24,26}
    };
};

#endif // LOG_H
