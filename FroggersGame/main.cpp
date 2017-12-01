#include <iostream>
using namespace std;
#include "constants.h"
const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 800;
const int ROW_COUNT = 14;
const float ROW_HEIGHT = 50.f;
#include "game.h"
//note: the first row is where the frog is at when game starts
int rows[ROW_COUNT] = {730+20,680,630,580,530,480,450,390,330,280,230,180,130,80};

int main()
{
    //cout<<endl;
    //for(int i=0, j = rows[0]; i< 13; i++, j-=50){
    //    cout<<j<<",";
    //}

    Game game;
    game.run();



    cout << "Hello World!" << endl;
    return 0;
}




