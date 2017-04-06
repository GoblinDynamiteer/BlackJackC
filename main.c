/*

BlackJack by Johan Kämpe!
Swedish pub rules

Rules from
http://www.bicyclecards.com/how-to-play/blackjack/
http://cherryspelgladje.se/spelregler/

TODO:
Raise Double:
	on 7, 8, 9, 10 or 11 on first deal - ACE counts as 1

Insurance:
	First dealer card is ACE, player adds 0.5x to bet.
	If dealer gets natural, player gets 2x insurance, but loses original bet.
	ex: bet 30 -> insurance 15 -> dealer gets natural -> bet = -30 + 15x2 = 0

	If dealer does not get natural, the insurance is lost, but original
	bet is kept.

Split 2 ACEs:
	Only +1 card per ACE, unless ACE -> can split agian.
	10+ACE counts as 21 and not natural blackjack

*/

#include "def.h"

int main(int argc, char *argv[]){

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

	if(!initGfx(&game)){
		printf("SDL / Graphics init failed!");
	}
	//printDeck(&game);

	//printf("\nDeck print done -- Start dealing test\n");
	//getchar();

	int counter = 0;

	while(processEvent(&game)){
		renderGame(&game);
		counter++;
		SDL_Delay(1000/60);
	}

	return 0;
}
