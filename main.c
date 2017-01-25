/*

BlackJack by Johan Kämpe!

Rules from
http://www.bicyclecards.com/how-to-play/blackjack/
http://www.cherryapp.se/casino-school/

*/

#include "def.h"

int main(){

	/*	 Init game struct */
	game game;

	initRandom();
	setupGame(&game);

	if(!setCardsNames(&game) || !setCards(&game)){
		printf("Setting up game failed!");
	}

	shuffleDeck(&game, SHUFFLES);

	if(!checkShuffle(&game)){
		printf("Shuffle failed!");
	}

	//printDeck(&game);

	//printf("\nDeck print done -- Start dealing test\n");
	//getchar();

	int counter = 0;

	while(++counter < 5){
		printf("\n- NEW DEAL - CYCLE %d\n" , counter);
		newGameCycle(&game);
		playerCycle(&game);
		printf("\n- DEALER CYCLE -\n");
		dealerCycle(&game);
		printf("\n- DETERMINE WINNERS -\n");
		winnerCycle(&game);
	}

	return 0;
}
