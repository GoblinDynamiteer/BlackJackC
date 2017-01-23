/*

BlackJack by Johan K�mpe!

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
		printf("\n- NEW HAND -\n");
		printf("\n<<DEALER HAS\n\t");
		printCardName(&game, *game.dealer.hand[0]);
		printf("\t");
		printCardName(&game, *game.dealer.hand[1]);
		addScore(&game, *game.dealer.hand[1], DEALER);
		printf("[%d / %d]\n",
				game.dealer.score.low,
				game.dealer.score.high
		);
		int i = 2;
		while(dealerDraw(&game)){
			printf("<< DEALER DRAWING\n\t");
			dealCardToPlayer(&game, DEALER);
			assert(game.dealer.hand[i] != NULL);
			printCardName(&game, *game.dealer.hand[i++]);
			printf("[%d / %d]\n",
					game.dealer.score.low,
					game.dealer.score.high
			);
		}
		if(checkNatural(&game, DEALER)){
			printf(">> DEALER HAS NATURAL BLACKJACK>\n");
		}
		else if(isPlayerBust(&game, DEALER)){
			printf(">> DEALER BUST>\n");
		}
		else{
			printf("<< DEALER STAYING>\n");
		}
		getchar();

	}

	return 0;
}
