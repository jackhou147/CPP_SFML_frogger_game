#ifndef CAR_H
#define CAR_H
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
class Car
{
public:
    Car();
    Car(int x, int y, int lane, int speed, int model);
    void draw(sf::RenderWindow& window);
    bool out_of_bounds();
    void move();
    void wrap();        //when the car is out of bounds, move back to beginning
    //getters
    int lane(),
        model(),
        width(),
        length(),
        posX(),
        posY();
    //setters
    void set_width(int width),
        set_length(int length),
        set_posX(int posX),
        set_posY(int posY);
private:
    int _posX,   //x-coordinate
        _posY,   //y-coordinate
        _lane,   //which lane this car is on
        _speed,
        _model,  //what model this car is
        _width,
        _length;
    sf::Texture car_texture;
    sf::Sprite car_sprite;

    struct CarModel{
       int width;
       float length;
       int dir;
    };

    CarModel models[5] = {
        {70,ROW_HEIGHT-8,1},
        {49,ROW_HEIGHT-3,1},
        {50,ROW_HEIGHT-10,-1},
        {50,ROW_HEIGHT-15,-1},
        {55,ROW_HEIGHT-10,1}
    };

};

#endif // CAR_H
