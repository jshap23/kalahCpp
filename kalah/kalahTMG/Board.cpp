#include "Board.h"

Board::Board()
{
        initStones = 30;
        numPits = 6;
        stonesInPits.resize(numPits*2+2);
        whiteMancala = numPits;
        blackMancala = 2*numPits+1;
}

Board::~Board()
{
}

void Board::initBoard(){

	srand (time(NULL));

	for(vector<int>::iterator it=stonesInPits.begin();it!=stonesInPits.end();it++)
		*it=0;
    for(int i=0;i<initStones;i++){
		int myNumberW = rand()%6+1;
		int myNumberB = rand()%6+1;
		int WhiteNumber = whiteMancala-myNumberW;
		int BlackNumber = blackMancala-myNumberB;
        stonesInPits[WhiteNumber]++;
		stonesInPits[BlackNumber]++;
    }
	gameFinished = false;
}

void Board::printBoard()
{
	cout << "\n \n \n";
	cout << "The Status of the Kalah Board " << endl;
	cout << endl;
	cout << " Black Store" << endl;
	cout << "      " << stonesInPits[blackMancala] << endl;
	for (int i = 0;i<numPits;i++){
		int blackPit = numPits*2-i;
		cout << "W" << i << "  " << stonesInPits[i] << " | " << stonesInPits[blackPit] << "  B" << blackPit << endl;
	}
	cout << "      " << stonesInPits[whiteMancala] << endl;
	cout << " White Store " << endl;
	cout << "\n \n \n";
}



int Board::getMancala(Player myPlayer){
    if (myPlayer.getPosition() == "WHITE")
        return whiteMancala;
    else
        return blackMancala;
}

int Board::getScore(Player myPlayer){
    if (myPlayer.getPosition() == "WHITE")
        return whiteScore;
    else
        return blackScore;
}

void Board::setScore(Player myPlayer, int myScore){
    if (myPlayer.getPosition() == "WHITE")
        whiteScore = myScore;
    else
        blackScore = myScore;
}

bool Board::getGameStatus(){
    return gameFinished;
}


void Board::checkForEnd(){
	int whiteInPlay = 0;
	int blackInPlay = 0;

	for(int i =0; i < numPits;i++){
		whiteInPlay += stonesInPits[i];
		blackInPlay += stonesInPits[numPits+i+1];
	}
	if(whiteInPlay==0){
		blackScore = blackInPlay + stonesInPits[blackMancala];
		whiteScore = stonesInPits[whiteMancala];
		gameFinished= true;
	}
	else if(blackInPlay ==0){
		blackScore = stonesInPits[blackMancala];
		whiteScore = whiteInPlay + stonesInPits[whiteMancala];
		gameFinished= true;
	}
}


int Board::movePit(int pitToMove){

	int totalLoot=0;
	int goAgain = 0;  //  0 move, 1 go again
	int loot = stonesInPits[pitToMove];
	int refMancala,opponentMancala;
	int nextPit;
	if(pitToMove<=6)
	{
		opponentMancala = blackMancala;
		refMancala = whiteMancala;
	}
	else{
		opponentMancala = whiteMancala;
		refMancala = blackMancala;
	}
	stonesInPits[pitToMove]=0;
	
	int nextMove=99999;
	int opPit = 2*numPits-pitToMove-1;
	if((loot==1) && (stonesInPits[pitToMove+1]==0) && ((pitToMove+1)!=refMancala)&&(stonesInPits[opPit]!=0)){
		stonesInPits[refMancala] += 1 + stonesInPits[opPit];
		stonesInPits[opPit] = 0;
	}
	else{
		for(int i = 1;i<=loot;i++){
			nextMove = (pitToMove + i)%(2*numPits+2);
			if(nextMove!=opponentMancala){
				stonesInPits[nextMove]++;
			}
			else
				loot++;
		}
		if(nextMove==refMancala)
			return 1;
	}
	return 0;
}