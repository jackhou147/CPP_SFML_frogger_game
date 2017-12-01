#include "log.h"

//CONSTRUCTORS
Log::Log()
{

}

Log::Log(int x, int y, int row, int speed, int dir, int size){
    _posX = x;
    _posY = y;
    log_sprite.setPosition(_posX,_posY);
    _row = row;
    _speed = speed;
    _dir = dir;
    _width = sizes[size].width;
    _length = sizes[size].length;
    _size = size;
}

//UTILITIES
void Log::draw(sf::RenderWindow &window){
    /* Purpose: draw the log
     */

    //----------load texture
    if (!log_texture.loadFromFile("assets/frogger_sprites.png"))
    {
        // error...
        //cout << endl<< "cannot load frogger_sprites.png" << endl;
    }else{
        //cout<<endl<<"log loaded!"<<endl;

        //set the texture rectangle based on length
        switch(_size){
        case 0:
            log_sprite.setTextureRect(sf::IntRect(6, 165, 179, 21));
            //scale the sprite absolutely
            log_sprite.setScale(
                        _width / log_sprite.getLocalBounds().width,
                       1.4*_length/log_sprite.getLocalBounds().height
            );
            break;
        case 1:
            log_sprite.setTextureRect(sf::IntRect(5, 197, 118, 21));
            //scale the sprite absolutely
            log_sprite.setScale(
                        _width / log_sprite.getLocalBounds().width,
                        1.4*_length/log_sprite.getLocalBounds().height);
            break;
        case 2:
            log_sprite.setTextureRect(sf::IntRect(6, 229, 85, 22));
            //scale the sprite absolutely
            log_sprite.setScale(
                        _width / log_sprite.getLocalBounds().width,
                        1.4*_length/log_sprite.getLocalBounds().height);
            break;
        }

        //create sprite from texture
        log_sprite.setTexture(log_texture);
    }

    //---------draw in window object
    log_sprite.setPosition(log_sprite.getPosition().x, _posY);
    window.draw(log_sprite);
}
void Log::move(){
    /* Purpose: move the log left/right
     * Pre-condition:
     * Post-condition:
     */
    log_sprite.move((_dir * _speed),0);
    _posX = log_sprite.getPosition().x;
    if(out_of_bounds()){
        wrap();
    }
}

bool Log::out_of_bounds(){
    /* Purpose: check if a log is still within grid boundaries
     * Pre-condition:
     * Post-condition:
     * Note: if the log is either on the extreme left or on
     * the extreme right, then it’s out of bounds
     */
    return ((_posX + _width) < 0 || _posX > SCREEN_WIDTH);
}

void Log::wrap(){
    /* Purpose: when the log is out of bounds, wrap it back to beginning
     * of its row
     *
     */
    if(_dir > 0){
        //if the log goes to the right
        _posX = -(sizes[_size].width);
        log_sprite.setPosition(_posX, _posY);
    }
    else if(_dir < 0){
        //if the log goes to the left
        _posX = SCREEN_WIDTH;
        log_sprite.setPosition(_posX, _posY);
    }
}


//getters
int Log::row(){
    return _row;
}
int Log::width(){
    return _width;
}
int Log::length(){
    return _length;
}
int Log::posX(){
    return _posX;
}
int Log::posY(){
    return _posY;
}
int Log::dir(){
    return _dir;
}
int Log::speed(){
    return _speed;
}
int Log::size(){
    return _size;
}

//setters
void Log::set_width(int width){
    _width = width;
}
void Log::set_length(int length) {
    _length = length;
}
void Log::set_posX(int posX){
    _posX = posX;
}
void Log::set_posY(int posY){
    _posY = posY;
}
