#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H

#include <vector>
#include "Board.h"
#include "Player.h"
#include <stdlib.h>
#include <time.h> 
#include <iostream>
#include <limits>


using namespace std;

class PlayerStrategies
{
    public:
        PlayerStrategies();
        virtual ~PlayerStrategies();
        int Move(Player,Board);
		int userMove(Player,Board);
};

#endif // PLAYERSTRATEGIES_H
