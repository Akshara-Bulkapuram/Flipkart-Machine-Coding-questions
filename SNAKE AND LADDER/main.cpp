
#include <iostream>
using namespace std;
#include "game.h"

int main() {
    Game game(100);
    game.addplayer("Claire");
    game.addplayer("Bob");
    game.addplayer("Alice");
    


    // Add snakes
    game.addsnake(99, 54);
    game.addsnake(70, 55);
    game.addsnake(52, 42);

    // Add ladders
    game.addladder(3, 22);
    game.addladder(5, 8);
    game.addladder(11, 26);
    game.addladder(20, 29);

    game.start();

    return 0;
}