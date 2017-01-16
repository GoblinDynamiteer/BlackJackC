/*
 * cards.c
 *
 *  Created on: 16 jan. 2017
 *      Author: kampe_000
 */


#include "..\def.h"

/*	 Sets cards to decks	*/
bool setCards(game * game){

	int count = 0;
	int value = ACE;
	int suit;

	for(int deck = 0; deck < DECKS; deck++){
		suit = HEARTS;
		for(int card = 0; card < DECK_SIZE; card++){
			game->deck[deck].card[card].value = value++;
			game->deck[deck].card[card].suit = suit;
			if(value == VALUES_MAX){
				value = ACE;
				suit++;
			}
			//printCardName(game, game->deck[deck].card[card]);
			assert(suit <= SUITS_MAX);
			count++;
		}
	}

	assert(count == DECK_SIZE * DECKS);
	return (count == DECK_SIZE * DECKS);
}

/* Fix swe/eng translations
 * Copies text names to char arrays	*/
bool setCardsNames(game * game){
	int count = 0;
	char * values[VALUES_MAX] = {
		"Ace",
		"Two",
		"Three",
		"Four",
		"Five",
		"Six",
		"Seven",
		"Eight",
		"Nine",
		"Ten",
		"Jack",
		"Queen",
		"King"
	};

	for(int i = 0; i < VALUES_MAX; i++){
		game->cardValues[i] = malloc(sizeof(char)* 8);
		strcpy(game->cardValues[i], values[i]);
		count++;
	}

	char * suits[SUITS_MAX] = {
		"Hearts",
		"Diamonds",
		"Clubs",
		"Spades",
	};

	for(int i = 0; i < SUITS_MAX; i++){
		game->cardSuits[i] = malloc(sizeof(char)* 10);
		strcpy(game->cardSuits[i], suits[i]);
		count++;
	}

	assert(count == SUITS_MAX + VALUES_MAX);
	return (count == SUITS_MAX + VALUES_MAX);
}

void printCardName(game * game, card card){
	printf("%s of %s\n",
			game->cardValues[card.value],
			game->cardSuits[card.suit]
	);
}
