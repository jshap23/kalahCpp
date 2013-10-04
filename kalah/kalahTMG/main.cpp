#include <iostream>
#include "Player.h"
#include "gameFactory.h"

using namespace std;


void printGameIntro(){
    cout << "Kalah in C++" << endl;
	cout << "Josh Shapiro" << endl;
	cout << "\n";
}

int main()
{
    printGameIntro();
    gameFactory gameKalah;
	// Create Players
	Player user;
	Player computer;
	gameKalah.setPlayers(user,computer);
	// Play Game
	gameKalah.playGame();
	gameKalah.getResults();

   do {
       cout << "\n" << "Press the Enter key to continue.\n";
   } while (cin.get()!='\n');

    return 0;
}
