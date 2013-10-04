#ifndef GAMEFACTORY_Hn
#define GAMEFACTORY_H

#include "Board.h"
#include "Player.h"
#include "PlayerStrategies.h"
#include <iostream>
#include <limits>

#include <string>
#include <exception>

struct gameResult{
    int numWhitePieces;
    int numBlackPieces;
    string winner;
    string loser;
};

class gameFactory
{
    public:
        gameFactory();
        virtual ~gameFactory();
        void playGame();
        void setPlayers(Player a, Player b);
        void setResults();
        void getResults();
    private:
        PlayerStrategies playerStrats;
        Board gameBoard;
        Player white;
        Player black;
        gameResult gameScore;
};

#endif // GAMEFACTORY_H
