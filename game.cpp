#include <iostream>
#include <string>
#include <cstdlib>
#include "Switchle.h"
using namespace std;

int main()
{
    Switchle game;
    game.StartGame();
    bool end = false;
    while(!end)
    {
        end = game.Check();
        game.Update();
        game.TakeGuess();
    }
    return 0;
}
