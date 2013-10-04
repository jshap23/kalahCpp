#include "PlayerStrategies.h"
#include "Player.h"
PlayerStrategies::PlayerStrategies()
{
    //ctor
}

PlayerStrategies::~PlayerStrategies()
{
    //dtor
}



int PlayerStrategies::userMove(Player thePlayer, Board gameBoard)
{
	gameBoard.printBoard();
	// select Pit to Move
	int pit2Move;

	while(cin)
	{
		cout << "Your turn" << endl;
		if(thePlayer.getPosition()=="WHITE")
			cout << "Enter Pit Number(0-5):  ";
		else
			cout << "Enter Pit Number(7-12):  ";
		
		cin >> pit2Move;

		if((thePlayer.getPosition()=="WHITE")&&(pit2Move<0))
		{
		    cout << "Sorry, that was less than 0.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
        }
		else if ((thePlayer.getPosition()=="WHITE")&&(pit2Move>5))
		{
		    cout << "Sorry, that was greater than 5.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
		}
		else if((thePlayer.getPosition()=="BLACK")&&(pit2Move<7))
		{
		    cout << "Sorry, that was less than 7.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
        }
		else if ((thePlayer.getPosition()=="BLACK")&&(pit2Move>12))
		{
		    cout << "Sorry, that was greater than 12.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
		}
		else if((gameBoard.stonesInPits[pit2Move]==0))
		{
			cout << "Sorry, there are not seeds in that pit. Choose again.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
		}
		else if (cin)
        {
			cout << pit2Move << endl;
			break;
        }
        else if (cin.fail() && !(cin.eof() || cin.bad()))
        {
            cout << "Sorry, but that is not a number.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
        }
	}
	return pit2Move;
}



int PlayerStrategies::Move(Player thePlayer, Board game){
    vector<int> stonesInPits;
    int playerMancala = game.getMancala(thePlayer);
	int opponentMancala = (playerMancala +game.numPits + 1)%(game.numPits*2+2);
    int myNumber=999999;
	
	int finalIndex;

	vector<int> gameCopy;
    gameCopy = game.stonesInPits;
	int numPits = game.numPits;
	for(int i = 1;i<=numPits;i++){
		if(gameCopy[playerMancala-i]!=0)
			stonesInPits.push_back(playerMancala-i);  //pits to select
	}
	/* AI */
	// look for steals
	bool canSteal = false;
	int bestSteal=0;
	int stealIndex = 99999;
	for(int i = 1;i<game.numPits;i++)
	{
		int checkIndex = (opponentMancala+i)%14;
		int opPit = 2*game.numPits-checkIndex;
		if((gameCopy[checkIndex]==1)&&(gameCopy[checkIndex+1]==0)&&(gameCopy[opPit]!=0))
		{
			canSteal = true;
			if(gameCopy[opPit]>bestSteal){
				bestSteal = gameCopy[opPit];
				stealIndex = checkIndex;
			}
			else if(gameCopy[opPit]==bestSteal){
				srand (time(NULL));  // if two ways to steal, choose randomly
				int aNum = rand()%1;
				if (aNum==1)
					stealIndex = checkIndex;
			}	
		}
	}			

	// score in one - go again
	bool goAgain = false;
	int goAgainIndex;
	for(int i = 1;i<=game.numPits;i++)
	{
		int checkIndex = (opponentMancala+i)%14;
		int numSeeds = gameCopy[checkIndex];
		int hit = checkIndex + numSeeds;
		if (hit==playerMancala)
		{
			if(goAgain==false){
				goAgain = true;
				goAgainIndex = checkIndex;
			}
			else
			{
				srand (time(NULL));  // if two ways to steal, choose randomly
				int aNum = rand()%1;
				if (aNum==1)
					goAgainIndex = checkIndex;
			}
		}
	}			
	// break Steals for Opponent
	bool breakSteal=false;
	int breakStealIndex;
	int bestSteal2Break = 0;

	for(int i = 1;i<game.numPits;i++)
	{
		int checkIndex = (opponentMancala+i)%14;
		int opPit = 2*game.numPits-checkIndex;
		if((gameCopy[opPit]==0)&&(gameCopy[opPit-1]==1)&&(gameCopy[checkIndex]!=0))
		{
			breakSteal = true;
			if(gameCopy[checkIndex]>bestSteal2Break){
				bestSteal2Break = gameCopy[checkIndex];
				breakStealIndex = checkIndex;
			}
			else if(gameCopy[checkIndex]==bestSteal2Break){
				srand (time(NULL));  // if two ways to steal, choose randomly
				int aNum = rand()%1;
				if (aNum==1)
					breakStealIndex = checkIndex;
			}
		}
	}
	// maximize number of seeds on my side
	bool maxSeedStrat = false;
	int numOnMySide=0;
	int maxSeedIndex=999999;
	int maxSeedVal = 0;
	int seedScenario = 0;
	for(int i = 1;i<=game.numPits;i++)
	{
		int checkIndex = (opponentMancala+i)%14;
		numOnMySide+=gameCopy[checkIndex];
	}
	for(int i = 1;i<=game.numPits;i++)
	{
		int checkIndex = (opponentMancala+i)%14;
		int seedAtPit = gameCopy[checkIndex];
		if (seedAtPit>0){
			int seedMaintain = playerMancala - checkIndex;
			int seedLoss = max(seedAtPit-seedMaintain,0);
			seedScenario = numOnMySide - seedLoss;
			if (seedScenario>maxSeedVal){
				maxSeedIndex = checkIndex;
				maxSeedVal = seedScenario;
				maxSeedStrat = true;
			}
				else if(seedScenario=maxSeedVal){
				srand (time(NULL));  // if tie, choose randomly
				int aNum = rand()%1;
				if (aNum==1)
					maxSeedIndex = checkIndex;
			}
		}
	}

	if(canSteal)
		finalIndex = stealIndex;
	else if(goAgain)
		finalIndex = goAgainIndex;
	else if(breakSteal)
		finalIndex = breakStealIndex;
	else if(maxSeedStrat)
		finalIndex = maxSeedIndex;
	else  	// Worst Case Randomly Select	
	{
		while(find(stonesInPits.begin(),stonesInPits.end(),finalIndex)==stonesInPits.end()){
			srand (time(NULL));
			int aNum = rand()%6+1;
			finalIndex = playerMancala-aNum;
		}
	}

	return finalIndex;
}
