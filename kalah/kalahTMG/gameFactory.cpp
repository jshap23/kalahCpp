#include "gameFactory.h"

gameFactory::gameFactory()
{
}

gameFactory::~gameFactory()
{
}

void gameFactory::playGame(){
    gameBoard.setScore(white,0);
    gameBoard.setScore(black,0);

    gameBoard.initBoard();
	gameBoard.printBoard();
    int numMoves = 0;
	int goAgain = 0;

    try{
        while(!gameBoard.getGameStatus()){
            if(numMoves%2 ==0){
				if(white.getAI()==true)
					goAgain = gameBoard.movePit(playerStrats.Move(white,gameBoard));
				else
					goAgain = gameBoard.movePit(playerStrats.userMove(white,gameBoard));
			}
            else{
				if(black.getAI()==true)
					goAgain = gameBoard.movePit(playerStrats.Move(black,gameBoard));
				else
					goAgain = goAgain = gameBoard.movePit(playerStrats.userMove(black,gameBoard));
			}
			gameBoard.checkForEnd();
            if(!goAgain)
				numMoves++;
			else
				cout << "Player goes again."<< endl;
        }
    }
    catch(exception& e){
        cout << "Standard exception: " << e.what() << endl;
    }
	setResults();
}

void gameFactory::setPlayers(Player a, Player b){
	int color;
	while (cin)
    {
		cout << "Choose Color " << endl;
		cout << "white(0) or black(1): " << endl;
		cin >> color;
        
		if((color!=0)&&(color!=1))
		{
		    cout << "Sorry, but that is not 0 or 1.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
		}
		else if (cin)
        {
			cout << "You selected " ;

			if(!color){
				cout << "WHITE" << endl;
				white = a;
				white.setPosition("WHITE");
				black = b;
				black.setPosition("BLACK");
				black.setComp(true);
			}
			else{
				cout << "BLACK" << endl;
				white = b;
				white.setPosition("WHITE");
				white.setComp(true);
				black = a;
				black.setPosition("BLACK");
			}
			break;
        }
        else if (cin.fail() && !(cin.eof() || cin.bad()))
        {
            cout << "Sorry, but that is not an integer.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
        }
    }
}

void gameFactory::setResults(){
    gameScore.numWhitePieces = gameBoard.getScore(white);
    gameScore.numBlackPieces = gameBoard.getScore(black);
    if (gameScore.numWhitePieces > gameScore.numBlackPieces){

        gameScore.winner = "WHITE";
        gameScore.loser = "BLACK";
    }
    else if (gameScore.numWhitePieces <gameScore.numBlackPieces){
        gameScore.winner = "BLACK";
        gameScore.loser = "WHITE";
    }
    else{
        gameScore.winner = "TIE";
        gameScore.loser = "TIE";
    }
}

void gameFactory::getResults(){
	if (gameScore.numWhitePieces > gameScore.numBlackPieces){
		cout << "\n \nGame Winner is  " << gameScore.winner << endl;
		cout << "With a final score of " << gameScore.numWhitePieces << "-" << gameScore.numBlackPieces<< endl;
    }
    else if (gameScore.numWhitePieces <gameScore.numBlackPieces){
		cout << "\n \nGame Winner is  " << gameScore.winner << endl;
		cout << "With a final score of " << gameScore.numBlackPieces << "-" << gameScore.numWhitePieces << endl;
    }
    else{
		cout << "\n \nOutcome is a Tie" << endl;
    }
	cout << "\n \nThank you for playing!" << endl;
}