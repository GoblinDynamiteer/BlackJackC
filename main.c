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

	if(!setCardsNames(&game) || !setCards(&game)){
		printf("Setting up game failed!");
	}

	shuffleDeck(&game, SHUFFLES);

	if(!checkShuffle(&game)){
		printf("Shuffle failed!");
	}

	//printDeck(&game);

	while(1){
		for(int i = 0; i < MAX_HAND; i++){
			game.player.hand[i] = NULL;
			game.player.hand[i] = dealNextCard(&game);
			printf("Player hand, card %d : ", i+1);
			printCardName(&game, *game.player.hand[i]);
		}
		getchar();
	}




	return 0;
}
