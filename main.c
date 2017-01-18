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
		for(int i = 0; i < MAX_HAND;){
			counter++;

			game.player.hand[i] = NULL;
			game.player.hand[i] = dealNextCard(&game);
			if(game.player.hand[i] == NULL){
				setCards(&game);
				shuffleDeck(&game, SHUFFLES);
				printf("\n\n<No more cards -- Shuffling deck>\n");
				if(!checkShuffle(&game)){
					printf("<Shuffle failed!>\n\n");
					break;
				}
				printf("<Shuffle correct!>\n\n");
				game.player.hand[i] = dealNextCard(&game);
			}
			printf("[Card #%5d]\n", counter);
			printf("[Hand %d] : ", i+1);
			printCardName(&game, *game.player.hand[i]);
			addScore(&game, *game.player.hand[i], PLAYER);
			printf("[Score: ");
			if(game.player.score.low <= 21)	{printf("%d",game.player.score.low);}
			if(game.player.score.high <= 21 &&
				game.player.score.high != game.player.score.low){
					printf(" / %d",game.player.score.high);
			}
			printf("]");
			if(game.player.score.low > 21){
				printf("\n<BUST!> [%d]\n", game.player.score.low);
				resetScore(&game);
				i = 0;
				continue;
			}
			getchar();
			i++;
		}
	}

	return 0;
}
