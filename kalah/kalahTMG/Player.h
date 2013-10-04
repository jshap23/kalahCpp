#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include <string>

using namespace std;


class Player
{
    public:
        Player();
        virtual ~Player();
        void setPosition(string);
        string getPosition();
		void setComp(bool);
		bool Player::getAI();
    private:
        string position;
		bool isComputer;
};

#endif // PLAYER_H
