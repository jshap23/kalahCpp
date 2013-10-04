#ifndef BOARD_H
#define BOARD_H

#include "Player.h"
#include <string>
#include <vector>
#include <time.h> 
#include <stdio.h>

using namespace std;

class Board
{
    public:
        Board();
        virtual ~Board();
        void initBoard();
		void printBoard();
        void checkForEnd();
        int movePit(int);
        int getMancala(Player);
        int getScore(Player);
        void setScore(Player,int);
        bool getGameStatus();
    private:
        bool gameFinished;
        int whiteScore;
        int blackScore;
        int initStones;
        int numPits;
        int whiteMancala;
        int blackMancala;
        vector<int> stonesInPits;  // Kalah Board is a vector
		// 0-5 : white Pits
		// 6 : white Store
		// 7-12: black Pits
		// 13 : black Store
	friend class PlayerStrategies;
};

#endif // BOARD_H
