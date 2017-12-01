#include "car.h"

Car::Car()
{

}

Car::Car(int x, int y, int lane, int speed, int model){
    //============CONSTRUCTOR============

    _posX = x;
    _posY = y;
    car_sprite.setPosition(_posX,_posY);
    _lane = lane;
    _speed = speed;
    _model = model;
    _width = models[model].width;
    _length = models[model].length;
}

void Car::draw(sf::RenderWindow& window){
    /* Purpose: draw the car
     */
    //cout<<endl<<"draw car!!"<<endl;

    //----------load texture
    if (!car_texture.loadFromFile("assets/frogger_sprites.png"))
    {
        // error...
        //cout << endl<< "cannot load frogger_sprites.png" << endl;
    }else{
        //cout<<endl<<"car loaded!"<<endl;

        //set the texture rectangle based on model
        switch(_model){
        case 0:
            car_sprite.setTextureRect(sf::IntRect(8, 265, 30, 22));
            //scale the sprite absolutely
            car_sprite.setScale(
                        _width / car_sprite.getLocalBounds().width,
                        _length/car_sprite.getLocalBounds().height
            );
            break;
        case 1:
            car_sprite.setTextureRect(sf::IntRect(45, 264, 29, 24));
            //scale the sprite absolutely
            car_sprite.setScale(
                        _width / car_sprite.getLocalBounds().width,
                        _length/car_sprite.getLocalBounds().height);
            break;
        case 2:
            car_sprite.setTextureRect(sf::IntRect(81, 263, 24, 26));
            //scale the sprite absolutely
            car_sprite.setScale(
                        _width / car_sprite.getLocalBounds().width,
                        _length/car_sprite.getLocalBounds().height);
            break;
        case 3:
            car_sprite.setTextureRect(sf::IntRect(9, 300, 24, 21));
            //scale the sprite absolutely
            car_sprite.setScale(
                        _width / car_sprite.getLocalBounds().width,
                        _length/car_sprite.getLocalBounds().height);
            break;
        case 4:
            car_sprite.setTextureRect(sf::IntRect(105, 301, 46, 19));
            //scale the sprite absolutely
            car_sprite.setScale(
                        _width / car_sprite.getLocalBounds().width,
                        _length/car_sprite.getLocalBounds().height);
            break;
        }

        //create sprite from texture
        car_sprite.setTexture(car_texture);
    }

    //---------draw in window object
    car_sprite.setPosition(car_sprite.getPosition().x, _posY);
    window.draw(car_sprite);
}

void Car::move(){
    /* Purpose: move the car left/right
     * Pre-condition:
     * Post-condition:
     */
    //cout<<endl<<"car moving!"<<endl;
    car_sprite.move((models[_model].dir * _speed),0);
    _posX = car_sprite.getPosition().x;
    if(out_of_bounds()){
        wrap();
    }
}

bool Car::out_of_bounds(){
    /* Purpose: check if a car is still within grid boundaries
     * Pre-condition:
     * Post-condition:
     * Note: if the car is either on the extreme left or on
     * the extreme right, then it’s out of bounds
     */

    return ((_posX + _width) < 0 || _posX > SCREEN_WIDTH);
}

void Car::wrap(){
    /* Purpose: when the car is out of bounds, wrap it back to beginning
     * of its lane
     *
     */

    switch(_lane) {
    case 0:
        _posX = -(models[_model].width);
        car_sprite.setPosition(_posX, _posY);
        break;
    case 1: //cars in this lane go in positive direction -->
        _posX = -(models[_model].width);
        car_sprite.setPosition(_posX, _posY);
        break;
    case 2: //cars in this lane go in negative direction <--
        _posX = SCREEN_WIDTH-1;
        car_sprite.setPosition(_posX, _posY);
        break;
    case 3: //cars in this lane go in negative direction <--
        _posX = SCREEN_WIDTH-1;
        car_sprite.setPosition(_posX, _posY);
        break;
    case 4: //cars in this lane go in positive direction -->
        _posX = -(models[_model].width);
        car_sprite.setPosition(_posX, _posY);
        break;
    }
}

//getters
int Car::lane(){
    return _lane;
}

int Car::model(){
    return _model;
}

int Car::width(){
    return _width;
}
int Car::length(){
    return _length;
}
int Car::posX(){
    return _posX;
}
int Car::posY(){
    return _posY;
}



//setters
void Car::set_width(int width){
    _width = width;
}
void Car::set_length(int length) {
    _length = length;
}
void Car::set_posX(int posX){
    _posX = posX;
}
void Car::set_posY(int posY){
    _posY = posY;
}







