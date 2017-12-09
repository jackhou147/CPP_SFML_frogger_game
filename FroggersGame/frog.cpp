#include "frog.h"
#include <iostream>

using namespace std;


Frog::Frog()
{
    //load texture
    if (!frog_texture.loadFromFile("assets/frogger_sprites.png"))
    {
        // error...
        std::cout << "cannot load frogger_sprites.png" << std::endl;
    }else{
        std::cout<<"loaded!"<<std::endl;
    }

    //create sprite from texture
    frog_sprite.setTexture(frog_texture);
    frog_sprite.setTextureRect(sf::IntRect(12, 369, 18, 13));

    //set scale
    frog_sprite.setScale(1.9,1.9);
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
    _width = frog_sprite.getGlobalBounds().width;
    _length = frog_sprite.getGlobalBounds().height;
    //
    cout<<endl<<_facing
    <<"("<<_posX<<","<<_posY<<")"<<endl;

}

void Frog::draw(sf::RenderWindow &window){
    /* purpose; draws the frog facing the correct direction
     * notes: will account for frog's death state
     */
    if (_dead != 1){

        frog_sprite.setTexture(frog_texture);
        if (_facing == 'U'){
            frog_sprite.setTextureRect(sf::IntRect(12, 369, 21, 21));
        }
        else if(_facing == 'D'){
            frog_sprite.setTextureRect(sf::IntRect(81, 369, 21, 21));
        }
        else if(_facing == 'L'){
            frog_sprite.setTextureRect(sf::IntRect(81, 336, 21, 21));

        }
        else if(_facing == 'R'){
            frog_sprite.setTextureRect(sf::IntRect(12, 336, 21, 21));
        }
    }
    else{
        frog_texture.loadFromFile("assets/dead_frog.png");
        frog_sprite.setTexture(frog_texture, true);
    }
    window.draw(frog_sprite);
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
    /*
     * Purpose: move the frog 1 unit up
     */
    _facing = 'U';
    //SFML position
    if (_rowNum > 12){
        //if frog is in the row before winning row
        frog_sprite.setPosition(frog_sprite.getPosition().x, rows[_rowNum] - 50);
        ++_rowNum;
    }
    else{
        //if frog is in any other row
        frog_sprite.setPosition(frog_sprite.getPosition().x, rows[++_rowNum]);
    }


    //update local coordinate values
    _posX = frog_sprite.getPosition().x;
    _posY = frog_sprite.getPosition().y;
}

void Frog::down(){
    /*
     * Purpose: move the frog 1 unit down
     */
    _facing = 'D';
    //SFML position
    frog_sprite.setPosition(frog_sprite.getPosition().x, rows[--_rowNum]);

    //update local coordinate values
    _posX = frog_sprite.getPosition().x;
    _posY = frog_sprite.getPosition().y;
}

void Frog::left(){
    /*
     * Purpose: move the frog 1 unit to the left
     */
    _facing = 'L';
    //SFML position
    frog_sprite.move(-1*ROW_HEIGHT, 0.f);
    //update local coordinate values
    _posX = frog_sprite.getPosition().x;
    _posY = frog_sprite.getPosition().y;
}

void Frog::right(){
    /*
     * Purpose: move the frog 1 unit to the right
     */
    _facing = 'R';
    //SFML position
    frog_sprite.move(ROW_HEIGHT, 0.f);
    //update local coordinate values
    _posX = frog_sprite.getPosition().x;
    _posY = frog_sprite.getPosition().y;
}




//-----------SETTERS-------------
void Frog::set_posX(float posX){
    cout<<"----set_posX: "<<posX;
    _posX = posX;
    frog_sprite.setPosition(_posX, frog_sprite.getPosition().y);
}

void Frog::set_posY(float posY){
    _posY = posY;
    frog_sprite.setPosition(frog_sprite.getPosition().x,_posY);
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


//-----------GETTERS-------------
char Frog::facing(){
    return _facing;
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

int Frog::posX(){
    return _posX;
}

int Frog::posY(){
    return _posY;
}

