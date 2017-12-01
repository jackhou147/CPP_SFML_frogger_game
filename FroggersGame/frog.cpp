#include "frog.h"
#include <iostream>
using namespace std;
Frog::Frog()
{
    //load texture
    if (!frog_texture.loadFromFile("assets/frogger_sprites.png", sf::IntRect(12, 369, 23, 17)))
    {
        // error...
        std::cout << "cannot load frogger_sprites.png" << std::endl;
    }else{
        std::cout<<"loaded!"<<std::endl;
    }

    //create sprite from texture
    frog_sprite.setTexture(frog_texture);
    //scale the sprite absolutely
    frog_sprite.setScale(
                50 / frog_sprite.getLocalBounds().width,
                (ROW_HEIGHT-10)/frog_sprite.getLocalBounds().height
    );
    //set position to be on the very bottom row
    frog_sprite.setPosition(SCREEN_WIDTH/2, rows[0]);
    //set rowNum
    _rowNum = 0;

    //set default values for member variables
    _facing = 'U';
    _posX = frog_sprite.getPosition().x;
    _posY = frog_sprite.getPosition().y;
    _log = -1;  //not on any log when starting
    _dead = -1;
    _width = frog_sprite.getLocalBounds().width;

    //
    cout<<endl<<_facing
    <<"("<<_posX<<","<<_posY<<")"<<endl;

}

sf::Sprite Frog::sprite(){
    return frog_sprite;
}

void Frog::set_facing(char facing){
    facing = toupper(facing);
    if(facing == 'U' ||
        facing == 'D'||
        facing == 'L'||
        facing == 'R' )
    {
        _facing = facing;
    }
}

char Frog::facing(){
    return _facing;
}

void Frog::draw(sf::RenderWindow &window){
    if (_facing == 'U' ||
            _facing == 'D'||
            _facing == 'L'||
            _facing == 'R') {
        //create sprite from texture
        frog_sprite.setTexture(frog_texture);
        //scale the sprite absolutely
        frog_sprite.setScale(
                    50 / frog_sprite.getLocalBounds().width,
                    (ROW_HEIGHT-8)/frog_sprite.getLocalBounds().height
        );
        window.draw(frog_sprite);
    };
}

void Frog::set_posX(float posX){
    cout<<"----set_posX: "<<posX;
    _posX = posX;
    frog_sprite.setPosition(_posX, frog_sprite.getPosition().y);
}

void Frog::set_posY(float posY){
    _posY = posY;
    frog_sprite.setPosition(frog_sprite.getPosition().x,_posY);
}

int Frog::posX(){
    return _posX;
}

int Frog::posY(){
    return _posY;
}

void Frog::move(char dir){
    dir = toupper(dir);
    switch(dir){
    case 'L':
        left();
        break;
    case 'R':
        right();
        break;
    case 'U':
        up();
        break;
    case 'D':
        down();
        break;
    };
}

void Frog::up(){
    _facing = 'U';
    //SFML position
    frog_sprite.setPosition(frog_sprite.getPosition().x, rows[++_rowNum]);
    //update local coordinate values
    _posX = frog_sprite.getPosition().x;
    _posY = frog_sprite.getPosition().y;
}

void Frog::down(){
    _facing = 'D';
    //SFML position
    frog_sprite.setPosition(frog_sprite.getPosition().x, rows[--_rowNum]);
    //update local coordinate values
    _posX = frog_sprite.getPosition().x;
    _posY = frog_sprite.getPosition().y;
}

void Frog::left(){
    _facing = 'L';
    //SFML position
    frog_sprite.move(-1*ROW_HEIGHT, 0.f);
    //update local coordinate values
    _posX = frog_sprite.getPosition().x;
    _posY = frog_sprite.getPosition().y;
}

void Frog::right(){
    _facing = 'R';
    //SFML position
    frog_sprite.move(ROW_HEIGHT, 0.f);
    //update local coordinate values
    _posX = frog_sprite.getPosition().x;
    _posY = frog_sprite.getPosition().y;
}

float Frog::width(){
    return _width;
}

float Frog::length(){
    return _length;
}

int Frog::rowNum(){
    return _rowNum;
}

void Frog::set_log(int logNum){
    _log = logNum;
}

void Frog::set_dead(int dead){
    _dead = dead;
}

int Frog::log(){
    return _log;
}

int Frog::dead(){
    return _dead;
}

