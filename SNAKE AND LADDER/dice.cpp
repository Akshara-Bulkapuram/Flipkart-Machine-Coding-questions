#include "dice.h"
#include <iostream>
using namespace std;

int Dice:: roll(){

    return rand()%6 +1;

}