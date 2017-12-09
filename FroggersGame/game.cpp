#include "game.h"
#include <iostream>
using namespace std;

Game::Game()
{
    //----------------CONSTRUCTOR----------------

    _command = '0';
    cout<<endl<<"creating screen"<<endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Java my ass!");
    window.setFramerateLimit(30);

    makeCars();
    makeLogs();

    //--------load background sprite
    if (!bg_texture.loadFromFile("assets/background.png"))
    {
        // error...
        std::cout << "cannot load background.png" << std::endl;
    }else{
        std::cout<<"loaded background!"<<std::endl;
        //create sprite from texture
        bg_sprite.setTexture(bg_texture);
        //scale the sprite to fill the window
        bg_sprite.scale(6.3f,3.7f);
    }
}

void Game::drawLogs(){
    /*
     * Purpose: draw logs on window object
     */
    for(int i=0; i < logs.size(); i++){
        logs[i].draw(window);
    }
}

void Game:: drawCars(){
    /*
     * Purpose: draw cars on window object
     */
    for(int i=0; i < cars.size(); i++){
        cars[i].draw(window);
    }
}

void Game::drawBg(){
    /*
     * Purpose: draw the background to window object
     */
    window.draw(bg_sprite);
}

void Game::run(){
    /*
     * Purpose: game loop
     */

    //-----start playing music
    sf::Music music;
    if (!music.openFromFile("assets/frogger.ogg"))
        cout<<"music can't be played"<<endl; // error
    cout<<"music loaded"<<endl;
    music.setLoop(true);
    music.play();


    //------game loop
    while(window.isOpen()){
        update();
        processEvents();
        render();
    }
}

void Game:: update(){
    /*
     * Purpose: update the position and states of all objects
     */

    //1. move car
    for(int i=0; i<cars.size(); i++){
        cars[i].move();
    }

    //2. move logs
    for(int i=0; i<logs.size(); i++){
        logs[i].move();
    }

    if(frog.dead() == -1){  //only update frog if it's not dead

        //3. check collision
        //3.1 check if the frog collides with any log
        frog.set_log(logCollision());
        //3.2 check if the frog collides with any car
        //if frog collides with car, set the frog to dead
        if(carCollision()){
            frog.set_dead(1);
        }else if(waterCollision() && frog.log() == -1){
        //3.3 if the frog collides with water,
        //but its not on a log,set it to dead
            frog.set_dead(1);
        }else {
            //...
            //if the frog is on a log
            if(frog.log() >= 0){
                //cout<<endl<<frog.log()<<"th log"<<endl;
                //frog moves with the log
                float tempX = frog.posX() + (logs[frog.log()].dir() * logs[frog.log()].speed());
                //cout<<"tempX: "<<tempX<<endl;
                //if the "moved" frog is within boundary, move it
                if(bounds_check(tempX > SCREEN_WIDTH/2 ? tempX+2*frog.width():tempX, frog.posY())){
                    frog.set_posX(tempX);
                    cout<<"posX: "<<frog.posX();
                }
            }
//            if(frog.facing() == 'U'){

//            }
        }
    }
}

void Game:: render(){
    /*
     * Purpose: render everything to screen
     */
    window.clear(sf::Color::Transparent);
    drawBg();
    drawCars();
    drawLogs();
    drawFrog();
    //if the frog is dead:
    if(frog.dead() == 1){
        cout<<"dead frog"<<endl;
        //draw text on screen, ask for input: restart?
        drawPrompt();
        //if user wants to restart, reset the game
        if(_command == 'R')
            reset();
    }
    if(checkWin()){
        drawPrompt();
        if(_command == 'R')
            reset();
    }
    window.display();
}

void Game:: processEvents(){
    /*
     * Purpose: process user input
     */

   sf::Event event;
   while (window.pollEvent(event))//or waitEvent
       {
       // check the type of the event...
           switch (event.type)
           {
               // window closed
               case sf::Event::Closed:
                   window.close();
                   break;

               // key pressed
               case sf::Event::KeyPressed:
                    switch(event.key.code){
                        //=====press left/up/down/right, move frog=======
                        case sf::Keyboard::Left:
                            if (frog.dead() == -1 &&
                                frog.posX() - ROW_HEIGHT >= 0 &&
                                !checkWin())
                            {
                                frog.move('L');
                                cout<<endl<<"move left"<<endl;
                            }
                            cout<<endl<<frog.facing()
                                <<"("<<frog.posX()<<","<<frog.posY()<<")"<<endl;
                            break;

                        case sf::Keyboard::Right:
                            cout<<endl<<"frog width: "<<frog.width()<<endl;
                            if (frog.dead() == -1 && //DO THIS WIDTH
                                frog.posX()+frog.width() + ROW_HEIGHT <= SCREEN_WIDTH &&
                                !checkWin())
                                frog.move('R');
                            cout<<endl<<frog.facing()
                                <<"("<<frog.posX()<<","<<frog.posY()<<")"<<endl;
                            break;

                        case sf::Keyboard::Down:
                            if (frog.dead() == -1 &&
                                !checkWin())
                                frog.move('D');
                            cout<<endl<<frog.facing()
                                <<"("<<frog.posX()<<","<<frog.posY()<<")"<<endl;
                            break;

                        case sf::Keyboard::Up:
                            if (frog.dead() == -1 &&
                                frog.rowNum() + 1 <= ROW_COUNT &&
                                !checkWin()){
                                if (frog.rowNum() == 13 && !checkColumn()){
                                    break;
                                }
                                frog.move('U');
                            }
                            cout<<endl<<frog.facing()
                                <<"("<<frog.posX()<<","<<frog.posY()<<")"<<endl;
                            break;

                        case sf::Keyboard::R:   //restart the game
                            if (frog.dead() == 1 || checkWin()){
                            _command = 'R';
                            }
                            break;
                    }
                   break;
               default:
                   break;
           }
       }
}

void Game::drawFrog(){
    /*
     * Purpose: draw frog on window object
     */
    frog.draw(window);
}

void Game:: makeCars(){
    /*
     * Purpose: generate all car objects and push into vector
     */
    cout<<endl<<"making cars"<<endl;

    //cars in first lane...
    //cars.push_back(makeCar(0, 100, 0));
    cars.push_back(makeCar(0, 700, 4));
    cars.push_back(makeCar(0, 100, 4));

    //cars in second lane...
    cars.push_back(makeCar(1, 100, 0));
    cars.push_back(makeCar(1, 300, 0));
    cars.push_back(makeCar(1, 800, 0));

    //cars in third lane...
    //x-coord: 150; model: 2
    cars.push_back(makeCar(2, 150, 2));

    //cars in fourth lane...
    //x-coord: 150; model: 3
    cars.push_back(makeCar(3, 150, 3));

    //cars in fifth lane...
    //x-coord: 180; model: 4
    cars.push_back(makeCar(4, 180, 1));
}

Car Game:: makeCar(int lane, int posX, int model){
    /*
     * Purpose: generate individual car objects and return them
     */
    cout<<endl<<"making car"<<endl;
    Car car;
    switch(lane) {
    case 0:
        car = Car(posX,rows[lane+1],lane,2,model);
        break;
    case 1:
        car = Car(posX,rows[lane+1],lane,3,model);
        break;
    case 2:
        car = Car(posX,rows[lane+1],lane,4,model);
        break;
    case 3:
        car = Car(posX,rows[lane+1],lane,3,model);
        break;
    case 4:
        car = Car(posX,rows[lane+1],lane,4,model);
        break;
    }
    return car;
}

void Game::makeLogs(){
    /*
     * Purpose: generate all log objects and push into vector
     */
    cout<<endl<<"making logs"<<endl;
    //Note: water starts at row 8, ends at row 13

    //logs in row 8...
    //posX==500, 0th size
    logs.push_back(makeLog(8, 500, 0));
    logs.push_back(makeLog(8, 0, 0));

    //logs in row 9...
    // posX==500, 0th size
    logs.push_back(makeLog(9, 1200, 1));
    logs.push_back(makeLog(9, 600, 1));
    logs.push_back(makeLog(9, 100, 1));

    //logs in row 10...
    logs.push_back(makeLog(10, 0, 1));

    //logs in row 11...
    logs.push_back(makeLog(11, 900, 2));
    logs.push_back(makeLog(11, 400, 2));
    logs.push_back(makeLog(11, 0, 2));

    //logs in row 12...
    logs.push_back(makeLog(12, 0, 2));

    //logs in row 13...
    logs.push_back(makeLog(13, 500, 0));
}

Log Game:: makeLog(int row, int posX, int size){
    /*
     * Purpose: generate individual log objects and return them
     */
    cout<<endl<<"making log"<<endl;
    Log log;
    switch(row) {
    case 8:
        log = Log(posX,rows[row],row,2,1,size);
        break;
    case 9:
        log = Log(posX,rows[row],row,3,-1,size);
        break;
    case 10:
        log = Log(posX,rows[row],row,4,-1,size);
        break;
    case 11:
        log = Log(posX,rows[row],row,3,1,size);
        break;
    case 12:
        log = Log(posX,rows[row],row,4,-1,size);
        break;
    case 13:
        log = Log(posX,rows[row],row,4,1,size);
        break;
    }
    return log;
}

bool Game::collides(float x1, float y1, float w1, float l1,
                     float x2, float y2, float w2, float l2){
    /*
     * Purpose: given the coordinates of two objects, check if they collide
     */
    return (
                ((x1 <= x2+w2 && x1 >=x2) && (y1 <= y2+l2 && y1 >= y2)) ||
                ((x1+w1 <= x2+w2 && x1+w1 >= x2) && (y1 <= y2+l2 && y1 >= y2)) ||
                ((x1 <= x2+w2 && x1 >=x2) && (y1+l1 <= y2+l2 && y1+l1 >= y2)) ||
                ((x1+w1 <= x2+w2 && x1+w1 >= x2) && (y1+l1 <= y2+l2 && y1+l1 >= y2))
            );
}

bool Game:: carCollision(){
    /*
     * Purpose: check each individual car, see if anyone is
     * colliding with the frog
     */
    //variables...
    bool result = false;    //default to be false

    //process...
    //loop through each car, check if collides with frog
    for(int i=0; i<cars.size(); i++){
        if(collides(
            frog.posX(),
            frog.posY(),
            frog.width(),
            frog.length(),
            cars[i].posX(),
            cars[i].posY(),
            cars[i].width(),
            cars[i].length()
        )){
            result = true;
            break;
        };
    };

    //output...
    return result;
}

int Game:: logCollision(){
    /*
     * Purpose: check each individual log, see if anyone is
     * colliding with the frog
     */
    //variables...
    int  result = -1;    //default to be -1, no log collided

    //process...
    //loop through each log, check if collides with frog
    for(int i=0; i<logs.size(); i++){
        if(collides(
            frog.posX(),
            frog.posY(),
            frog.width(),
            frog.length(),
            logs[i].posX(),
            logs[i].posY(),
            logs[i].width()-30,
            logs[i].length()
        )){
            result = i;
            break;
        };
    };

    //output...
    return result;
}

bool Game:: waterCollision(){
    /*
     * Purpose: see if the frog is within water
     */
    //if frog position is between lane 8 and lane 13, return true
    //else return false
    if(frog.rowNum() >= 8 && frog.rowNum() <= 13)
        return true;
    return false;
}

void Game:: reset(){
    /*
     * Purpose: reset the game
     */
    //reset frog
    Frog newFrog;
    frog = newFrog;
    //reset command
    _command = '0';
}

void Game::drawPrompt(){
    /*
     * Purpose: draw prompt to window object
     */
    sf::Font font;
    if (!font.loadFromFile("assets/font.ttf"))
    {
        // error...
        cout<<endl<<"cant load font"<<endl;
    }else if(checkWin()){
        sf::Text text;

        // select the font
        text.setFont(font); // font is a sf::Font

        // set the string to display
        text.setString("YOU WON!! Restart? [R]");

        // set the character size
        text.setCharacterSize(34); // in pixels, not points!

        // set the color
        text.setFillColor(sf::Color::Red);

        // set the text style
        text.setStyle(sf::Text::Bold);

        // set position
        text.setPosition((SCREEN_WIDTH-(text.getGlobalBounds().width))/2,
                         (SCREEN_HEIGHT-(text.getGlobalBounds().height))/2);

        // inside the main loop, between window.clear() and window.display()
        window.draw(text);
    }else{
        sf::Text text;

        // select the font
        text.setFont(font); // font is a sf::Font

        // set the string to display
        text.setString("GAME OVER! Restart? [R]");

        // set the character size
        text.setCharacterSize(34); // in pixels, not points!

        // set the color
        text.setFillColor(sf::Color::Red);

        // set the text style
        text.setStyle(sf::Text::Bold);

        // set position
        text.setPosition((SCREEN_WIDTH-(text.getGlobalBounds().width))/2,
                         (SCREEN_HEIGHT-(text.getGlobalBounds().height))/2);

        // inside the main loop, between window.clear() and window.display()
        window.draw(text);
    }
}

bool Game:: bounds_check(float x, float y){
    /*
     * Purpose: given a set of coordinates, see if the object
     * is within screen boundaries
     */
    if (y >= 0 && y <= SCREEN_HEIGHT && x >= 0 && x <= SCREEN_WIDTH) {
        return true;
    }else{
        return false;
    }
}

bool Game::checkWin(){
    /*
     * Purpose: check if the frog has won.
     * Note: checks if the frog passes the last row of logs
     */


    if (frog.posY() < rows[13]){
        return true;
    }
    return false;
}

bool Game::checkColumn(){
    //checks where the frog is relative to the "winning" row
    //purpose: prevents the frog from entering the "winning row"
    //         unless the frog is lined up with the open column
    if (
        (frog.posX() <= 1310 && frog.posX() >= 1240) ||
        (frog.posX() <= 110 && frog.posX() >= 40) ||
        (frog.posX() <= 410 && frog.posX() >= 340) ||
        (frog.posX() <= 720 && frog.posX() >= 640) ||
        (frog.posX() <= 1010 && frog.posX() >= 940)
        ){
        return true;
    }
    return false;
}
