
#include <iostream>
using namespace std;

#include "game.h"

Game:: Game(int s){
        boardsize=s;
    }

void Game::addladder(int s,int t){
    ladders[s]=t;
}

void Game::addsnake(int s,int t){
    snakes[s]=t;
}

void Game::addplayer(string ss){
        Player p= Player(ss);
        players.push(p);
}

void Game::start(){
        if(players.size()==0){
            cout<< "No players added"<<endl;
            return;
        }
        while(true){
            Player curr= players. front();
            players.pop();
            int x= dice.roll();
            cout<<  curr.name << " rolled a "<< x<<" (" <<curr.position<< ")"<< endl;
            int final_pos= x+ curr.position;

            if(final_pos> boardsize){
                cout << "Need lesser number of moves" <<endl;
            }
            else{
                while (snakes.find(final_pos)!=snakes.end() || ladders.find(final_pos)!=snakes.end())
                {
                    if(snakes.find(final_pos)!=snakes.end()){
                    final_pos=snakes[final_pos];
                }
                    if(ladders.find(final_pos)!=snakes.end()){
                    final_pos=ladders[final_pos];
                }
                }
                curr.position=final_pos;

                if(final_pos==boardsize){
                    cout<< "yayy "+ curr.name+ " won the game!!"<<endl;
                    break;
                }
                
            }

            players.push(curr);

        }


    }

