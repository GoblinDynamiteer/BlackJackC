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

	printDeck(&game);

	printf("\nDeck print done -- Start dealing test\n");
	getchar();

	int counter = 0;

	while(1){
		counter++;
		firstDeal(&game);
		printf("\nFirst Deal:\nYour hand:\n");
		printCardName(&game, *game.player.hand[0]);
		printCardName(&game, *game.player.hand[1]);
		printf("\nDealer hand:\n");
		printCardName(&game, *game.dealer.hand[0]);
		printf("************\n");
		printf("\nScore: %d / %d - Dealer: %d / %d",
				game.player.score.low,
				game.player.score.high,
				game.dealer.score.low,
				game.dealer.score.high
		);
		if(checkNatural(&game, PLAYER)){
			printf("\n[DEAL %4d]\n", counter);
			getchar();
		}
	}


	return 0;
}
