#include "Player.h"

Player::Player()
{
	isComputer = false;
}

Player::~Player()
{
}

void Player::setPosition(string myPosition){
    position = myPosition;
}

string Player::getPosition(){
    return position;
}


void Player::setComp(bool playerStatus){
	isComputer = playerStatus;
}


bool Player::getAI(){
	 return isComputer;
}
