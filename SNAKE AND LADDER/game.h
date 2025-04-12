#pragma once


#include <iostream>
using namespace std;
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cstdlib>
#include "player.h"
#include "dice.h"


class Game{
    private:
    int boardsize;
    queue<Player> players;
    unordered_map<int, int> snakes;
    unordered_map<int, int> ladders;
    Dice dice;

    public:
    Game(int s);

    void addplayer(string s);
    void addsnake(int s, int t);
    void addladder(int s, int t);

    void start();

};


