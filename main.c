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

	if(!setCardsNames(&game) || !setCards(&game)){
		printf("Setting up game failed!");
	}

	return 0;
}
