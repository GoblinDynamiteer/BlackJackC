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

	if(!setCardsNames(&game) || !setCards(&game)){
		printf("Setting up game failed!");
	}

	shuffleDeck(&game, SHUFFLES);
	printDeck(&game);

	return 0;
}
